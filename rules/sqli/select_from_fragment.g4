// 非完整 SQL 上下文里的 SELECT ... FROM 片段。
rule select_from_fragment {
    severity: LOW
    action: ALLOW
    description: "SELECT ... FROM 片段"
    pattern: Select(fragment = "true", from = "true")
}
