# 编译型规则引擎

一个"规则可编译、插件化、高性能、语义级检测"的 规则引擎平台：
安全人员用**标准 ANTLR 语法（.g4）**写攻击检测规则，`rulec` 编译器把每条规则
编译成独立的 C++ 匹配插件（.so），主引擎 `dlopen` 热加载，
在归一化文本的 token 流上逐位置匹配，判定 ALLOW / BLOCK / UNKNOWN。
全程不需要修改、重新编译主引擎。

```
安全人员编写标准 ANTLR 语法规则（.g4）
        |
        v
   Rule Compiler (rulec)  ── java 生成解析器 + g++ -shared ──>  lib<rule>_rule.so
        |
        v
   主引擎 dlopen 加载调用（不修改、不重编译）
```

## 整体架构与数据流

```
HTTP Request
   |
   v
Normalization       解码 / 去注释 / 空白折叠 / 关键字混淆还原
   |
   v
Fast Path           廉价预筛（子串扫描，生产可升级 DFA），无命中直接 ALLOW
   | 命中
   v
SQL Parser          ANTLR4 + MiniSQL.g4（判定"是否完整可解析的 SQL"）
   |
   v
Rule Engine         逐个执行规则插件 rule_check_text(归一化文本)
   |
   v
ALLOW / BLOCK / UNKNOWN
```

## 核心设计原则

### 规则即标准 ANTLR 语法

- `MiniSQL.g4`：只判定"是否完整可解析的 SQL"（fullSqlOk 门控 + UNKNOWN 判定），
  不含任何安全语义。
- `SQLTokens.g4` / `RuleSQL.g4`：规则共享的词法与表达式语法
  （位于 `rules/_shared/`），各规则 `import` 复用。
- 攻击规则（`rules/**/*.g4`）是**标准 ANTLR parser grammar**，只描述攻击形状，
  头部注释携带元数据，不依赖引擎实现。

### 判定语义（无 AST 层）

规则匹配直接作用于归一化文本的 token 流，不经过 AST；
语义条件（如 `1=1` vs `1=2`、函数名识别）由规则语法里的 **ANTLR 谓词**直接表达。

verdict 规则：

- 完整 SQL 或命中任意规则 → **ALLOW**
- 命中 BLOCK 规则 → **BLOCK**
- 两者都不满足 → **UNKNOWN**（`--fail-closed` 可转 BLOCK，不静默放行）

### Fast Path 与 Deep Path 分层

| 层 | 技术 | 职责 |
|---|---|---|
| Fast Path | 子串扫描（生产可升级 DFA 状态机） | O(n) 廉价预筛，无攻击特征直接 ALLOW |
| Deep Path | 共享词法 + 规则插件逐位置匹配 | 语义级判定，决定最终 ALLOW / BLOCK |

### 片段（不完整 SQL）防护

真实请求大多是参数值、注入后缀等**不完整 SQL**（如 `1 OR 1=1`、`admin' OR '1'='1'`、
`UNION SELECT 1,2,3`），完整解析必然失败。系统按四层递进处理：

1. **Fast Path**：无攻击特征直接 ALLOW（性能关键路径）
2. **完整解析**：能解析则直接进入规则判定
3. **规则匹配**：对所有规则在归一化文本 token 流上逐位置匹配（含语义谓词），
   引号不平衡（`admin'`）由共享词法容错处理
4. **UNKNOWN 兜底**：完整 SQL 与规则都不识别时返回 UNKNOWN

片段场景实测：

```bash
./build/engine "1 OR 1=1"              # BLOCK（always_true + boolean_injection）
./build/engine "2=2"                   # BLOCK（always_true）
./build/engine "UNION SELECT 1,2,3"    # BLOCK（union_select）
./build/engine "admin' OR '1'='1' --"  # BLOCK（string_tautology，引号容错）
./build/engine "id=1"                  # UNKNOWN（无法识别且无规则命中）
```

已知边界：生产环境仍需对 charset、双重编码、嵌套引号等做升级
（见 DESIGN.md Roadmap）。

## 组件与职责

| 组件 | 文件 | 职责 |
|---|---|---|
| 完整 SQL 判定 | `MiniSQL.g4` | fullSqlOk 门控（fragment/raw 画像）与 UNKNOWN 判定 |
| 共享规则语法 | `rules/_shared/` | `SQLTokens.g4`（词法）+ `RuleSQL.g4`（表达式/语句 + 语义谓词） |
| 规则编译器 | `rule_compiler.cc` | ANTLR 语法规则 → 生成解析器 → `g++ -shared` → `.so` |
| 插件 ABI | `rule_plugin.h` | `rule_abi / rule_attack_count / rule_attack / rule_check_text`（返回命中攻击类型） |
| 主引擎 | `engine.cc` | Normalization → Fast Path → 解析判定 → Rule Engine → Verdict |
| 规则集 | `rules/` | `rules/sqli/`（24 条）+ `rules/xss/`（1 条） |
| 校验逻辑 | `validate_sqli.sh` | 47 个正/负样本断言，验证规则不误报、不漏报 |

## 规则集

### 拦截型规则（命中即 BLOCK）

