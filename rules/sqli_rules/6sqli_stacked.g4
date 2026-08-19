// 6. Stacked Query（镜像 sqli_rules/6sqli_stacked.t）
// 分号后跟 SQL 关键字 -> 片段解析器产出 Stacked 节点。
// 只检测"分号 + 关键字"，不单独检测分号，降低误报。
rule sqli_stacked {
    severity: CRITICAL
    description: "堆叠查询：; 后跟 SQL 关键字"
    pattern: Stacked()
}
