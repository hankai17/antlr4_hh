// rule: update_fragment
// severity: MEDIUM
// action: ALLOW
// description: UPDATE ... SET 语句片段
// profile: fragment

parser grammar update_fragment;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : UPDATE IDENT (SET expr_list?)? ;