`always_true`（`1=1` / `2=2` / `1=1.0` 恒真）、`string_tautology`（`'a'='a'`）、
`boolean_injection`（OR/AND 一侧为常量比较）、`union_select`、`stacked_query`、
`sleep`、`load_file`、`benchmark`、`pg_sleep`、`script_tag`（XSS）。

### 检测型规则（`action: ALLOW` 只告警，避免误伤合法 SQL）

子查询、EXISTS/IN 子查询、LIKE、BETWEEN、数值表达式（`1+1=2`）、ORDER BY、LIMIT、
字符串拼接（`||`）、INSERT/UPDATE/DELETE/SELECT 语句片段、information_schema 枚举。

### profile 门控

- `sql`：始终参与匹配
- `fragment` / `raw`：仅在输入**不是完整 SQL** 时参与匹配
  （如 SELECT 片段规则不会误伤完整查询，XSS 只在非 SQL 输入生效）

## 规则写法（标准 ANTLR 语法）

```g4
// rule: always_true
// severity: HIGH
// action: BLOCK
// description: 恒真条件：两侧等值常量（1=1 / 2=2 / 1=1.0）
// profile: sql

parser grammar always_true;

options { tokenVocab = SQLTokens; }

import RuleSQL;

// 语义谓词 numbersEqual 做数值规范化比较：1=1、2=2、1=1.0 命中，1=2 不命中
pattern : l=NUMBER EQ r=NUMBER {numbersEqual($l, $r)}? ;
```

要点：

- 头部 `// rule: / severity: / action: / description: / profile:` 是规则元数据
- `pattern` 是匹配入口；引擎对归一化文本的 token 流逐位置尝试匹配
- 语义条件用 ANTLR 谓词表达（`isIdent` / `numbersEqual` / `stringsEqual` 等共享于 RuleSQL）
- 规则文件只依赖共享语法，与引擎实现解耦

## 快速开始

```bash
cmake -S . -B build                 # 配置（默认 Release）
cmake --build build -j              # 构建 engine + rulec + 全部规则插件（ANTLR 自动生成）
cmake --build build --target demo   # 端到端演示（11 个样本）
cmake --build build --target validate  # 规则校验（47 个正/负样本断言）
```

手工检测：

```bash
./build/engine "SELECT * FROM users WHERE 1=1"                    # BLOCK: always_true
./build/engine "SELECT * FROM t WHERE a=1 OR 1=2"                 # BLOCK: boolean_injection
./build/engine "SELECT id FROM a UNION SELECT pwd FROM admin"     # BLOCK: union_select
./build/engine "1;DROP TABLE users"                               # BLOCK: stacked_query
./build/engine "GET /q?x=<script>alert(1)</script>"               # BLOCK: script_tag
./build/engine "SELECT name FROM users WHERE id = 1"              # ALLOW（无规则命中）
./build/engine --fail-closed "hello union world"                  # 解析失败 -> BLOCK（默认 UNKNOWN）
```

### 新增一条攻击（安全人员视角，不碰 C++）

```bash
vi rules/sqli/sqli_rules.g4
```

```g4
// attack: benchmark
// severity: CRITICAL
// action: BLOCK
// description: 性能消耗函数 BENCHMARK()
// profile: sql

benchmark_pat : i=IDENT {isIdent($i, "benchmark")}? LPAREN expr_list? RPAREN ;
```

```bash
cmake --build build --target plugins
./build/engine "SELECT BENCHMARK(10000000, MD5('x'))"
```

## 验证结果

- demo 11 例：良性 SQL ALLOW；恒真 / UNION / SLEEP / LOAD_FILE / BENCHMARK / XSS /
  堆叠 / 片段（`1 OR 1=1`、`UNION SELECT`、`admin' OR '1'='1'`）均 BLOCK；
  非 SQL 良性请求 Fast Path 放行
- validate 47 例：拦截/检测正例 + 危险函数/XSS 正例 + 片段正例全部命中；
  7 个负样本（`id=1`、`a=1 AND b=2`、`age > 18` 等）零误报

## 目录结构

```
├── MiniSQL.g4           # 完整 SQL 判定语法（构建时自动生成解析器到 build/gen/）
├── rule_plugin.h        # 插件 ABI
├── rule_compiler.cc     # rulec：ANTLR 规则语法 -> 解析器 -> .so
├── engine.cc               # 主引擎
├── CMakeLists.txt       # 构建（含 ANTLR 自动生成，生成物不入库）
├── demo.sh              # 端到端演示脚本
├── validate_sqli.sh     # 规则校验逻辑
├── rules/
│   ├── _shared/         # SQLTokens.g4 / RuleSQL.g4（规则共享词法与匹配骨架）
│   ├── sqli/            # sqli_rules.g4（合并 24 条 SQLi 攻击，单插件）
│   └── xss/             # XSS 规则（raw 画像）
└── build/plugins/       # 编译出的 .so（热加载目录）
```

## 设计文档与需求原文

- 完整设计（架构、规则语法、编译流水线、插件 ABI、Roadmap）：[DESIGN.md](DESIGN.md)
- 原始需求：[README](README)
