// rule: insert_fragment
// severity: MEDIUM
// action: ALLOW
// description: INSERT INTO 语句片段
// profile: fragment

parser grammar insert_fragment;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : INSERT INTO? IDENT? (LPAREN expr_list RPAREN)? (VALUES LPAREN expr_list RPAREN)? ;
