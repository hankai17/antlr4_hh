// DELETE FROM 语句片段（片段解析器产出 StmtDelete）。
rule delete_fragment {
    severity: MEDIUM
    action: ALLOW
    description: "DELETE FROM 语句片段"
    pattern: StmtDelete()
}
