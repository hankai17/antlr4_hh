// rule: string_concat
// severity: LOW
// action: ALLOW
// description: 字符串拼接特征 ||
// profile: sql

parser grammar string_concat;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : add_expr PIPE2 add_expr ;
