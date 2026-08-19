// 11. DELETE Injection（镜像 sqli_rules/11sqli_delete.t）
// 片段解析器产出 StmtDelete 节点。
rule sqli_delete {
    severity: MEDIUM
    action: ALLOW
    description: "DELETE FROM 语句片段"
    pattern: StmtDelete()
}
