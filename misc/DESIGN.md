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

- SELECT id,name FROM users WHERE status='active' AND age>18 ORDER BY name LIMIT 10

## 12. 生成代码详解（rule_check_text / sqli_rules.cpp / ATN）

以下内容解释 rulec 生成的插件代码：`rule_check_text` 的匹配流程、为什么每次尝试
都新建 parser、`tokens.seek` 的真实语义、生成 parser 里的静态数据，以及
`sqli_rules.cpp` 整体结构与 ATN 机制。针对 `rules/sqli/sqli_rules.g4` 生成物
（`build/plugins/gen/sqli_rules.cpp`、`build/plugins/gen/sqli_rules_rule.cc`）讲解。

### 12.1 rule_check_text 生成代码

`rule_check_text` 是插件 `.so` 暴露的 C ABI 入口，由主引擎通过 `dlsym` 调用
（`engine.cc`）。它在 `rule_compiler.cc` 的 `generateWrapper()` 里按模板生成，
落到每个插件的 `*_rule.cc` 里。签名：

```c
int rule_check_text(const char* text, int* matched,
                    int* startOff, int* endOff, int max_matches)
```

一句话概括：**对一段归一化文本，在任意 token 位置尝试解析每个攻击子规则，
能完整解析出来就记一次命中，返回命中总数和每个命中的字符区间。**

逐步流程：

1. **词法分析**：`ANTLRInputStream input(text ? text : "")` 容忍空指针；
   `SQLTokens` 是插件间共享的 SQL 词法，`lexer.removeErrorListeners()` 关掉默认错误
   输出；`tokens.fill()` 一次性把全文切完。
2. **过滤可见 token**：遍历 token 流，只保留 `DEFAULT_CHANNEL` 上的 token，遇到 EOF
   停止。空白、注释这类隐藏通道 token 被剔除——注释里写 `SLEEP()` 不会误报，
   这也是输入叫"归一化文本"的原因之一。
3. **双重循环尝试匹配**：
   - 外层遍历每个可见 token 位置 `i`，把它当作候选起点；
   - 内层遍历每条攻击规则 `k`；
   - 两个快速跳过条件：`done[k]` 表示该规则已经命中过（**每条规则在整个输入里
     最多命中一次**）；`startsOk(k, t)` 是生成时的首 token 过滤——根据 `// start:`
     元数据，当前 token 类型根本不可能开启这条规则就直接跳过，这是性能优化；
   - `tokens.seek(visible[i]->getTokenIndex())` 把 token 流回退到候选起点，然后
     **新建一个解析器实例**（保证每个起点的解析状态是干净的），再通过
     `switch (k)` 调用对应的子规则，如 `parser.sleep_pat()`。
4. **命中判定**：调用完后检查 `parser.getNumberOfSyntaxErrors() != 0`。有语法错误
   说明从该起点不匹配这条规则，继续试下一个位置；没有错误就是完整匹配。
   当前模板是无异常控制流（没有 `BailErrorStrategy` / `try-catch`）。
5. **记录结果**：命中时写三件事——
   - `matched[count] = k`：命中规则的索引，引擎拿它去查 `rule_attack(k)` 的元信息
     （severity/action）；
   - `startOff[count]`：第一个 token 的字符起始偏移；
   - `endOff[count]`：最后一个被消费 token 的结束偏移（`getCurrentToken()` 是首个
     未消费的 token，所以取它前一个 token 的 `getStopIndex()`），区间含端点；
   - `count` 递增；外层循环条件 `count < max_matches` 保证不超过调用方给的结果数组长度。
6. **返回值**就是命中数量。引擎侧据此决定是否拦截——但 `rule_check_text` 本身不做
   拦截判断，只报告"结构命中了哪几条规则"，action 由引擎读 `AttackInfo` 决定。

两个容易踩坑的语义点：

- 命中位置不锚定：每条规则会在每个 token 起点都试，所以 `UNION SELECT` 藏在 SQL
  中间也能命中；
- `done` 数组意味着一个攻击类型只报告一次，即使文本里有三处 `SLEEP()`，也只返回
  一条 `sleep` 命中。

