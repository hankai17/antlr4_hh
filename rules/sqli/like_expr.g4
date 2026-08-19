// rule: like_expr
// severity: LOW
// action: ALLOW
// description: LIKE 表达式结构检测
// profile: sql

parser grammar like_expr;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : add_expr NOT? LIKE add_expr ;
