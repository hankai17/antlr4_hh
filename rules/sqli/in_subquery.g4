// rule: in_subquery
// severity: MEDIUM
// action: ALLOW
// description: IN 子查询结构检测
// profile: sql

parser grammar in_subquery;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : add_expr NOT? IN LPAREN select_stmt RPAREN ;
