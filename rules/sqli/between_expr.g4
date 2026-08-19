// rule: between_expr
// severity: LOW
// action: ALLOW
// description: BETWEEN 表达式结构检测
// profile: sql

parser grammar between_expr;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : add_expr NOT? BETWEEN add_expr AND add_expr ;
