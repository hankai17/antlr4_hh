// 7. ORDER BY Injection（镜像 sqli_rules/7sqli_order_by.t）
// ORDER BY 表达式结构检测；合法 SQL 常见，只告警。
rule sqli_order_by {
    severity: LOW
    action: ALLOW
    description: "ORDER BY 表达式结构检测"
    pattern: OrderBy()
}
