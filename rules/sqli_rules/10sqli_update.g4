// 10. UPDATE Injection（镜像 sqli_rules/10sqli_update.t）
// 片段解析器产出 StmtUpdate 节点。
rule sqli_update {
    severity: MEDIUM
    action: ALLOW
    description: "UPDATE ... SET 语句片段"
    pattern: StmtUpdate()
}
