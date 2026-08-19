// rule: script_tag
// severity: HIGH
// action: BLOCK
// description: XSS：<script> 标签
// profile: raw

parser grammar script_tag;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : LT i=IDENT {isIdent($i, "script")}? ;
