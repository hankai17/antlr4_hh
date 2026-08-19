// SQLi：恒真条件（经典 OR/WHERE 1=1 注入的基础）
// 语义：BinaryExpr(op="=") 两侧都是数值常量，且常量值相等。
// 与具体字面量解耦：1=1、2=2、1=1.0 都会命中；id=1、1=2 不会误报。
rule always_true {
    severity: HIGH
    description: "恒真条件：两侧等值常量（1=1 / 2=2 / 1=1.0）"
    pattern: BinaryExpr(op = "=",
                        left = Constant(type = "NUMBER"),
                        right = Constant(type = "NUMBER"),
                        left.value = right.value)
}
