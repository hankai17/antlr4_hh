// rule: limit_expr
// severity: LOW
// action: ALLOW
// description: LIMIT 表达式结构检测
// profile: sql

parser grammar limit_expr;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : LIMIT expr (OFFSET expr)? ;
