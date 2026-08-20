// rule: pg_sleep
// severity: CRITICAL
// action: BLOCK
// description: PostgreSQL 时间盲注：pg_sleep()
// profile: sql

parser grammar pg_sleep;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : i=IDENT {isIdent($i, "pg_sleep")}? LPAREN expr_list? RPAREN ;
