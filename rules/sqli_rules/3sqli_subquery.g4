// 3. Subquery Injection（镜像 sqli_rules/3sqli_subq.t）
// 子查询结构检测（(SELECT ...) / EXISTS (SELECT ...) / IN (SELECT ...)）。
// 子查询本身是合法 SQL，默认只告警不拦截（action: ALLOW）。
rule sqli_subquery {
    severity: MEDIUM
    action: ALLOW
    description: "子查询结构检测"
    pattern: Select(subquery = "true")
}
