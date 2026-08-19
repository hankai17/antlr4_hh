// 15. LIKE Injection（镜像 sqli_rules/15sqli_like.t）
rule sqli_like {
    severity: LOW
    action: ALLOW
    description: "LIKE 表达式结构检测"
    pattern: BinaryExpr(op = "LIKE")
    pattern: BinaryExpr(op = "NOT LIKE")
}
