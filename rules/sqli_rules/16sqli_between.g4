// 16. BETWEEN Injection（镜像 sqli_rules/16sqli_between.t）
rule sqli_between {
    severity: LOW
    action: ALLOW
    description: "BETWEEN 表达式结构检测"
    pattern: BinaryExpr(op = "BETWEEN")
    pattern: BinaryExpr(op = "NOT BETWEEN")
}
