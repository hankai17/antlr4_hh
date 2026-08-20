// rule: subquery
// severity: MEDIUM
// action: ALLOW
// description: 子查询结构检测
// profile: sql

parser grammar subquery;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : LPAREN select_stmt RPAREN ;
