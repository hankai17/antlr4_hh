// rule: sleep
// severity: CRITICAL
// action: BLOCK
// description: 时间盲注：SLEEP()
// profile: sql

parser grammar sleep;

options { tokenVocab = SQLTokens; }

import RuleSQL;

// SLEEP 是函数名而非关键字：IDENT + 大小写不敏感谓词
pattern : i=IDENT {isIdent($i, "sleep")}? LPAREN expr_list? RPAREN ;
