// ORDER BY 表达式结构检测；合法 SQL 常见，只告警。
rule order_by_expr {
    severity: LOW
    action: ALLOW
    description: "ORDER BY 表达式结构检测"
    pattern: OrderBy()
}
