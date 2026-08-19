// 4. String Concatenation（镜像 sqli_rules/4sqli_strcat.t）
// SQLite 字符串拼接 ||；MiniSQL 完整语法不支持 ||，由片段解析器
// 产出 BinaryExpr(op="||") 后在 AST 层检测。
// || 本身可能是合法文本，LOW + 只告警。
rule sqli_strcat {
    severity: LOW
    action: ALLOW
    description: "字符串拼接特征 ||"
    pattern: BinaryExpr(op = "||")
}
