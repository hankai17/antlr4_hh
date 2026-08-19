// EXISTS / NOT EXISTS 子查询结构检测。
rule exists_subquery {
    severity: MEDIUM
    action: ALLOW
    description: "EXISTS 子查询结构检测"
    pattern: UnaryExpr(op = "EXISTS")
    pattern: UnaryExpr(op = "NOT EXISTS")
}
