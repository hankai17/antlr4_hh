// rule: stacked_query
// severity: CRITICAL
// action: BLOCK
// description: 堆叠查询：; 后跟 SQL 关键字
// profile: sql

parser grammar stacked_query;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : SEMI (SELECT | INSERT | UPDATE | DELETE | DROP | ALTER | CREATE) ;
