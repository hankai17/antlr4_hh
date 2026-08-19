// 5. Numeric Expression（镜像 sqli_rules/5sqli_num.t）
// 结构特征：比较左侧是算术表达式（1+1=2 / 10-1=9），不做常量求值。
rule sqli_numeric {
    severity: LOW
    action: ALLOW
    description: "数值表达式比较（如 1+1=2）"
    pattern: BinaryExpr(op = "=", left = BinaryExpr())
}
