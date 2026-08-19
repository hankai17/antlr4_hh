// rule: boolean_injection
// severity: MEDIUM
// action: BLOCK
// description: 布尔型注入：OR/AND 一侧为常量比较
// profile: sql

parser grammar boolean_injection;

options { tokenVocab = SQLTokens; }

import SQLExpr;

// 两侧都是列比较（a=1 OR b=2）不会命中：至少一侧必须是"常量 = 常量"
// 结构检测不做等值求值（1=2 也算注入形状；恒真由 always_true 负责）
pattern
    : const_cmp (OR | AND) comparison
    | comparison (OR | AND) const_cmp
    ;

const_cmp
    : NUMBER EQ NUMBER
    | STRING EQ STRING
    ;
