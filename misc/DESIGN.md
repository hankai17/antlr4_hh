# 编译型规则引擎设计

## 1. 目标

让**安全人员**只写 `.g4` 规则文件，就能把新的攻击检测能力编译成 C++ 插件并注入规则引擎，
全程**不需要修改、重新编译主引擎**。检测建立在**语义层**（AST）而不是字符串层：
规则描述"攻击长什么样"，而不是"攻击文本里有什么"。

```
安全人员
   |
   | 编写 .g4 规则文件（攻击模式 + 语义条件）
   v
Rule Compiler (rulec)
   |
   | 代码生成 + g++ -shared
   v
lib<rule>.so   <-------- 独立插件，dlopen 热加载
   |
   v
主引擎（不修改、不重编译）
```

## 2. 总体架构与数据流

```
HTTP Request
   |
   v
Normalization       解码 / 去注释 / 空白折叠 / 关键字混淆还原
   |
   v
Fast Path           廉价预筛（DFA 状态机 / 子串扫描）
   | 无命中 -> ALLOW（不进入重解析，性能关键路径）
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
Rule Engine         逐个 dlopen 插件执行 rule_check_text(归一化文本)
   |                 命中 BLOCK 规则 -> BLOCK
   v
ALLOW / BLOCK / UNKNOWN
```

分层职责：

| 层 | 负责什么 | 谁修改 |
|---|---|---|
| MiniSQL.g4 | 完整 SQL 判定（语法、方言） | 解析器维护者 |
| SQLTokens.g4 / RuleSQL.g4 | 规则共享词法 / 表达式语法 + 语义谓词 | 规则语法维护者 |
| 规则文件 `rules/**/*.g4` | 具体攻击检测语义 | **安全人员** |
| rulec | ANTLR 规则语法 -> 解析器 -> .so 编译 | 引擎维护者（安全人员无感） |

## 3. 关键设计原则

### 3.1 Grammar 与 Rule 分离

- `MiniSQL.g4`：只判定"是否完整可解析的 SQL"，不含任何安全语义。
- `SQLTokens.g4` / `RuleSQL.g4`：规则共享的词法与表达式语法。
- 规则文件（`rules/**/*.g4`）是**标准 ANTLR 语法**，用 token 与语义谓词描述攻击。

SQL 方言升级、新增 token 时只动共享语法；新增攻击规则只动 `rules/`，引擎零改动。

### 3.2 判定语义（无 AST 层）

规则匹配直接作用于归一化文本的 token 流，不经过 AST；
语义条件（如 `1=1` vs `1=2`）由规则语法里的 ANTLR 谓词直接表达。
verdict 规则：完整 SQL 或命中任意规则 → ALLOW；否则 UNKNOWN
（`--fail-closed` 可将 UNKNOWN 转 BLOCK）。

## 4. 规则语言（标准 ANTLR 语法）

### 4.1 语法

```
ruleDef    : RULE IDENT '{' property* patternDef '}'
property   : 'severity' ':' SEVERITY
           | 'action'   ':' ACTION
           | 'profile'  ':' PROFILE        // sql | raw
           | 'description' ':' STRING
patternDef : 'pattern' ':' nodePattern
nodePattern: IDENT '(' patternArgList? ')'
patternArg : IDENT '=' STRING
           | IDENT '=' BOOL
           | IDENT '=' nodePattern
           | IDENT '.' IDENT '=' IDENT '.' IDENT   // 属性路径等值
```

一条规则可以有多个 `patternDef`（`patternDef+`），语义为**或（OR）**，
例如 `boolean_injection` 用四个 pattern 覆盖 `OR/AND × 左/右分支` 四种形状。

### 4.2 模式语义

- `KindName(...)`：全树搜索 `kind == KindName` 的节点（隐式 any 语义）。
- `attr = "value"`：标量属性**相等**。
- `role = Pattern`：该语义角色子节点存在且递归匹配，如 `left = Constant(value = "1")`。
- `role.attr = role.attr`：**跨节点属性比较**，如 `left.value = right.value`
  表示"左子节点与右子节点的 value 属性相等"——把规则从"字面值绑定"
  升级为"语义条件"的关键谓词。
- `contains = "sub"`：特殊谓词，对 Text 节点 `value` 属性做子串包含（raw 画像）。
- 命中任一节点即算规则命中；规则引擎对整棵 AST 深度优先遍历。

