// 17. IN Injection（镜像 sqli_rules/17sqli_in.t）
// 只对"IN 子查询"变体告警；IN (1,2,3) 普通列表合法，不检测。
rule sqli_in {
    severity: MEDIUM
    action: ALLOW
    description: "IN 子查询结构检测"
    pattern: BinaryExpr(op = "IN", right = Select(subquery = "true"))
    pattern: BinaryExpr(op = "NOT IN", right = Select(subquery = "true"))
}
