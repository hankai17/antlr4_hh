// rule: select_from_fragment
// severity: LOW
// action: ALLOW
// description: SELECT ... FROM 片段
// profile: fragment

parser grammar select_from_fragment;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : SELECT (STAR | expr_list) FROM table_ref ;
