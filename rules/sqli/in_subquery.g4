// IN 子查询变体检测；IN (1,2,3) 普通列表合法，不检测。
rule in_subquery {
    severity: MEDIUM
    action: ALLOW
    description: "IN 子查询结构检测"
    pattern: BinaryExpr(op = "IN", right = Select(subquery = "true"))
    pattern: BinaryExpr(op = "NOT IN", right = Select(subquery = "true"))
}