数字字面量在 AST 构建时做了规范化（`1` / `1.0` / `1.00` -> `"1"`），
因此 `1 = 1.0` 与 `1 = 1` 是同一语义。

子查询 `Select` 节点带 `subquery=true` 属性（`(SELECT ...)`、`IN (SELECT ...)`、
`EXISTS (SELECT ...)` 等上下文），便于精确匹配子查询注入。

### 4.3 示例

`rules/sqli/sleep.g4`：

```
rule sleep {
    severity: CRITICAL
    description: "时间盲注：SLEEP()"
    pattern: FunctionCall(name = "sleep")
}
```

`rules/sqli/always_true.g4`（语义级恒真检测，`2=2` 不会误报）：

```
rule always_true {
    severity: HIGH
    description: "恒真条件：两侧等值常量（1=1 / 2=2 / 1=1.0）"
    pattern: BinaryExpr(op = "=",
                        left = Constant(type = "NUMBER"),
                        right = Constant(type = "NUMBER"),
                        left.value = right.value)
}
```

`left.value = right.value` 表达"两侧常量**语义相等**"：`1=1`、`2=2`、
`1=1.0` 命中；`id=1`、`1=2` 不命中。字符串变体同理
（`rules/sqli/string_tautology.g4`，`'a'='a'` 命中、`name='admin'` 不命中）。

### 4.4 规则即 ANTLR 语法（当前规则集）

`rules/` 下的攻击规则本身是**标准 ANTLR 语法文件**（parser grammar），
每条规则由 ANTLR 生成各自的 C++ 匹配器，rulec 编译成独立 `.so`：

```
rules/sqli/always_true.g4（ANTLR 语法 + 元数据注释）
   │ rulec：java 生成规则解析器（import RuleSQL）
   ▼
build/plugins/gen/always_true.{h,cpp} + wrapper
   │ g++ -shared
   ▼
libsqli_rules.so（text 模式：对归一化文本 token 流匹配）
```

- 共享词法 `SQLTokens.g4`：关键字映射、引号容错（字面量 vs 分隔引号）、未知字符跳过
- 共享表达式语法 `RuleSQL.g4`：expr/comparison/select_stmt 与语义谓词
  （isIdent / numbersEqual / stringsEqual），各规则 import 复用
- 规则元数据（name/severity/action/description/profile）写在头部注释，rulec 解析
- 引擎对 text 模式插件：归一化文本 → 共享词法 → 逐位置尝试 `pattern` 规则
- profile 门控：`fragment`/`raw` 仅非完整 SQL 输入生效（保留上下文区分能力）

> DSL 规则语言与 AST 语义匹配层已移除；规则集全部为标准 ANTLR 语法。

`rules/xss/script_tag.g4`（raw 画像，不经过 SQL 解析）：

```
// rule: script_tag
// severity: HIGH
// action: BLOCK
// description: XSS：<script> 标签
// profile: raw

parser grammar script_tag;

options { tokenVocab = SQLTokens; }

import RuleSQL;

pattern : LT i=IDENT {isIdent($i, "script")}? ;
```

## 5. 编译流水线（rulec）

```
rules/sqli/sleep.g4
   |
   | java 生成规则解析器（import RuleSQL / tokenVocab=SQLTokens）
   v
规则解析器 sleep.{h,cpp} + wrapper（rule_check_text）
   |
   | g++ -shared（共享词法 SQLTokens + 规则解析器 + wrapper）
   v
build/plugins/libsleep.so
```

插件导出 `rule_check_text(const char*)`：对归一化文本做共享词法 +
逐位置尝试 `pattern`（BailErrorStrategy）；命中即返回 true。
共享词法只生成一次（幂等），插件可独立分发、独立签名校验。

## 6. 插件 ABI 与热加载

每个 `.so` 导出三个 C 符号（`rule_plugin.h`）：

```cpp
 int       rule_abi();                       // 版本协商，不匹配拒绝加载
 int       rule_attack_count();              // 插件包含的攻击数量
 AttackInfo* rule_attack(int i);             // 第 i 个攻击元信息（name/severity/action/...）
 int       rule_check_text(const char* text, int* matched, int max);
                                             // 返回命中攻击索引数量（应用层可获取攻击类型）
```

