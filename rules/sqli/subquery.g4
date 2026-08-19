// 子查询结构检测：(SELECT ...) / EXISTS (SELECT ...) / IN (SELECT ...)。
// 子查询本身是合法 SQL，默认只告警不拦截（action: ALLOW）。
rule subquery {
    severity: MEDIUM
    action: ALLOW
    description: "子查询结构检测"
    pattern: Select(subquery = "true")
}
