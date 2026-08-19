// 14. EXISTS Injection（镜像 sqli_rules/14sqli_exists.t）
rule sqli_exists {
    severity: MEDIUM
    action: ALLOW
    description: "EXISTS 子查询结构检测"
    pattern: UnaryExpr(op = "EXISTS")
    pattern: UnaryExpr(op = "NOT EXISTS")
}
