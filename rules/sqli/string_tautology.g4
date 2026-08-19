// rule: string_tautology
// severity: HIGH
// action: BLOCK
// description: 恒真条件：两侧等值字符串常量（'a'='a'）
// profile: sql

parser grammar string_tautology;

options { tokenVocab = SQLTokens; }

import SQLExpr;

pattern : l=STRING EQ r=STRING {stringsEqual($l, $r)}? ;
