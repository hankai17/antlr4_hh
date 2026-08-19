// LIKE / NOT LIKE 表达式结构检测。
rule like_expr {
    severity: LOW
    action: ALLOW
    description: "LIKE 表达式结构检测"
    pattern: BinaryExpr(op = "LIKE")
    pattern: BinaryExpr(op = "NOT LIKE")
}
