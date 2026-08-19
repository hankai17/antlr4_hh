# 编译型 WAF 规则系统

一个"规则可编译、插件化、高性能、语义级检测"的 WAF 规则平台：
安全人员用 ANTLR 风格 `.g4` 写检测规则，`rulec` 编译器把规则编译成独立 C++ 插件（.so），
WAF 主引擎 `dlopen` 热加载插件，在**语义层（AST）**判定 ALLOW / BLOCK。
全程不需要修改、重新编译主引擎。

```
安全人员编写 .g4 规则文件
        |
        v
   Rule Compiler (rulec)  ── 代码生成 + g++ -shared ──>  lib<rule>_rule.so
        |
        v
   WAF 主引擎 dlopen 加载调用（不修改、不重编译）
```

## 整体架构与数据流

```
HTTP Request
   |
   v
Normalization       解码 / 去注释 / 空白折叠 / 关键字混淆还原
   |
   v
Fast Path           廉价预筛（DFA 状态机 / 子串扫描），无命中直接 ALLOW
   | 命中
   v
SQL Parser          ANTLR4 + MiniSQL.g4（完整 SQL 解析）
   | 解析失败
   v
Fragment Parser     容错词法 + 片段解析（引号不平衡也能产出 AST）
   |
   v
AST                 语义中间层（规则唯一可见的数据）
   |
   v
Rule Engine         逐个执行规则插件 waf_rule_check(ast)
   |
   v
ALLOW / BLOCK / UNKNOWN
```

## 核心设计原则

### Grammar 与 Rule 分离

- `MiniSQL.g4`：只负责解析 SQL 结构，不含任何安全语义。
- `Rule.g4`：规则文件的语言（声明式模式 DSL），供安全人员描述攻击。
- 规则文件只引用 AST 节点类型，不接触 SQL 文本——SQL 方言升级时规则不用改，
  新增规则也不动解析器。

### AST 作为中间层

解析树被 `AstBuilder`（ANTLR Listener）折叠成语义 AST，规则在语义层匹配：

```
WHERE 1=1
   |
   v
BinaryExpr {op="="}
   |-- Constant {type=NUMBER, value=1}    (named: left)
   |-- Constant {type=NUMBER, value=1}    (named: right)
```

因此 `WHERE 1=1`、`WHERE (1)=(1)`、`WHERE 1 /*x*/ = 1` 折叠后是同一棵树；
规则关心"语义"而非字符串，`2=2`、`1=1.0` 也能命中恒真检测，`id=1` 不误报。

### Fast Path 与 Deep Path 分层

| 层 | 技术 | 职责 |
|---|---|---|
| Fast Path | 状态机（DFA / 子串扫描） | O(n) 廉价预筛，无攻击特征直接 ALLOW |
| Deep Path | ANTLR SQL parser + AST + 规则插件 | 语义级判定，决定最终 ALLOW / BLOCK |

原型用子串特征表实现 Fast Path；生产可升级为 DFA 状态机，
并把 fast-path 特征与规则同源生成，避免漏配。

### 片段（不完整 SQL）防护

真实请求大多是参数值、注入后缀等**不完整 SQL**（如 `1 OR 1=1`、`admin' OR '1'='1'`、
`UNION SELECT 1,2,3`），完整解析必然失败。系统按四层递进处理：

1. **Fast Path**：无攻击特征直接 ALLOW（性能关键路径）
2. **完整解析**：能解析则直接跑语义规则
3. **容错片段解析**：解析失败时用容错词法器 + 片段解析器**直接构造 AST**
   （不塞进完整语句），引号不平衡（`admin'`）也能继续识别结构；
   所有节点带 `fragment="true"` 标记，现有语义规则原样复用
4. **raw 规则兜底**：连片段结构都识别不出时走文本特征（XSS 等）；再不行返回 UNKNOWN
   （生产建议 `--fail-closed` 转 BLOCK，不静默放行）

片段场景实测：

```bash
./build/waf "1 OR 1=1"              # BLOCK（容错片段解析后 sqli_boolean/always_true 命中）
./build/waf "2=2"                   # BLOCK（always_true）
./build/waf "UNION SELECT 1,2,3"    # BLOCK（sqli_union）
./build/waf "admin' OR '1'='1' --"  # BLOCK（容错词法后 string_tautology 命中）
./build/waf "id=1"                  # ALLOW（合法片段，无误报）
```

已知边界：生产环境仍需对 charset、双重编码、嵌套引号等做升级
（libinjection 级容错词法，见 DESIGN.md Roadmap）。

## 组件与职责

| 组件 | 文件 | 职责 |
|---|---|---|
| SQL 结构语法 | `MiniSQL.g4` | SQL 解析（SELECT / WHERE / IN / LIKE / BETWEEN / EXISTS / 子查询 …） |
| 规则语言 | `Rule.g4` | 声明式攻击模式 DSL（属性相等、跨节点比较、contains、多分支 pattern） |
| AST 中间层 | `ast.h` | 通用节点（kind/attrs/children/named），插件与引擎共享同一份头文件 |
| 解析树 → AST | `ast_builder.cc` | AND/OR 左结合折叠、子查询标记、数字规范化 |
| 规则编译器 | `rule_compiler.cc` | `.g4` → 生成 C++ → `g++ -shared` → `.so` |
| 插件 ABI | `rule_plugin.h` | `waf_rule_abi / waf_rule_info / waf_rule_check` |
| 主引擎 | `waf.cc` | Normalization → Fast Path → Parser → AST → Rule Engine → Verdict |
| 规则集 | `rules/` | `rules/sqli/`（拦截 + 检测合并集）+ `rules/xss/` |
| 校验逻辑 | `validate_sqli.sh` | 43 个正/负样本断言，验证规则不误报、不漏报 |

