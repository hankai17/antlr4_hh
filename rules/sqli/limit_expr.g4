// LIMIT 表达式结构检测。
rule limit_expr {
    severity: LOW
    action: ALLOW
    description: "LIMIT 表达式结构检测"
    pattern: Limit()
}
