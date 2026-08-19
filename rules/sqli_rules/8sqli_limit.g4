// 8. LIMIT Injection（镜像 sqli_rules/8sqli_limit.t）
rule sqli_limit {
    severity: LOW
    action: ALLOW
    description: "LIMIT 表达式结构检测"
    pattern: Limit()
}
