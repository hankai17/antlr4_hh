// SQLi：文件读取 LOAD_FILE()
rule load_file {
    severity: CRITICAL
    description: "文件读取：LOAD_FILE()"
    pattern: FunctionCall(name = "load_file")
}
