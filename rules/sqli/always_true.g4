// rule: always_true
// severity: HIGH
// action: BLOCK
// description: 恒真条件：两侧等值常量（1=1 / 2=2 / 1=1.0）
// profile: sql

parser grammar always_true;

options { tokenVocab = SQLTokens; }

import RuleSQL;

// 语义谓词 numbersEqual 做数值规范化比较：1=1、2=2、1=1.0 都命中，1=2 不命中
pattern : l=NUMBER EQ r=NUMBER {numbersEqual($l, $r)}? ;
