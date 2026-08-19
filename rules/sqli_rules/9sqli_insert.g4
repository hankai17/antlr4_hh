// 9. INSERT Injection（镜像 sqli_rules/9sqli_insert.t）
// INSERT 语句由片段解析器产出 StmtInsert 节点做 AST 检测。
rule sqli_insert {
    severity: MEDIUM
    action: ALLOW
    description: "INSERT INTO 语句片段"
    pattern: StmtInsert()
}