主引擎 `dlopen(RTLD_NOW|RTLD_LOCAL)` + `dlsym` 加载；加载失败、符号缺失、
ABI 不匹配都有独立日志且**不会拖垮引擎**。因此：

- 新增规则 = 丢一个 `.g4` 进 `rules/`，`make plugins`，插件目录即热更新；
- 引擎代码零改动；规则与引擎通过 AST + ABI 解耦。

## 7. Fast Path 与 Deep Path 分层

ANTLR 适合复杂 CFG，但逐请求跑完整解析在高压下成本偏高。设计上分两层：

| 层 | 技术 | 成本 | 职责 |
|---|---|---|---|
| Fast Path | 状态机（DFA/正则编译） | O(n)，纳秒~微秒级 | 命中粗粒度攻击特征才放行到深检 |
| Deep Path | ANTLR SQL parser + AST + 规则插件 | 毫秒级 | 语义级判定，决定最终 ALLOW/BLOCK |

原型用子串扫描表（`union` / `sleep(` / `load_file` / `1=1` / `<script` ...）
实现 Fast Path；生产可升级为 DFA 状态机，并把特征表从规则文件自动生成
（规则与 fast-path 特征同源，避免漏配）。

## 8. 目录结构

```
.
├── MiniSQL.g4            # SQL 结构语法（解析层）
├── rule_plugin.h         # 插件 ABI 契约
├── rule_compiler.cc      # rulec：ANTLR 规则语法 -> 解析器 -> .so
├── engine.cc                # 主引擎：Normalization/FastPath/解析判定/RuleEngine
├── examples/call_plugin.c   # 最小动态库调用示例（纯 C）
├── rules/
│   ├── _shared/          # SQLTokens.g4 / RuleSQL.g4（规则共享词法与表达式语法）
│   ├── sqli/             # sqli_rules.g4（合并 24 条 SQLi 攻击，单插件）
│   └── xss/script_rules.g4 # XSS raw 规则
├── misc/                 # 设计文档、antlr jar、demo.sh、validate_sqli.sh
└── build/plugins/*.so    # 编译产物（热加载目录）
```

## 9. 使用流程（安全人员视角）

```bash
# 1. 写规则（无需碰 C++）
vi rules/sqli/benchmark.g4

# 2. 编译（rulec 自动生成 C++ 并出 .so；CMake 默认构建即含插件）
cmake --build build --target plugins

# 3. 引擎热加载生效（原型为每次请求扫描插件目录；生产可做成 inotify 热更）
./build/engine --rules build/plugins "SELECT BENCHMARK(1000000, MD5('x'))"
```

（构建：`cmake -S . -B build && cmake --build build -j`；产物 `build/engine`、
`build/rulec`、`build/plugins/*.so`。ANTLR 生成物不入库，构建时自动生成到
`build/gen/`（MiniSQL）与 `build/plugins/gen/`（规则解析器）；
改语法后重新 `cmake --build build` 即自动重新生成。）

## 10. 已实现原型 vs 生产化差距（Roadmap）

### 已实现
- 攻击规则为标准 ANTLR 语法，SQLi 24 条合并进单个 sqli_rules.g4（单插件），
  rulec 生成 C++ 匹配器；插件 ABI 返回命中攻击类型列表（名称/级别/动作/描述/profile）
- 共享规则语法：SQLTokens.g4（容错词法）+ RuleSQL.g4（表达式/语句 + 语义谓词）
- 语义谓词：isIdent / numbersEqual / stringsEqual（`1=1`、`2=2`、`1=1.0` 可命中）
- `validate` 校验目标（47 个正/负样本断言）
- 片段防护：共享词法容错 + 规则语法逐位置匹配，
  `1 OR 1=1` / `admin' OR '1'='1'` / `UNION SELECT` 片段均可命中规则
- 主引擎全流水线：Normalization -> Fast Path -> 解析判定 -> Rule Engine -> Verdict
- sql / fragment / raw 三画像门控 + fail-closed 选项

### 生产化差距
- **Normalization 升级**：URL 解码、charset 探测、等价字符（全角/零宽）、
  字符串字面量感知的注释剥离（当前是朴素实现）。
- **Fast Path 升级**：子串表替换为 DFA 状态机，特征与规则同源生成。
- **规则语法扩展**：ANTLR 谓词里做常量折叠（`1+1=2`、`0*1=0` 算术恒真）、
  跨 token 约束、规则依赖/优先级、白名单 action 语义。
