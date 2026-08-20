// rule: union_select
// severity: CRITICAL
// action: BLOCK
// description: UNION SELECT 联合查询
// profile: sql

parser grammar union_select;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : UNION ALL? SELECT expr_list? ;
