// BETWEEN / NOT BETWEEN 表达式结构检测。
rule between_expr {
    severity: LOW
    action: ALLOW
    description: "BETWEEN 表达式结构检测"
    pattern: BinaryExpr(op = "BETWEEN")
    pattern: BinaryExpr(op = "NOT BETWEEN")
}