版本差异提醒：`build-release/plugins/gen/sqli_rules_rule.cc` 是**旧版 rulec 生成的**
——"规则在外层、位置在内层"的循环，用了 `BailErrorStrategy` + `try/catch`，也没有
`startsOk` 过滤；`build/plugins/gen/` 和当前源码模板才是新版结构（首 token 过滤 +
无异常 + `done` 数组）。对比文件看到差异是模板演进造成的，不是代码损坏。

### 12.2 为什么每次尝试都新建 parser

不是"每个 token 一个 parser"，而是**每个 token 起点 × 每条规则的一次尝试，各新建
一个 parser**（parser 在内层循环里构造）。最坏情况一个起点要建 n 个，只是
`startsOk` 会把大多数组合提前剪掉。

"临时对象"没问题，原因有三点：

1. **构造 parser 很便宜**。真正昂贵的东西——ATN（自动机表）和 DFA 预测缓存——是
   **静态共享**的（`OnceFlag` 全局只初始化一次），每次构造只是把 token 流、错误
   处理器、监听器接好，开销跟解析本身相比可忽略。
2. **复用反而危险**。Parser 持有大量随运行变化的状态：当前 token 索引、
   `_syntaxErrors` 计数、解析上下文栈、错误恢复状态、预测模拟器状态。命中判定依赖
   `getNumberOfSyntaxErrors() == 0`——复用一个 parser 时，前一次尝试留下的语法错误
   计数会**累积**，第二次解析即使成功也会被误判为失败。ANTLR 的 C++ 运行时虽然提供
   `Parser::reset()`（会清零 `_syntaxErrors`、seek 回 0、重置错误处理器），但
   "用完即弃"是最不容易出错的路：每次状态天然干净，不用操心漏复位哪个字段。
3. **临时对象的作用域刚好覆盖用途**。parser 只在当次尝试内用：`switch` 调用匹配规则
   → 查错误数 → 取 `getCurrentToken()` 算 endOff → 写入调用方数组。这些信息在作用域
   结束前全部提取完毕，随后析构清理，没有状态逃逸，也不会泄漏。

真正的性能开销不在"建对象"，而在**滑动窗口式重解析**：每个候选起点都要从该位置
重新跑一遍规则解析，这本质上是"在任意位置找模式"的代价。`startsOk`（首 token 过滤）
和 `done`（每条规则只报一次）就是用来把重试次数压到最低的。

### 12.3 tokens.seek 语义

`seek` 不是截取，只是**移动读指针**。运行时实现：

```cpp
// BufferedTokenStream.cpp
void BufferedTokenStream::seek(size_t index) {
  lazyInit();
  _p = adjustSeekIndex(index);   // 只是把内部游标 _p 指到 index
}
```

`_p` 是"下一个要读的 token 位置"。整个 token 缓冲 `_tokens` 一个都没删，seek 之前和
之后的 token 都还在里面。区别只在于：**parser 从 `_p` 开始往后读**，前面的 token
对它不可见（只是"不可见"，不是被移除）。效果上类似"从第 i 个 token 处截一段子串来
匹配"，但没有真正复制或截断数据。

另外，`CommonTokenStream::adjustSeekIndex` 实现为 `nextTokenOnChannel(i, channel)`：
seek 时自动跳到指定位置之后第一个在默认通道上的 token。生成代码传入的是 `visible[i]`
的 token 索引（本来就是默认通道的 token），所以通常就是它自己；如果传入的是隐藏通道
token（空白/注释），会顺延到下一个有效 token。

最后补充：parser 从 `_p` 开始读之后**不一定读到 EOF**——规则匹配完就停（比如
`sleep_pat` 匹配到 `SLEEP(...)` 结束，后面还有别的 SQL 也不影响）。剩余 token 留在
缓冲里，等下一次尝试时被另一个 parser 从另一个起点读取。

### 12.4 静态数据与 xxx_pat 执行体

`static` 不在 `xxx_pat()` 函数体里，而在生成 parser 文件**顶部和初始化函数里**
（`xxx_pat()` 本身是普通成员函数）：

```cpp
::antlr4::internal::OnceFlag sqli_rulesParserOnceFlag;          // 一次性初始化锁
static thread_local
std::unique_ptr<Sqli_rulesStaticData> sqli_rulesParserStaticData = nullptr;  // 共享静态数据
```

