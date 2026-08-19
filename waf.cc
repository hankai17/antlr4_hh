// ============================================================
// waf — 编译型 WAF 规则系统主引擎
// ------------------------------------------------------------
// 请求处理流水线：
//   HTTP payload
//     -> Normalization（注释剥离、空白折叠）
//     -> Fast Path（廉价子串扫描，无命中直接 ALLOW，性能关键路径）
//     -> MiniSQL Parser（完整 SQL，ANTLR 解析）
//     -> Fragment Wrap（不完整 SQL：包装进合法上下文再解析，如 WHERE <payload>）
//     -> AST（语义中间层，规则不接触 SQL 文本）
//     -> Rule Engine（dlopen 加载的规则插件逐个 check）
//     -> ALLOW / BLOCK / UNKNOWN
// ============================================================

#include <dlfcn.h>
#include <glob.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "antlr4-runtime.h"
#include "MiniSQLLexer.h"
#include "MiniSQLParser.h"

#include "ast.h"
#include "ast_builder.h"
#include "fragment_parser.h"
#include "rule_plugin.h"

using namespace antlr4;

namespace {

// ------------------------------------------------------------
// Normalization
// ------------------------------------------------------------

std::string trim(const std::string& s) {
    size_t b = 0, e = s.size();
    while (b < e && std::isspace(static_cast<unsigned char>(s[b]))) ++b;
    while (e > b && std::isspace(static_cast<unsigned char>(s[e - 1]))) --e;
    return s.substr(b, e - b);
}

// 原型级归一化：剥离 SQL 注释、折叠空白。
// 注意：这是朴素实现，不感知字符串字面量；生产版需按词法感知处理
// （URL 解码、charset、关键字混淆、等价空白等）。
std::string normalize(const std::string& raw) {
    std::string s = raw;

    // 块注释 /* ... */
    while (true) {
        size_t p = s.find("/*");
        if (p == std::string::npos) break;
        size_t q = s.find("*/", p + 2);
        if (q == std::string::npos) {
            s.erase(p);
            break;
        }
        s.erase(p, q + 2 - p);
    }

    // 行注释 -- ...（含 MySQL 变体 -- 后跟空白才生效，原型从宽）
    std::string out;
    for (size_t i = 0; i < s.size();) {
        if (s[i] == '-' && i + 1 < s.size() && s[i + 1] == '-') {
            while (i < s.size() && s[i] != '\n') ++i;
        } else {
            out += s[i++];
        }
    }

    // 空白折叠
    std::string collapsed;
    bool lastSpace = false;
    for (char ch : out) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            if (!lastSpace) collapsed += ' ';
            lastSpace = true;
        } else {
            collapsed += ch;
            lastSpace = false;
        }
    }
    return trim(collapsed);
}

std::string lower(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

// ------------------------------------------------------------
// 规则插件加载
// ------------------------------------------------------------

struct LoadedRule {
    void* handle = nullptr;
    std::string name;
    std::string severity;
    std::string action;
    std::string description;
    std::string profile;
    bool (*check)(const waf::AstNode&) = nullptr;
};

std::vector<std::string> listPlugins(const std::string& dir) {
    std::vector<std::string> files;
    glob_t g;
    std::string pattern = dir + "/*.so";
    if (glob(pattern.c_str(), 0, nullptr, &g) == 0) {
        for (size_t i = 0; i < g.gl_pathc; ++i) files.emplace_back(g.gl_pathv[i]);
    }
    globfree(&g);
    std::sort(files.begin(), files.end());
    return files;
}

std::vector<LoadedRule> loadRules(const std::string& dir) {
    std::vector<LoadedRule> rules;
    for (const auto& path : listPlugins(dir)) {
        void* handle = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!handle) {
            std::cerr << "[waf] load failed: " << path << " : " << dlerror() << "\n";
            continue;
        }

        auto abi = reinterpret_cast<int (*)()>(dlsym(handle, "waf_rule_abi"));
        auto infoFn = reinterpret_cast<const waf::RuleInfo* (*)()>(dlsym(handle, "waf_rule_info"));
        auto checkFn = reinterpret_cast<bool (*)(const waf::AstNode&)>(dlsym(handle, "waf_rule_check"));
        if (!abi || !infoFn || !checkFn) {
            std::cerr << "[waf] bad plugin symbols: " << path << "\n";
            dlclose(handle);
            continue;
        }
        if (abi() != waf::WAF_RULE_ABI) {
            std::cerr << "[waf] ABI mismatch (plugin=" << abi()
                      << ", engine=" << waf::WAF_RULE_ABI << "): " << path << "\n";
            dlclose(handle);
            continue;
        }

        const waf::RuleInfo* info = infoFn();
        LoadedRule r;
        r.handle = handle;
        r.name = info->name;
        r.severity = info->severity;
        r.action = info->action;
        r.description = info->description;
        r.profile = info->profile;
        r.check = checkFn;
        rules.push_back(std::move(r));
    }
    return rules;
}

