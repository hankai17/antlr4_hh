// UPDATE ... SET 语句片段（片段解析器产出 StmtUpdate）。
rule update_fragment {
    severity: MEDIUM
    action: ALLOW
    description: "UPDATE ... SET 语句片段"
    pattern: StmtUpdate()
}
