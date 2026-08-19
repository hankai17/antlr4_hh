// SQLi：恒真条件（字符串常量变体）
// 语义：BinaryExpr(op="=") 两侧都是字符串常量且值相等（'a'='a'）。
rule string_tautology {
    severity: HIGH
    description: "恒真条件：两侧等值字符串常量（'a'='a'）"
    pattern: BinaryExpr(op = "=",
                        left = Constant(type = "STRING"),
                        right = Constant(type = "STRING"),
                        left.value = right.value)
}
