// rule: numeric_expr
// severity: LOW
// action: ALLOW
// description: 数值表达式比较（如 1+1=2）
// profile: sql

parser grammar numeric_expr;

options { tokenVocab = SQLTokens; }

import SQLExpr;

// 左侧必须是含运算符的算术（id=1 这种单操作数不命中）
pattern : arith EQ add_expr ;
arith : mul_expr (add_op mul_expr)+ ;
