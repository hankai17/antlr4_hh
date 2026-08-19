// SQLi：恒真条件（经典 OR/WHERE 1=1 注入的基础）
// 语义：BinaryExpr(op="=")，左右都是数值常量且相等。
rule always_true {
    severity: HIGH
    description: "恒真条件：WHERE 1=1"
    pattern: BinaryExpr(op = "=",
                        left = Constant(value = "1"),
                        right = Constant(value = "1"))
}
