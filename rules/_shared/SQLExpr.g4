// ============================================================
// SQLExpr.g4 — 规则共享表达式/语句语法
// ------------------------------------------------------------
// 攻击规则 .g4 通过 import 复用这里的表达式与 SELECT 语句结构，
// 只需要写自己的 pattern 规则 + 语义谓词。
// ============================================================

parser grammar SQLExpr;

options { tokenVocab = SQLTokens; }

@parser::includes {
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>
}

@parser::members {
// 规则共享的语义谓词（导入到每条规则的生成解析器中）
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
}

expr     : or_expr ;
or_expr  : and_expr (OR and_expr)* ;
and_expr : not_expr (AND not_expr)* ;

not_expr
    : NOT not_expr
    | comparison
    ;

comparison
    : add_expr cmp_tail*
    ;

cmp_tail
    : cmp_op add_expr
    | NOT? IN LPAREN (select_stmt | expr_list) RPAREN
    | NOT? LIKE add_expr
    | NOT? BETWEEN add_expr AND add_expr
    | IS NOT? (NULL | TRUE | FALSE)
    | NOT? EXISTS LPAREN select_stmt RPAREN
    ;

cmp_op : EQ | NE | LT | LE | GT | GE ;

add_expr : mul_expr (add_op mul_expr)* ;
add_op   : PLUS | MINUS | PIPE2 ;

mul_expr : unary_expr (mul_op unary_expr)* ;
mul_op   : STAR | DIV | MOD ;

unary_expr
    : (PLUS | MINUS) unary_expr
    | primary
    ;

primary
    : NUMBER
    | STRING
    | TRUE
    | FALSE
    | NULL
    | IDENT (LPAREN expr_list? RPAREN)?
    | LPAREN (select_stmt | expr) RPAREN
    ;

expr_list : expr (COMMA expr)* ;

select_stmt
    : SELECT (STAR | expr_list)
      (FROM table_ref)?
      (WHERE expr)?
      (ORDER BY expr (ASC | DESC)?)?
      (LIMIT expr)?
    ;

table_ref : IDENT | LPAREN select_stmt RPAREN ;
