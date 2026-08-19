// ============================================================
// rulec — WAF 规则编译器
// ------------------------------------------------------------
// 输入：rules/xxx.g4（Rule.g4 规则语言）
// 输出：C++ 检测插件源码 + lib<name>_rule.so
//
// 流水线：
//   Rule.g4 规则  --RuleParser-->  规则 AST  --codegen-->  plugin.cc
//                                                       --g++ -shared-->
//                                                       lib<name>_rule.so
//
// 生成的插件只依赖 ast.h / rule_plugin.h，不依赖 ANTLR 运行时，
// 因此 .so 可以独立分发、热加载。
// ============================================================

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "antlr4-runtime.h"
#include "RuleLexer.h"
#include "RuleParser.h"

using namespace antlr4;

namespace {

// ------------------------------------------------------------
// 规则 AST（从 Rule.g4 解析树折叠而来）
// ------------------------------------------------------------

struct Pattern;

struct PatternArg {
    std::string name;              // 属性名 / 语义角色
    std::string value;             // 标量值（等值或 contains）
    bool isContains = false;       // contains 谓词
    std::unique_ptr<Pattern> nested;     // 嵌套子模式
};

struct Pattern {
    std::string kind;
    std::vector<std::unique_ptr<PatternArg>> args;
};

struct RuleDef {
    std::string name;
    std::string severity = "MEDIUM";
    std::string action = "BLOCK";
    std::string profile = "sql";
    std::string description;
    std::unique_ptr<Pattern> pattern;
};

std::string unescapeString(const std::string& token) {
    if (token.size() >= 2 && token.front() == '"' && token.back() == '"') {
        std::string s = token.substr(1, token.size() - 2);
        std::string out;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == '\\' && i + 1 < s.size()) {
                switch (s[i + 1]) {
                    case 'n': out += '\n'; ++i; break;
                    case 't': out += '\t'; ++i; break;
                    case 'r': out += '\r'; ++i; break;
                    case '"': out += '"'; ++i; break;
                    case '\\': out += '\\'; ++i; break;
                    default: out += s[i]; break;
                }
            } else {
                out += s[i];
            }
        }
        return out;
    }
    return token;
}

std::string lower(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

// 已知 AST 节点类型（供校验告警）。
const std::set<std::string> kKnownKinds = {
    "Query", "Select", "SelectItem", "From", "TableRef",
    "Where", "GroupBy", "Having", "OrderBy", "OrderItem", "Limit",
    "BinaryExpr", "UnaryExpr", "Constant", "ColumnRef", "FunctionCall",
    "List", "CaseExpr", "WhenClause", "Text",
};

std::unique_ptr<PatternArg> convertArg(RuleParser::PatternArgContext* ctx) {
    auto arg = std::make_unique<PatternArg>();
    arg->name = ctx->IDENT()->getText();
    if (ctx->STRING()) {
        arg->value = unescapeString(ctx->STRING()->getText());
        arg->isContains = (arg->name == "contains");
    } else if (ctx->BOOL()) {
        arg->value = ctx->BOOL()->getText();
    } else if (ctx->nodePattern()) {
        auto nested = std::make_unique<PatternArg>();
        nested->name = arg->name;  // 语义角色
        auto pat = std::make_unique<Pattern>();
        pat->kind = ctx->nodePattern()->IDENT()->getText();
        if (ctx->nodePattern()->patternArgList()) {
            for (auto* a : ctx->nodePattern()->patternArgList()->patternArg()) {
                pat->args.push_back(convertArg(a));
            }
        }
        nested->nested = std::move(pat);
        return nested;
    }
    return arg;
}

RuleDef parseRuleFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("cannot open rule file: " + path);
    }
    std::stringstream ss;
    ss << in.rdbuf();

    ANTLRInputStream input(ss.str());
    RuleLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    RuleParser parser(&tokens);

    lexer.removeErrorListeners();
    parser.removeErrorListeners();

    RuleParser::RuleFileContext* tree = parser.ruleFile();
    if (parser.getNumberOfSyntaxErrors() > 0) {
        throw std::runtime_error("rule file has syntax errors: " + path);
    }
    if (tree->ruleDef().empty()) {
        throw std::runtime_error("no rule defined in: " + path);
    }

    RuleParser::RuleDefContext* def = tree->ruleDef(0);
    RuleDef rule;
    rule.name = def->IDENT()->getText();

    for (auto* p : def->property()) {
        if (p->SEVERITY()) rule.severity = p->SEVERITY()->getText();
        else if (p->ACTION()) rule.action = p->ACTION()->getText();
        else if (p->PROFILE()) rule.profile = lower(p->PROFILE()->getText());
        else if (p->STRING()) rule.description = unescapeString(p->STRING()->getText());
    }

    RuleParser::NodePatternContext* pat = def->patternDef()->nodePattern();
    rule.pattern = std::make_unique<Pattern>();
    rule.pattern->kind = pat->IDENT()->getText();
    if (pat->patternArgList()) {
        for (auto* a : pat->patternArgList()->patternArg()) {
            rule.pattern->args.push_back(convertArg(a));
        }
    }

    if (!kKnownKinds.count(rule.pattern->kind)) {
        std::cerr << "warning: unknown pattern kind '" << rule.pattern->kind
                  << "' (known: Query/Select/BinaryExpr/...)" << std::endl;
    }
    return rule;
}

