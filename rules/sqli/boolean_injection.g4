// 布尔型注入：OR/AND 一侧连接"常量 = 常量"比较（... OR 1=1 注入形状）。
// 多个 pattern 为或（OR）；两侧都是列比较（a=1 OR b=2）不会命中。
rule boolean_injection {
    severity: MEDIUM
    description: "布尔型注入：OR/AND 一侧为常量比较"
    pattern: BinaryExpr(op = "OR", right = BinaryExpr(op = "=", left = Constant(), right = Constant()))
    pattern: BinaryExpr(op = "AND", right = BinaryExpr(op = "=", left = Constant(), right = Constant()))
    pattern: BinaryExpr(op = "OR", left = BinaryExpr(op = "=", left = Constant(), right = Constant()))
    pattern: BinaryExpr(op = "AND", left = BinaryExpr(op = "=", left = Constant(), right = Constant()))
}