以及初始化函数里的 `static const int32_t serializedATNSegment[]`（一大段数字表）。

`sqli_rulesParserInitialize()` 只在 parser 第一次构造时执行一次（由 `call_once` 或
`thread_local` 保证），干四件事：

1. **组装词法/规则元数据**——把规则名表、字面量名表、符号名表存进
   `Sqli_rulesStaticData`，并据此构造 `Vocabulary`（token 类型 ↔ 名称的映射）。
2. **反序列化 ATN**——`serializedATNSegment` 是语法文件的"编译产物"，一个紧凑的整数
   表；`ATNDeserializer::deserialize()` 把它还原成真正的 `ATN` 对象。ANTLR 故意不
   生成几百行 `new State(...)` 代码，而是内嵌这张表，减小生成代码体积。
3. **预建 DFA 缓存**——对 ATN 里每个 decision（预测决策点）创建对应的 `DFA` 对象放进
   `decisionToDFA`。这些是**自适应预测**用的缓存：运行时遇到某个决策点，先查 DFA
   是否有缓存结果，没有才现算并写入。
4. **共享上下文缓存**——`sharedContextCache` 用于缓存预测期间共享的 ATN 上下文。

每个 parser 实例的构造函数做的是：

```cpp
sqli_rules::sqli_rules(TokenStream *input) : Parser(input) {
  sqli_rules::initialize();   // 确保上面的静态数据已就绪（只初始化一次）
  _interpreter = new atn::ParserATNSimulator(this, *sqli_rulesParserStaticData->atn,
        sqli_rulesParserStaticData->decisionToDFA,
        sqli_rulesParserStaticData->sharedContextCache, options);
}
```

即：**每个 parser 只新建自己的 `ParserATNSimulator`（预测模拟器），但 ATN、DFA 缓存、
上下文缓存全部指向同一份静态共享数据**。这就是"新建 parser 很便宜"的原因——贵的东西
建一次，全插件复用。

`xxx_pat()` 被调用时实际做的（普通运行时解析工作）：

1. `_tracker.createInstance<Sleep_patContext>(_ctx, getState())`——分配一个解析树节点
   （由 `_tracker` 统一登记，parser 销毁时统一回收）；
2. `enterRule(...)`——把规则压入调用栈、设置起始状态；
3. 按语法逐项执行：`match(IDENT)` 匹配 token、语义谓词 `isIdent($i, "sleep")`（大小写
   不敏感的标识符判断）、`match(LPAREN)`、可选的 `expr_list()`、`match(RPAREN)`；
4. 包在 `finally { exitRule(); }` 里，保证无论是否抛异常都正确退出规则；
5. 遇到 `RecognitionException` 就 `reportError` + `recover`——这会让 `_syntaxErrors`
   加 1，也就是 `rule_check_text` 判定"这条规则没匹配上"的依据。

分工总结：**静态部分是"语法本体的缓存"，一次性建好供所有 parser 共享；`xxx_pat()`
是"每次解析的执行体"，只消耗 token 流、产生错误计数，不碰静态数据**。
`rule_check_text` 甚至没用返回的解析树，只关心 `getNumberOfSyntaxErrors()` 和 token
位置。

### 12.5 sqli_rules.cpp 与 ATN

`sqli_rules.cpp` 是 ANTLR 4.13.2 从 `rules/sqli/sqli_rules.g4` 生成的 **parser 本体**
（24 条攻击规则、41 个语法规则）。它和三个文件配套：`sqli_rules.h`（声明）、
`SQLTokens.cpp`（共享词法）、`sqli_rules_rule.cc`（rulec 生成的 wrapper，
即 `rule_check_text` 所在）。

文件结构自上而下：

1. **匿名命名空间里的 `Sqli_rulesStaticData`**（`sqli_rules.cpp` 顶部）——一个"语法级"
   数据容器，全文件所有 parser 实例共享：`ruleNames`（41 条规则的名字表）、
   `literalNames` / `symbolicNames`（字面量与符号 token 名称表，合成 `vocabulary`）、
   `decisionToDFA`（每个预测决策点对应的 DFA 缓存）、`sharedContextCache`（预测上下文
   缓存）、`serializedATN` + `atn`（序列化 ATN 视图和反序列化后的真实 ATN 对象）。
