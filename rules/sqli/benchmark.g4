// SQLi：性能消耗型函数 BENCHMARK()
rule benchmark {
    severity: CRITICAL
    description: "性能消耗函数 BENCHMARK()"
    pattern: FunctionCall(name = "benchmark")
}