- **AST 覆盖面**：JOIN 语义、CTE、`BENCHMARK` 等更多函数族、
  XSS 走 HTML parser（`html.g4` -> DOM AST），RCE 走 shell/表达式解析器。
- **生产级容错词法**：已实现基础容错（引号不平衡、未知字符跳过）；
  生产仍需 libinjection 级能力：charset/双重编码、嵌套引号、MySQL 注释变体等。
- **解析器合并（可选）**：MiniSQL.g4（完整判定）与规则语法（RuleSQL）可进一步
  统一，实现单一 SQL 语法。
- **插件治理**：插件签名校验（防投毒 .so）、沙箱/受限编译选项、
  插件元数据版本、性能预算（超时/调用次数上限）。
- **运行时形态**：常驻服务 + 请求上下文传递、规则热更（inotify）、
  匹配日志结构化输出、命中率/误报率统计。
- **引擎性能**：规则按首 token 建索引（只跑可能命中的插件）、并行规则求值。

## 11. 安全与健壮性考量

- **解析失败默认 UNKNOWN**：失败关闭（fail-closed）由部署策略决定；
  原型提供 `--fail-closed`，生产建议默认拦截并转人工复核。
- **插件隔离**：插件与引擎同进程，生产需对规则编译器做输入校验
  （rulec 只允许声明式模式，禁止任意代码注入——模式值统一走字符串转义）。
- **规则质量**：语义规则可读性好、误报面小（`2=2` 不误报即示例）；
  生产需要规则测试夹具（正/负样本回归）。
- 规则想直接 import MiniSQL 是不行的，除了 ANTLR 禁止 parser grammar import combined grammar 之外，即便拆开，两者的词法哲学（容错 vs 严格）和 token 集合（SQLTokens 有
  DROP/||/分号，MiniSQL 有 GROUP/CASE/JOIN）也天然不同——合并不了，只能让规则侧在 MiniSQL 的 parser 语法基础上做词汇表对齐。
  所以 不完整sql必须自定义lexer  minisql.g4是lexer/parser一体的
-               SQLTokens.g4                                                        lexer.l
  ━━━━━━━━━━  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━  ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
   工具链      ANTLR4（.g4 → C++）                                                 Flex/lex（.l → C）
  ──────────  ──────────────────────────────────────────────────────────────────  ──────────────────────────────────────────────────────────────────────────────────────────────────
   词法对象    SQL 文本（关键字、操作符、数字/字符串字面量）                       规则 DSL（export/action/%{...} 代码块、正则字符类、转义字符串）——不是 SQL
  ──────────  ──────────────────────────────────────────────────────────────────  ──────────────────────────────────────────────────────────────────────────────────────────────────
   容错设计    引号容错（字面量 vs 分隔引号）、未知字符跳过、关键字大小写不敏感    状态机严格处理（IN_PAREN/IN_BRACKET/IN_CODE 等 start condition，非法字符返回 INVALID_CHARACTER）
  ──────────  ──────────────────────────────────────────────────────────────────  ──────────────────────────────────────────────────────────────────────────────────────────────────
   结构        声明式 lexer 规则 + @lexer::members 谓词                            正则规则 + 内嵌 C++ action（return IDENT; 等）
  ──────────  ──────────────────────────────────────────────────────────────────  ──────────────────────────────────────────────────────────────────────────────────────────────────
   产出        token 流，供规则语法 tokenVocab 使用                                token 流，喂给 Bison/yacc 解析器（parser.hh）
  ──────────  ──────────────────────────────────────────────────────────────────  ──────────────────────────────────────────────────────────────────────────────────────────────────
   在本项目    在用：25 条规则全部经它分词，构建时自动生成                         废弃：无人引用


- SQLTokens.g4作为lexer 的输出是 RuleSQL.g4作为parser 的输入是吧 方向对，但有一个关键细节要修正：RuleSQL.g4 本身不会生成一个独立运行的 parser——它只是被每条规则 import 的“共享语法片段”，在生成每条规则的 parser 时被 ANTLR 合并进去
  SQLTokens.g4 生成词法器，把文本变成 token；RuleSQL.g4 是规则 parser 的共享零件，被合并进每条规则；规则 parser 消费 token 流匹配自己的 pattern。
