// 13. SELECT + FROM Fragment（镜像 sqli_rules/13sqli_select_from.t）
// 片段解析器产出的 Select 带 fragment + from 标记。
rule sqli_select_from {
    severity: LOW
    action: ALLOW
    description: "SELECT ... FROM 片段"
    pattern: Select(fragment = "true", from = "true")
}
