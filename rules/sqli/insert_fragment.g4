// INSERT INTO 语句片段（MiniSQL 不解析 INSERT，由片段解析器产出 StmtInsert）。
rule insert_fragment {
    severity: MEDIUM
    action: ALLOW
    description: "INSERT INTO 语句片段"
    pattern: StmtInsert()
}
