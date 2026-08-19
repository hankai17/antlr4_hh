// rule: load_file
// severity: CRITICAL
// action: BLOCK
// description: 文件读取：LOAD_FILE()
// profile: sql

parser grammar load_file;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : i=IDENT {isIdent($i, "load_file")}? LPAREN expr_list? RPAREN ;
