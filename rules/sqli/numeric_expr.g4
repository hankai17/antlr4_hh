// 数值表达式比较结构检测（如 1+1=2、10-1=9），不做常量求值。
rule numeric_expr {
    severity: LOW
    action: ALLOW
    description: "数值表达式比较（如 1+1=2）"
    pattern: BinaryExpr(op = "=", left = BinaryExpr())
}
