// rule: exists_subquery
// severity: MEDIUM
// action: ALLOW
// description: EXISTS 子查询结构检测
// profile: sql

parser grammar exists_subquery;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern
    : EXISTS LPAREN select_stmt RPAREN
    | NOT EXISTS LPAREN select_stmt RPAREN
    ;
