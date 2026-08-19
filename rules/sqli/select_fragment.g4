// rule: select_fragment
// severity: LOW
// action: ALLOW
// description: SELECT 片段
// profile: fragment

parser grammar select_fragment;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : SELECT (STAR | expr_list) (FROM table_ref)? (WHERE expr)? (ORDER BY expr)? (LIMIT expr)? ;
