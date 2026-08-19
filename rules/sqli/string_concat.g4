// 字符串拼接 ||：片段解析器产出 BinaryExpr(op="||")。
// || 本身可能是合法文本，LOW + 只告警。
rule string_concat {
    severity: LOW
    action: ALLOW
    description: "字符串拼接特征 ||"
    pattern: BinaryExpr(op = "||")
}
