// ============================================================
// Rule.g4 — WAF 规则语言
// ------------------------------------------------------------
// 与 SQL.g4（MiniSQL.g4）职责分离：
//   * SQL.g4    负责把 SQL 解析成结构（parse tree -> AST）
//   * Rule.g4   负责描述"攻击模式 / 语义条件"
//
// 一条规则 = 元信息（severity/action/profile/description）
//          + 一个 AST 模式（pattern）。
//
// 例：
//   rule always_true {
//     severity: HIGH
//     description: "WHERE 1=1 恒真条件"
//     pattern: BinaryExpr(op = "=", left = Constant(value = "1"),
//                         right = Constant(value = "1"))
//   }
//
// 模式语义：
//   * KindName(...) 匹配 AST 中任意 kind == KindName 的节点（全树搜索）
//   * arg = "str"   标量属性相等（如 op = "="、name = "sleep"）
//   * arg = true    布尔属性相等（如 union = true）
//   * arg = Pattern 语义角色子节点递归匹配（如 left = Constant(...)）
//   * contains = "s" 特殊谓词：Text 节点 value 属性包含子串（用于 raw 规则）
// ============================================================

grammar Rule;

ruleFile
    : ruleDef+
    ;

ruleDef
    : RULE IDENT '{' property* patternDef+ '}'
    ;

property
    : SEVERITY_KW ':' SEVERITY
    | ACTION_KW ':' ACTION
    | PROFILE_KW ':' PROFILE
    | DESCRIPTION_KW ':' STRING
    ;

patternDef
    : PATTERN_KW ':' nodePattern
    ;

nodePattern
    : IDENT '(' patternArgList? ')'
    ;

patternArgList
    : patternArg (',' patternArg)*
    ;

patternArg
    : IDENT EQ STRING
    | IDENT EQ BOOL
    | IDENT EQ nodePattern
    | IDENT DOT IDENT EQ IDENT DOT IDENT
    ;


// ============================================================
// Lexer
// ============================================================

RULE            : 'rule';
SEVERITY_KW     : 'severity';
ACTION_KW       : 'action';
PROFILE_KW      : 'profile';
DESCRIPTION_KW  : 'description';
PATTERN_KW      : 'pattern';

EQ  : '=';
DOT : '.';

SEVERITY : 'LOW' | 'MEDIUM' | 'HIGH' | 'CRITICAL';
ACTION   : 'ALLOW' | 'BLOCK';
PROFILE  : 'sql' | 'raw';
BOOL     : 'true' | 'false';

IDENT : [a-zA-Z_] [a-zA-Z0-9_]*;

STRING
    : '"' ( '\\' . | ~["\\] )* '"'
    ;

WS
    : [ \t\r\n]+ -> skip
    ;

LINE_COMMENT
    : ('//' ~[\r\n]* | '#' ~[\r\n]* ) -> skip
    ;

BLOCK_COMMENT
    : '/*' .*? '*/' -> skip
    ;
