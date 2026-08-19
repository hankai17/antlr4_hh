// 12. SELECT Fragment（镜像 sqli_rules/12sqli_select.t）
// 非完整 SQL 上下文里出现 SELECT 片段（片段解析器产出的 Select 带 fragment 标记；
// 完整查询的 Select 不带该标记，不会被误伤）。
rule sqli_select {
    severity: LOW
    action: ALLOW
    description: "SELECT 片段"
    pattern: Select(fragment = "true")
}