// ------------------------------------------------------------
// Fast Path：廉价预筛层（原型用子串特征表，生产可升级为 DFA 状态机）
// ------------------------------------------------------------

const std::vector<std::string> kFastPathTokens = {
    // SQL 关键结构与注入惯用特征（命中才进入深检；无命中直接 ALLOW）
    "select", "union", "sleep(", "load_file", "benchmark",
    "information_schema", "0x",
    // 其他语句类型与堆叠查询
    "insert ", "update ", "delete ", "drop ", "alter ", "create ", ";",
    "||", "order by", "limit ",
    // 恒真 / 布尔盲注惯用词
    "=", "or ", "and ", "'", "--", "/*",
    // XSS
    "<script",
};

std::vector<std::string> fastPathHit(const std::string& normalized) {
    std::string hay = lower(normalized);
    std::vector<std::string> hits;
    for (const auto& tok : kFastPathTokens) {
        if (hay.find(tok) != std::string::npos) hits.push_back(tok);
    }
    return hits;
}

// ------------------------------------------------------------
// SQL 解析 -> AST
// ------------------------------------------------------------

enum class ParseStatus { OK, ERROR };

struct SqlResult {
    ParseStatus status = ParseStatus::ERROR;
    waf::AstPtr ast;
};

SqlResult parseSql(const std::string& sql) {
    ANTLRInputStream input(sql);
    MiniSQLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    MiniSQLParser parser(&tokens);

    lexer.removeErrorListeners();
    parser.removeErrorListeners();

    MiniSQLParser::SqlContext* tree = parser.sql();
    bool ok = lexer.getNumberOfSyntaxErrors() == 0 && parser.getNumberOfSyntaxErrors() == 0;

    SqlResult res;
    if (!ok) return res;

    waf::AstBuilder builder;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&builder, tree);
    res.ast = builder.result();
    res.status = ParseStatus::OK;
    return res;
}

// 真实请求大多是"不完整 SQL 片段"（参数值、注入后缀、引号不平衡载荷）。
// 不再把片段塞进完整语句，而是用容错词法 + 片段解析器直接构造 AST
// （fragment="true" 标记），语义规则原样复用。
SqlResult parseSqlFragment(const std::string& frag) {
    SqlResult res;
    res.ast = waf::frag::parseFragment(frag);
    if (res.ast) res.status = ParseStatus::OK;
    return res;
}

// raw 画像：把归一化文本包成一个 Text 节点。
// value 使用小写归一化文本，保证 contains 谓词大小写不敏感；raw 保留原文供日志。
waf::AstPtr makeTextAst(const std::string& normalized, const std::string& raw) {
    auto root = std::make_unique<waf::AstNode>("Text");
    root->setAttr("value", lower(normalized));
    root->setAttr("raw", raw);
    return root;
}

std::string verdictName(bool blocked) {
    return blocked ? "BLOCK" : "ALLOW";
}

}  // namespace

