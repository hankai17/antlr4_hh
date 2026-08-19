#!/usr/bin/env bash
# ============================================================
# SQLi 规则校验器
# ------------------------------------------------------------
# 对每个样本运行 waf，断言：
#   BLOCK  <rule>  期望命中规则并拦截
#   ALLOW  <rule>  期望命中规则但放行（检测型规则）
#   UNKNOWN <rule> 期望命中规则但解析失败（fragment 检测）
#   NONE          期望无规则命中且 ALLOW（负样本）
#
# usage: validate_sqli.sh <waf_binary> <rules_dir>
# ============================================================
set -u

WAF="$1"
RULES="$2"
pass=0
fail=0

check() {
    local payload="$1" expect_verdict="$2" expect_rule="${3:-}"
    local out got ok=1
    out=$("$WAF" --rules "$RULES" "$payload" 2>&1)
    # 取最后一个判定词（VERDICT: xxx 或 FAST PATH ... -> ALLOW）
    got=$(printf '%s\n' "$out" | grep -Eo 'ALLOW|BLOCK|UNKNOWN' | tail -1)

    if [[ "$expect_rule" == "NONE" ]]; then
        if [[ "$got" != "ALLOW" ]]; then ok=0; fi
        if printf '%s\n' "$out" | grep -q '!! '; then ok=0; fi
    else
        if [[ "$got" != "$expect_verdict" ]]; then ok=0; fi
        if ! printf '%s\n' "$out" | grep -q "!! ${expect_rule}"; then ok=0; fi
    fi

    if [[ $ok == 1 ]]; then
        printf '[PASS] %-12s %s\n' "$expect_rule" "$payload"
        pass=$((pass + 1))
    else
        printf '[FAIL] %-12s %s   (verdict=%s, expect=%s)\n' \
            "$expect_rule" "$payload" "$got" "$expect_verdict"
        fail=$((fail + 1))
    fi
}

# ------------------------------------------------------------
# 正样本：BLOCK 型规则（高置信度，拦截）
# ------------------------------------------------------------
check "SELECT * FROM users WHERE 1=1"                    BLOCK   always_true
check "SELECT * FROM t WHERE a=1 OR 1=2"                 BLOCK   sqli_boolean
check "SELECT * FROM t WHERE a=1 AND 1=1"                BLOCK   sqli_boolean
check "SELECT * FROM t WHERE 2=2 OR b=3"                 BLOCK   sqli_boolean
check "SELECT id,name FROM users UNION SELECT user,password FROM admin" BLOCK sqli_union
check "1;SELECT * FROM users"                            BLOCK   sqli_stacked
check "1;DROP TABLE users"                               BLOCK   sqli_stacked
check "SELECT SLEEP(5)"                                  BLOCK   sleep
check "SELECT LOAD_FILE('/etc/passwd')"                  BLOCK   load_file
check "SELECT BENCHMARK(10000000, MD5('x'))"             BLOCK   benchmark
check "SELECT * FROM t WHERE 'a'='a'"                    BLOCK   string_tautology
check "GET /q?x=<script>alert(1)</script>"               BLOCK   script_tag

# ------------------------------------------------------------
# 正样本：检测型规则（命中但按 action 放行 / 解析失败）
# ------------------------------------------------------------
check "SELECT * FROM t WHERE id IN (SELECT id FROM s)"   ALLOW   sqli_subquery
check "SELECT * FROM t WHERE id IN (SELECT id FROM s)"   ALLOW   sqli_in
check "SELECT * FROM t WHERE EXISTS (SELECT 1 FROM s)"   ALLOW   sqli_exists
check "SELECT * FROM t WHERE NOT EXISTS (SELECT 1 FROM s)" ALLOW sqli_exists
check "SELECT * FROM t WHERE name LIKE '%x%'"            ALLOW   sqli_like
check "SELECT * FROM t WHERE id BETWEEN 1 AND 5"         ALLOW   sqli_between
check "SELECT * FROM t WHERE 1+1=2"                      ALLOW   sqli_numeric
check "SELECT * FROM t ORDER BY 1"                       ALLOW   sqli_order_by
check "SELECT * FROM t LIMIT 10"                         ALLOW   sqli_limit
check "SELECT * FROM t WHERE a='x' || 'y'"               ALLOW   sqli_strcat
check "INSERT INTO users VALUES (1)"                     ALLOW   sqli_insert
check "UPDATE users SET name='x'"                        ALLOW   sqli_update
check "DELETE FROM users"                                ALLOW   sqli_delete
check "x' UNION SELECT 1,2,3"                            BLOCK   sqli_union
check "foo SELECT a FROM b"                              ALLOW   sqli_select_from

# ------------------------------------------------------------
# 片段（不完整 SQL）正样本：包装进合法上下文后语义规则生效
# ------------------------------------------------------------
check "1 OR 1=1"                                         BLOCK   sqli_boolean
check "2=2"                                              BLOCK   always_true
check "'a'='a'"                                          BLOCK   string_tautology
check "UNION SELECT 1,2,3"                               BLOCK   sqli_union
check "ORDER BY 1"                                       ALLOW   sqli_order_by
check "LIMIT 1"                                          ALLOW   sqli_limit
check "EXISTS (SELECT 1 FROM s)"                         ALLOW   sqli_exists
check "x = (SELECT 1)"                                   ALLOW   sqli_subquery
check "admin' OR '1'='1' --"                             BLOCK   string_tautology

# ------------------------------------------------------------
# 负样本：不误报（ALLOW 且无任何规则命中）
# ------------------------------------------------------------
check "SELECT name FROM users WHERE id = 1"              ALLOW   NONE
check "SELECT 42"                                        ALLOW   NONE
check "SELECT * FROM t WHERE a = 1 AND b = 2"            ALLOW   NONE
check "hello world"                                      ALLOW   NONE
check "id=1"                                             ALLOW   NONE
check "abc"                                              ALLOW   NONE
check "age > 18"                                         ALLOW   NONE

# ------------------------------------------------------------
echo
echo "summary: $pass passed, $fail failed"
[[ $fail == 0 ]]
