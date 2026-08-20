// rule: order_by_expr
// severity: LOW
// action: ALLOW
// description: ORDER BY 表达式结构检测
// profile: sql

parser grammar order_by_expr;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : ORDER BY expr (ASC | DESC)? ;
