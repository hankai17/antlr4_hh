// SQLi：时间盲注 SLEEP()
rule sleep {
    severity: CRITICAL
    description: "时间盲注：SLEEP()"
    pattern: FunctionCall(name = "sleep")
}
