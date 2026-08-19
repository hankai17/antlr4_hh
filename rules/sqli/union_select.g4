// SQLi：UNION SELECT 联合查询注入
rule union_select {
    severity: CRITICAL
    description: "UNION SELECT 联合查询"
    pattern: Query(union = true)
}
