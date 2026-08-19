// 1. Boolean-based SQL Injection（镜像 sqli_rules/1sqli_bool.t）
// 结构特征：OR/AND 一侧连接"常量 = 常量"比较（注入惯用形状 ... OR 1=1）。
// 多个 pattern = 或（OR）；a=1 OR b=2 两侧都是列比较，不会命中。
rule sqli_boolean {
    severity: MEDIUM
    description: "布尔型注入：OR/AND 一侧为常量比较"
    pattern: BinaryExpr(op = "OR", right = BinaryExpr(op = "=", left = Constant(), right = Constant()))
    pattern: BinaryExpr(op = "AND", right = BinaryExpr(op = "=", left = Constant(), right = Constant()))
    pattern: BinaryExpr(op = "OR", left = BinaryExpr(op = "=", left = Constant(), right = Constant()))
    pattern: BinaryExpr(op = "AND", left = BinaryExpr(op = "=", left = Constant(), right = Constant()))
}
