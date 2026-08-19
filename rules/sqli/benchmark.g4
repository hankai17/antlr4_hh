// rule: benchmark
// severity: CRITICAL
// action: BLOCK
// description: 性能消耗函数 BENCHMARK()
// profile: sql

parser grammar benchmark;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : i=IDENT {isIdent($i, "benchmark")}? LPAREN expr_list? RPAREN ;