// ------------------------------------------------------------
// 代码生成
// ------------------------------------------------------------

struct CodegenContext {
    int nextId = 0;
    std::ostringstream decls;   // 前置声明
    std::ostringstream bodies;  // 函数定义
};

int emitPattern(CodegenContext& cg, const Pattern& pat) {
    int id = cg.nextId++;

    std::ostringstream body;
    body << "static bool m" << id << "(const waf::AstNode& n) {\n";
    body << "    if (n.kind != \"" << pat.kind << "\") return false;\n";

    for (const auto& arg : pat.args) {
        if (arg->nested) {
            int nestedId = emitPattern(cg, *arg->nested);
            body << "    {\n"
                 << "        const waf::AstNode* c = n.namedChild(\"" << arg->name << "\");\n"
                 << "        if (!c || !m" << nestedId << "(*c)) return false;\n"
                 << "    }\n";
        } else if (arg->isContains) {
            body << "    const std::string& v = n.attr(\"value\");\n"
                 << "    if (v.find(\"" << arg->value << "\") == std::string::npos) return false;\n";
        } else {
            body << "    if (n.attr(\"" << arg->name << "\") != \"" << arg->value << "\") return false;\n";
        }
    }
    body << "    return true;\n"
         << "}\n\n";

    cg.decls << "static bool m" << id << "(const waf::AstNode& n);\n";
    cg.bodies << body.str();
    return id;
}

std::string cppEscape(const std::string& s) {
    std::string out;
    for (char ch : s) {
        switch (ch) {
            case '\\': out += "\\\\"; break;
            case '"': out += "\\\""; break;
            case '\n': out += "\\n"; break;
            case '\t': out += "\\t"; break;
            case '\r': out += "\\r"; break;
            default: out += ch; break;
        }
    }
    return out;
}

std::string generatePlugin(const RuleDef& rule) {
    CodegenContext cg;
    int topId = emitPattern(cg, *rule.pattern);

    std::ostringstream out;
    out << "// Generated by rulec from rule file. DO NOT EDIT.\n"
        << "#include \"rule_plugin.h\"\n"
        << "#include <string>\n\n"
        << cg.decls.str() << "\n"
        << cg.bodies.str()
        << "extern \"C\" int waf_rule_abi() { return waf::WAF_RULE_ABI; }\n\n"
        << "extern \"C\" const waf::RuleInfo* waf_rule_info() {\n"
        << "    static const waf::RuleInfo info = {\n"
        << "        \"" << cppEscape(rule.name) << "\",\n"
        << "        \"" << rule.severity << "\",\n"
        << "        \"" << rule.action << "\",\n"
        << "        \"" << cppEscape(rule.description) << "\",\n"
        << "        \"" << rule.profile << "\"\n"
        << "    };\n"
        << "    return &info;\n"
        << "}\n\n"
        << "extern \"C\" bool waf_rule_check(const waf::AstNode& root) {\n"
        << "    return waf::matchAny(root, m" << topId << ");\n"
        << "}\n";
    return out.str();
}

bool writeFile(const std::string& path, const std::string& content) {
    std::ofstream out(path);
    if (!out) return false;
    out << content;
    return out.good();
}

int run(const std::string& gxx, const std::string& includeDir,
        const std::string& ccFile, const std::string& soFile) {
    std::string cmd = gxx + " -std=c++17 -O2 -fPIC -shared -I" + includeDir +
                      " -o " + soFile + " " + ccFile;
    return std::system(cmd.c_str());
}

}  // namespace

int main(int argc, char* argv[]) {
    std::string includeDir = ".";
    std::string outDir = "build/plugins";
    std::string ruleFile;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--include" && i + 1 < argc) includeDir = argv[++i];
        else if (a == "-o" && i + 1 < argc) outDir = argv[++i];
        else ruleFile = a;
    }

    if (ruleFile.empty()) {
        std::cerr << "usage: rulec [--include DIR] [-o OUTDIR] rule.g4\n";
        return 2;
    }

    try {
        RuleDef rule = parseRuleFile(ruleFile);
        std::string cc = generatePlugin(rule);

        std::string mkdir = "mkdir -p " + outDir;
        if (std::system(mkdir.c_str()) != 0) {
            throw std::runtime_error("cannot create output dir: " + outDir);
        }

        std::string ccPath = outDir + "/" + rule.name + "_rule.cc";
        std::string soPath = outDir + "/lib" + rule.name + "_rule.so";
        if (!writeFile(ccPath, cc)) {
            throw std::runtime_error("cannot write " + ccPath);
        }
        if (run("g++", includeDir, ccPath, soPath) != 0) {
            throw std::runtime_error("g++ failed, see " + ccPath);
        }

        std::cout << "[rulec] " << ruleFile << " -> " << soPath << "\n"
                  << "        rule=" << rule.name
                  << " severity=" << rule.severity
                  << " action=" << rule.action
                  << " profile=" << rule.profile << "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[rulec] error: " << e.what() << "\n";
        return 1;
    }
}
