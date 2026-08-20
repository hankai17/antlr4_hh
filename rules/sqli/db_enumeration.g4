// rule: db_enumeration
// severity: MEDIUM
// action: ALLOW
// description: 数据库结构枚举：information_schema 元数据访问
// profile: sql

parser grammar db_enumeration;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : i=IDENT {isIdent($i, "information_schema")}? ;