2. **静态初始化**——`OnceFlag` + `thread_local` 的 `unique_ptr<Sqli_rulesStaticData>`，
   加上 `sqli_rulesParserInitialize()`。把 `serializedATNSegment[]` 交给
   `ATNDeserializer::deserialize()` 还原成 ATN 对象，再为 ATN 里每个决策点建一个 DFA
   放进 `decisionToDFA`。只在第一次构造 parser 时做一次。
3. **Parser 构造函数**——`initialize()` 保证静态数据就绪，然后
   `new atn::ParserATNSimulator(...)`；每个实例只新建自己的模拟器，ATN/DFA/缓存全部
   指向共享数据。后面还有 `getATN()`、`getRuleNames()`、`getVocabulary()` 等元数据
   访问器。
4. **Context 类群**——每个语法规则一个解析树节点类，提供访问器（如
   `Sleep_patContext` 上有 `IDENT()`、`LPAREN()`、`expr_list()`）。本项目 wrapper 没
   使用解析树，只用了错误计数和 token 位置。
5. **规则函数**——每次调用的执行体（见 12.4）。简单决策（如可选的 `expr_list?`）用
   生成器预计算的 **bitset 快速判断**：`(1ULL << _la) & 294717317185536`，即"下一个
   token 类型是否在能开启 `expr_list` 的集合里"，这是生成器对简单决策做的 LL(1) 静态
   优化；复杂决策走 ATN 自适应预测。
6. **Sempred 谓词函数**——`sleep_patSempred`、`constNumbersEqual`、`stringsEqual`
   等。`.g4` 里 `{...}?` 的谓词会同时出现在规则体内直接调用（解析时求值）和
   `Sempred` 函数（**预测阶段**也要能求值，因为选 alternative 可能依赖谓词）。
   `isIdent` 让 `Sleep(...)`、`sleep(...)`、`SLEEP(...)` 都能命中，这就是规则里写
   `IDENT` 而非小写字面量的原因。

**ATN（Augmented Transition Network）是 ANTLR 对整部语法的"编译产物"：一张带状态的
转移图。** 每个规则、每个 alternative、每个 token 匹配、每个子规则调用、每个循环都
映射成图里的状态和转移。对 sqli_rules 来说，这张图有 **396 个状态**（
`serializedATNSegment` 开头的 `4,1,55,396` 就是格式版本 4、语法类型 PARSER、
最大 token 类型 55、状态数 396）。

关键设计是**序列化**：ANTLR 不生成几百行 `new State()` 代码，而是把整张图压成一个
`int32_t` 数组，运行时由 `ATNDeserializer` 一次还原成对象。好处是生成文件小、加载快、
且同一份 ATN 被所有 parser 实例共享。

ATN 在运行时承担两个职责：

1. **语法识别（recognize）**：预测阶段确定走哪条路径后，规则函数按确定好的方案依次
   `match`，驱动 token 流前进。
2. **ALL(\*) 自适应预测（prediction）**：这是 ANTLR 4 相对 LL(k) 的核心改进。遇到决策
   点时，`ParserATNSimulator` 在 ATN 图上做**图遍历 + 试探性消费 token**，动态决定需要
   多少 lookahead，而不是固定看 k 个 token。预测结果会**缓存进该决策点的 DFA**：下次
   遇到相同的 token 序列直接查表，免去重走 ATN。

ATN 和 DFA 的关系：

- **ATN = 语法蓝图**：完整、静态、描述"语言长什么样"；
- **DFA = 运行时的预测缓存**：每个决策点一个，记录"这些 token 来了 → 选这条分支"，
  随着解析不断学习变厚。

这套机制适合当 WAF 规则引擎的原因：ANTLR 的 parser 允许**从任意规则作为起始规则**
解析（不强制从根规则开始），这正是 wrapper 能对每个 token 起点调用 `parser.sleep_pat()`
等碎片规则的原因；配合 ATN 的按需预测，从任意位置开始的子串匹配在语法层面就是合法的。
而命中与否完全由"该规则是否无错解析完"决定，不依赖解析树——所以生成代码才能只留下
`getNumberOfSyntaxErrors()` 和 token 偏移这两样东西给 `rule_check_text` 用。