int main(int argc, char* argv[]) {
    std::string rulesDir = "build/plugins";
    std::string payload;
    bool failClosed = false;
    bool dumpAst = false;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--rules" && i + 1 < argc) {
            rulesDir = argv[++i];
        } else if (a == "--fail-closed") {
            failClosed = true;
        } else if (a == "--dump-ast") {
            dumpAst = true;
        } else if (a == "--") {
            if (i + 1 < argc) payload = argv[++i];
        } else {
            payload = a;
        }
    }

    if (payload.empty()) {
        std::cerr << "usage: waf [--rules DIR] [--fail-closed] [--dump-ast] \"payload\"\n";
        return 2;
    }

    std::cout << "== Compiled WAF Rule Engine ==\n";
    std::cout << "INPUT:  " << payload << "\n";

    // 1. Normalization
    std::string normalized = normalize(payload);
    std::cout << "NORMAL: " << normalized << "\n";

    // 2. Fast Path
    std::vector<std::string> hits = fastPathHit(normalized);
    if (hits.empty()) {
        std::cout << "FAST PATH: no suspicious token -> ALLOW\n";
        return 0;
    }
    std::cout << "FAST PATH: suspicious token(s):";
    for (const auto& t : hits) std::cout << " [" << t << "]";
    std::cout << "\n";

    // 3. 加载规则插件
    std::vector<LoadedRule> rules = loadRules(rulesDir);
    if (rules.empty()) {
        std::cerr << "[waf] no rule plugins loaded from " << rulesDir << "\n";
        return 1;
    }
    std::cout << "RULES (" << rules.size() << " loaded from " << rulesDir << "):\n";
    for (const auto& r : rules) {
        std::cout << "  - " << r.name << " [" << r.severity << "/" << r.action
                  << "/" << r.profile << "] " << r.description << "\n";
    }

    bool needSql = false, needRaw = false;
    for (const auto& r : rules) {
        if (r.profile == "sql") needSql = true;
        if (r.profile == "raw") needRaw = true;
    }

    // 4. Parser -> AST（按规则画像按需构建）
    waf::AstPtr sqlAst;
    ParseStatus sqlStatus = ParseStatus::OK;
    bool fullSqlOk = false;
    if (needSql) {
        SqlResult r = parseSql(normalized);
        fullSqlOk = (r.status == ParseStatus::OK);
        if (!fullSqlOk) {
            // 容错片段解析：不完整 SQL 直接产出 AST（无需补全成完整语句）。
            r = parseSqlFragment(normalized);
            if (r.status == ParseStatus::OK) {
                std::cout << "SQL PARSE: OK (fragment AST)\n";
            } else {
                std::cout << "SQL PARSE: ERROR\n";
            }
        } else {
            std::cout << "SQL PARSE: OK\n";
        }
        sqlStatus = r.status;
        sqlAst = std::move(r.ast);
        if (dumpAst && sqlAst) std::cout << "SQL AST:\n" << sqlAst->dump();
    }
    bool sqlOk = (sqlStatus == ParseStatus::OK);

    waf::AstPtr textAst;
    // raw 规则作为兜底：仅完整 SQL 解析失败时参与判定（XSS 等非 SQL 载荷）。
    bool runRaw = needRaw && !fullSqlOk;
    if (runRaw) {
        textAst = makeTextAst(normalized, payload);
        if (dumpAst) std::cout << "TEXT AST:\n" << textAst->dump();
    }

    // 5. Rule Engine
    std::vector<const LoadedRule*> matched;
    for (const auto& r : rules) {
        bool hit = false;
        if (r.profile == "sql") {
            if (sqlAst && sqlStatus == ParseStatus::OK) hit = r.check(*sqlAst);
        } else if (r.profile == "raw") {
            if (textAst) hit = r.check(*textAst);
        }
        if (hit) matched.push_back(&r);
    }

    std::cout << "MATCHED RULES: " << matched.size() << "\n";
    for (const auto* r : matched) {
        std::cout << "  !! " << r->name << " [" << r->severity << "] " << r->description << "\n";
    }

    // 6. Verdict
    bool blocked = false;
    for (const auto* r : matched) {
        if (r->action == "BLOCK") blocked = true;
    }

    if (sqlStatus == ParseStatus::ERROR && !blocked) {
        if (failClosed) {
            blocked = true;
            std::cout << "SQL PARSE ERROR with --fail-closed -> treated as BLOCK\n";
        } else {
            std::cout << "SQL PARSE ERROR -> verdict UNKNOWN (use --fail-closed to block)\n";
            return 3;
        }
    }

    std::cout << "VERDICT: " << verdictName(blocked) << "\n";
    return blocked ? 1 : 0;
}
