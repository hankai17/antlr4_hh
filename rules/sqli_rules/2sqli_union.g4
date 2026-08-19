// 2. UNION SQL Injection（镜像 sqli_rules/2sqli_union.t）
rule sqli_union {
    severity: CRITICAL
    description: "UNION 联合查询注入"
    pattern: Query(union = true)
}
