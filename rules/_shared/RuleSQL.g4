// ============================================================
// RuleSQL.g4 — 规则共享匹配骨架
// ------------------------------------------------------------
// 供 rules/**/*.g4 import 复用。注意：
//   * 这不是完整 SQL 语法 —— 完整语句判定由引擎专用 MiniSQL.g4 负责
//     （MiniSQL 词法不同，且覆盖 GROUP BY/HAVING/JOIN/CASE 等）
//   * 这里只提供规则编写所需的最小结构：
//       布尔/算术表达式、表达式列表、最小 SELECT 形状
//   * 语义谓词（isIdent / numbersEqual / stringsEqual）随语法导入
// ============================================================

parser grammar RuleSQL;

options { tokenVocab = SQLTokens; }

@parser::includes {
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>
}

@parser::members {
// ----------------------------------------------------------
// 规则共享语义谓词
// ----------------------------------------------------------
static std::string lowerText(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return r;
}

static bool isIdent(antlr4::Token* t, const std::string& expected) {
    return lowerText(t->getText()) == expected;
}

static std::string canonicalNumber(const std::string& raw) {
    char* end = nullptr;
    double v = std::strtod(raw.c_str(), &end);
    if (end == raw.c_str() || *end != '\0') return raw;
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%.17g", v);
    return buf;
}

static bool numbersEqual(antlr4::Token* a, antlr4::Token* b) {
    return canonicalNumber(a->getText()) == canonicalNumber(b->getText());
}

static std::string unquote(const std::string& s) {
    if (s.size() >= 2 && s.front() == '\'' && s.back() == '\'') {
        return s.substr(1, s.size() - 2);
    }
    return s;
}

static bool stringsEqual(antlr4::Token* a, antlr4::Token* b) {
    return unquote(a->getText()) == unquote(b->getText());
}

// ----------------------------------------------------------
// 常量值求值（参考 sql_parser.t 的 expr_recursive：括号由语法处理，
// 值语义由谓词提取）——1=(1) / (1)=1 / (1)=(1) 都解析为常量比较
// 用通用 ParserRuleContext 遍历，避免依赖生成顺序靠后的上下文类型。
// ----------------------------------------------------------
static bool constLiteralText(antlr4::ParserRuleContext* c, int tokenType,
                             std::string& val) {
    if (!c) return false;
    for (auto* child : c->children) {
        if (auto* t = dynamic_cast<antlr4::tree::TerminalNode*>(child)) {
            if (t->getSymbol()->getType() == tokenType) {
                val = t->getText();
                return true;
            }
        } else if (auto* pc = dynamic_cast<antlr4::ParserRuleContext*>(child)) {
            if (constLiteralText(pc, tokenType, val)) return true;
        }
    }
    return false;
}

static bool constNumbersEqual(antlr4::ParserRuleContext* a,
                              antlr4::ParserRuleContext* b) {
    std::string va, vb;
    return constLiteralText(a, NUMBER, va) && constLiteralText(b, NUMBER, vb) &&
           canonicalNumber(va) == canonicalNumber(vb);
}

static bool constStringsEqual(antlr4::ParserRuleContext* a,
                              antlr4::ParserRuleContext* b) {
    std::string va, vb;
    return constLiteralText(a, STRING, va) && constLiteralText(b, STRING, vb) &&
           unquote(va) == unquote(vb);
}
}

// ----------------------------------------------------------
// 表达式骨架（层级参考 SQLiteParser.g4，仅保留本规则已用到的子集）：
//   expr -> expr_or -> expr_and -> expr_not(NOT*)
//   -> expr_binary(= != | IS | BETWEEN | IN | LIKE 尾缀内联)
//   -> expr_comparison(< <= > >=) -> expr_bitwise -> expr_addition(+-)
//   -> expr_multiplication(* / %) -> expr_string(||) -> expr_unary
//   -> expr_base(字面量/标识符/函数/子查询/括号)
// ----------------------------------------------------------

expr     : expr_or ;
expr_or  : expr_and (OR expr_and)* ;
expr_and : expr_not (AND expr_not)* ;
expr_not : NOT* expr_binary ;

expr_binary
    : expr_comparison (
        (EQ | NE) expr_comparison
        | IS NOT? (NULL | TRUE | FALSE)
        | NOT? BETWEEN expr_comparison AND expr_comparison
        | NOT? IN LPAREN (select_stmt | expr_comparison (COMMA expr_comparison)*) RPAREN
        | NOT? LIKE expr_comparison
    )*
    ;

expr_comparison : expr_bitwise ((LT | LE | GT | GE) expr_bitwise)* ;
expr_bitwise    : expr_addition ;   // SQLTokens 无 << >> & | token，保留层级占位
expr_addition   : expr_multiplication ((PLUS | MINUS) expr_multiplication)* ;
expr_multiplication : expr_string ((STAR | DIV | MOD) expr_string)* ;
expr_string     : expr_unary (PIPE2 expr_unary)* ;
expr_unary      : (PLUS | MINUS)* expr_base ;

expr_base
    : literal_value
    | IDENT (LPAREN expr_list? RPAREN)?
    | (NOT? EXISTS)? LPAREN select_stmt RPAREN
    | expr_recursive
    ;

literal_value : NUMBER | STRING | TRUE | FALSE | NULL ;

expr_list      : expr (COMMA expr)* ;
expr_recursive : LPAREN expr (COMMA expr)* RPAREN ;   // 括号表达式（SQLiteParser.g4）

// ----------------------------------------------------------
// 最小 SELECT 形状（用于子查询/片段识别，非完整 SELECT 语法）
// ----------------------------------------------------------

select_stmt
    : SELECT (STAR | expr_list)
      (FROM table_ref)?
      (WHERE expr)?
    ;

table_ref : IDENT | LPAREN select_stmt RPAREN ;

// ----------------------------------------------------------
// 常量值：字面量或任意层括号包裹（1 / (1) / ((1))）
// ----------------------------------------------------------

constant_value
    : NUMBER
    | STRING
    | TRUE
    | FALSE
    | NULL
    | LPAREN constant_value RPAREN
    ;