## 规则集

### 高置信度规则（`rules/sqli/`，命中即 BLOCK）

`always_true`（两侧等值常量：1=1 / 2=2 / 1=1.0）、`string_tautology`（'a'='a'）、
`union_select`、`sleep`、`load_file`、`benchmark`、`script_tag`（XSS，raw 画像）。

### 检测型规则（`rules/sqli/` 合并集）

除高置信度拦截规则外，`rules/sqli/` 还包含覆盖 SQLi 常见攻击形状的检测规则：
布尔注入、堆叠查询、子查询、EXISTS/IN 子查询、LIKE/BETWEEN/数值表达式、
字符串拼接（||）、ORDER BY/LIMIT、INSERT/UPDATE/DELETE/SELECT 语句片段。

分层策略：

- 高置信度（UNION、堆叠查询、布尔恒真形状、危险函数）→ `BLOCK`
- 中/低置信度结构特征（子查询、LIKE、BETWEEN、ORDER BY、LIMIT、`||`、
  INSERT/UPDATE/DELETE/SELECT 片段）→ `action: ALLOW` 只告警，避免误伤合法 SQL
- MiniSQL 解析不了的语句（INSERT/UPDATE/DELETE、堆叠、`||`）走 raw 文本层，
  且 raw 规则只在输入**不是完整 SQL** 时参与判定（fragment 检测语义）

## 规则语言速览

```g4
rule always_true {
    severity: HIGH
    description: "恒真条件：两侧等值常量（1=1 / 2=2 / 1=1.0）"
    pattern: BinaryExpr(op = "=",
                        left = Constant(type = "NUMBER"),
                        right = Constant(type = "NUMBER"),
                        left.value = right.value)
}
```

模式语义：

- `Kind(...)`：全树搜索该类型节点
- `attr = "value"`：标量属性相等
- `role = Pattern`：语义角色子节点递归匹配（如 `left = Constant(...)`）
- `left.value = right.value`：跨节点属性比较（语义条件，`2=2` / `1=1.0` 可命中）
- `contains = "s"`：文本包含（raw 画像）
- 一条规则多个 `pattern` = 或（OR）多分支

## 快速开始

```bash
cmake -S . -B build                 # 配置（默认 Release）
cmake --build build -j              # 构建 waf 引擎 + rulec 编译器 + 全部规则插件
cmake --build build --target demo   # 端到端演示（10 个样本）
cmake --build build --target validate  # 规则校验（42 个正/负样本断言）
```

手工检测：

```bash
./build/waf "SELECT * FROM users WHERE 1=1"                    # BLOCK: always_true
./build/waf "SELECT * FROM t WHERE a=1 OR 1=2"                 # BLOCK: sqli_boolean
./build/waf "SELECT id FROM a UNION SELECT pwd FROM admin"     # BLOCK: sqli_union
./build/waf "1;DROP TABLE users"                               # BLOCK: sqli_stacked
./build/waf "GET /q?x=<script>alert(1)</script>"               # BLOCK: script_tag
./build/waf "SELECT name FROM users WHERE id = 1"              # ALLOW（无规则命中）
./build/waf --fail-closed "hello union world"                  # 解析失败 -> BLOCK（默认 UNKNOWN）
```

### 新增一条规则（安全人员视角，不碰 C++）

```bash
vi rules/sqli/benchmark.g4
```

```g4
rule benchmark {
    severity: CRITICAL
    description: "性能消耗函数 BENCHMARK()"
    pattern: FunctionCall(name = "benchmark")
}
```

```bash
cmake --build build --target plugins
./build/waf "SELECT BENCHMARK(10000000, MD5('x'))"
```

## 验证结果

- demo 11 例：良性 SQL ALLOW、恒真/UNION/SLEEP/LOAD_FILE/BENCHMARK/XSS/堆叠均 BLOCK、
  片段（`1 OR 1=1` / `UNION SELECT` / `admin' OR '1'='1'`）BLOCK、非 SQL 请求 Fast Path 放行
- validate 43 例：SQLi 拦截/检测正例 + 危险函数/XSS 正例 + 片段正例全部命中；
  7 个负样本（`id=1`、`a=1 AND b=2`、`age > 18` 等）零误报

## 目录结构

```
├── MiniSQL.g4           # SQL 结构语法
├── Rule.g4              # 规则语言语法
├── ast.h                # AST 中间层（插件与引擎共享）
├── ast_builder.{h,cc}   # 解析树 -> 语义 AST
├── fragment_lexer.{h,cc}  # 容错词法器（不完整 SQL / 引号不平衡）
├── fragment_parser.{h,cc} # 片段解析器（直接构造 AST，无需包装）
├── rule_plugin.h        # 插件 ABI
├── rule_compiler.cc     # rulec：规则 -> C++ -> .so
├── waf.cc               # 主引擎
├── CMakeLists.txt       # 构建（waf / rulec / plugins / demo / validate / grammars）
├── demo.sh              # 端到端演示脚本
├── validate_sqli.sh     # 规则校验逻辑
├── rules/
│   ├── sqli/            # SQLi 规则合并集（拦截 + 检测）
│   └── xss/             # XSS raw 规则
└── build/plugins/       # 编译出的 .so（热加载目录）
```

## 设计文档与需求原文

- 完整设计（架构、规则语言、编译流水线、插件 ABI、Roadmap）：[DESIGN.md](DESIGN.md)
- 原始需求：[README](README)
