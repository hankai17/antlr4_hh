// rule: delete_fragment
// severity: MEDIUM
// action: ALLOW
// description: DELETE FROM 语句片段
// profile: fragment

parser grammar delete_fragment;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : DELETE FROM? IDENT ;
