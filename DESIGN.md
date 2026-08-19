# 编译型 WAF 规则系统设计

## 1. 目标

让**安全人员**只写 `.g4` 规则文件，就能把新的攻击检测能力编译成 C++ 插件并注入 WAF，
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
lib<rule>_rule.so   <-------- 独立插件，dlopen 热加载
   |
   v
WAF 主引擎（不修改、不重编译）
```

## 2. 总体架构与数据流

```
HTTP Request
   |
   v
Normalization       解码 / 去注释 / 空白折叠 / 关键字混淆还原
   |
   v
Fast Path           廉价预筛（yanshi 状态机 / 子串扫描）
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
Rule Engine         逐个 dlopen 插件执行 waf_rule_check(ast)
   |                 命中 BLOCK 规则 -> BLOCK
   v
ALLOW / BLOCK / UNKNOWN
```

分层职责：

| 层 | 负责什么 | 谁修改 |
|---|---|---|
| MiniSQL.g4 | SQL 结构解析（语法、方言） | 解析器维护者 |
| Rule.g4 | 规则语言（攻击模式 DSL） | 规则语言维护者 |
| AST builder | 解析树 -> 语义 AST 折叠 | 引擎维护者 |
| 规则文件 `rules/**/*.g4` | 具体攻击检测语义 | **安全人员** |
| rulec | 规则 -> C++ -> .so 编译 | 引擎维护者（安全人员无感） |

## 3. 关键设计原则

### 3.1 Grammar 与 Rule 分离

- `MiniSQL.g4`：只回答"这段 SQL 的结构是什么"，不含任何安全语义。
- `Rule.g4`：定义规则文件的语法，让安全人员用声明式模式描述攻击。
- 规则文件（`rules/**/*.g4`）只引用 **AST 节点类型**，不引用 SQL 文本。

这样 SQL 方言升级、新增语法时，规则不需要跟着改；反之新增规则也不动解析器。

### 3.2 AST 作为中间层

解析树（parse tree）是语法细节的忠实投影（括号、优先级分层、中间规则），不适合直接做语义匹配。
`AstBuilder`（一个 ANTLR Listener）把解析树折叠成紧凑的语义 AST：

```
WHERE 1=1
   |
   v
BinaryExpr {op="="}
   |-- Constant {type=NUMBER, value=1}    (named: left)
   |-- Constant {type=NUMBER, value=1}    (named: right)
```

规则不关心字符串，只关心语义；因此 `WHERE 1=1`、`WHERE (1)=(1)`、
`WHERE 1 /*x*/ = 1` 折叠后是同一棵树。

### 3.3 AST 节点模型（通用结构）

`ast.h` 定义了一个与 SQL 方言无关的通用节点，主引擎与插件共享这一份头文件：

```cpp
struct AstNode {
    std::string kind;                         // "Query" / "Select" / "BinaryExpr" / ...
    std::map<std::string, std::string> attrs; // op、value、name、union、star ...
    std::vector<std::unique_ptr<AstNode>> children;   // 有序子节点
    std::map<std::string, AstNode*> named;    // 语义角色：left/right/operand/low/high
};
```

当前原型支持的节点：

| kind | 关键 attrs | 语义角色 |
|---|---|---|
| Query | union=true | - |
| Select | star="\*", distinct=true | - |
| SelectItem | - | - |
| From / Where / GroupBy / Having / OrderBy / Limit | - | - |
| TableRef | name, alias | - |
| BinaryExpr | op（`=` `AND` `OR` `IN` `LIKE` `BETWEEN` `+` `-` ...） | left, right（low/high for BETWEEN） |
| UnaryExpr | op（`NOT` `IS NULL` `EXISTS` `-` ...） | operand |
| Constant | type（NUMBER/STRING/NULL/BOOL）, value | - |
| ColumnRef | name, table, schema | - |
| FunctionCall | name（小写化） | - |
| List / CaseExpr / WhenClause / OrderItem | - | - |
| Text（raw 画像专用） | value（归一化全文）, raw | - |

## 4. 规则语言（Rule.g4）

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
对应 yanshi 规则文件里的多分支 export（如 `1sqli_boolean` 覆盖
`OR/AND × 左/右分支` 四种形状）。

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

`rules/xss/script_tag.g4`（raw 画像，不经过 SQL 解析）：

```
rule script_tag {
    severity: HIGH
    profile: raw
    description: "XSS：<script> 标签"
    pattern: Text(contains = "<script")
}
```

## 5. 编译流水线（rulec）

```
rules/sqli/sleep.g4
   |
   | Rule.g4 parser（ANTLR）
   v
规则 AST（name / severity / pattern 树）
   |
   | C++ 代码生成（纯字符串拼接，无模板元编程）
   v
build/plugins/sleep_rule.cc
   |
   | g++ -std=c++17 -O2 -fPIC -shared
   v
build/plugins/libsleep_rule.so
```

生成代码要点：每个模式节点对应一个 `static bool mN(const AstNode&)`，
嵌套模式递归调用，`waf_rule_check` 用 `waf::matchAny` 做全树 DFS。
生成的插件**只依赖 `ast.h` / `rule_plugin.h`**，不链接 ANTLR 运行时——
插件可以独立分发、独立签名校验。

## 6. 插件 ABI 与热加载

每个 `.so` 导出三个 C 符号（`rule_plugin.h`）：

```cpp
int       waf_rule_abi();                       // 版本协商，不匹配拒绝加载
RuleInfo* waf_rule_info();                      // name / severity / action / description / profile
bool      waf_rule_check(const AstNode& root);  // 语义匹配
```

主引擎 `dlopen(RTLD_NOW|RTLD_LOCAL)` + `dlsym` 加载；加载失败、符号缺失、
ABI 不匹配都有独立日志且**不会拖垮引擎**。因此：

- 新增规则 = 丢一个 `.g4` 进 `rules/`，`make plugins`，插件目录即热更新；
- 引擎代码零改动；规则与引擎通过 AST + ABI 解耦。

## 7. Fast Path：ANTLR 与 yanshi 的分工

ANTLR 适合复杂 CFG，但逐请求跑完整解析在高压下成本偏高。设计上分两层：

| 层 | 技术 | 成本 | 职责 |
|---|---|---|---|
| Fast Path | yanshi 状态机（DFA/正则编译） | O(n)，纳秒~微秒级 | 命中粗粒度攻击特征才放行到深检 |
| Deep Path | ANTLR SQL parser + AST + 规则插件 | 毫秒级 | 语义级判定，决定最终 ALLOW/BLOCK |

原型用子串扫描表（`union` / `sleep(` / `load_file` / `1=1` / `<script` ...）
模拟 yanshi 层；生产替换为 yanshi 编译出的 DFA，并把特征表从规则文件自动生成
（规则与 fast-path 特征同源，避免漏配）。

## 8. 目录结构

```
.
├── MiniSQL.g4            # SQL 结构语法（解析层）
├── Rule.g4               # 规则语言语法（规则层）
├── ast.h                 # AST 中间层（header-only，插件共享）
├── ast_builder.{h,cc}    # 解析树 -> 语义 AST
├── rule_plugin.h         # 插件 ABI 契约
├── rule_compiler.cc      # rulec：规则 -> C++ -> .so
├── waf.cc                # 主引擎：Normalization/FastPath/Parser/AST/RuleEngine
├── rules/
│   ├── sqli/always_true.g4  union_select.g4  sleep.g4  load_file.g4
│   ├── sqli_rules/1sqli_boolean.g4 ... 17sqli_in.g4   # 镜像 yanshi 17 类 SQLi
│   └── xss/script_tag.g4
├── validate_sqli.sh      # 规则校验逻辑（正/负样本断言）
└── build/plugins/*.so    # 编译产物（热加载目录）
```

## 9. 使用流程（安全人员视角）

```bash
# 1. 写规则（无需碰 C++）
vi rules/sqli/benchmark.g4

# 2. 编译（rulec 自动生成 C++ 并出 .so；CMake 默认构建即含插件）
cmake --build build --target plugins

# 3. 引擎热加载生效（原型为每次请求扫描插件目录；生产可做成 inotify 热更）
./build/waf --rules build/plugins "SELECT BENCHMARK(1000000, MD5('x'))"
```

（构建：`cmake -S . -B build && cmake --build build -j`；产物 `build/waf`、
`build/rulec`、`build/plugins/*.so`。语法变更后用
`cmake --build build --target grammars` 重新生成 ANTLR 解析器。）

## 10. 已实现原型 vs 生产化差距（Roadmap）

### 已实现
- SQL -> AST 语义折叠（AND/OR 左结合、比较/IN/LIKE/BETWEEN/IS NULL/EXISTS、函数、CASE、子查询）
- Rule.g4 规则语言 + rulec 编译器 + 独立 .so 插件
- 语义谓词：属性路径等值（`left.value = right.value`）、数字字面量规范化
- 一条规则多 pattern（OR 分支）、子查询标记（`subquery=true`）、EXISTS 独立表达式
- 镜像 yanshi sqli_rules 的 17 类 SQLi 规则 + `validate` 校验目标（43 个样本断言）
- 片段防护：容错词法 + 片段解析器直接构造 AST（不塞完整语句），
  `1 OR 1=1` / `admin' OR '1'='1'` / `UNION SELECT` 片段均可命中语义规则
- 主引擎全流水线：Normalization -> Fast Path -> Parser -> AST -> Rule Engine -> Verdict
- sql / raw 双画像（SQLi 语义检测 + XSS 文本检测）
- ABI 协商、加载容错、fail-closed 选项、AST 调试输出

### 生产化差距
- **Normalization 升级**：URL 解码、charset 探测、等价字符（全角/零宽）、
  字符串字面量感知的注释剥离（当前是朴素实现）。
- **yanshi fast path**：子串表替换为 DFA 状态机，特征与规则同源生成。
- **规则语言扩展**：`regex`、`not`、`count`（如至少 N 个危险函数）、
  跨节点约束（如 `BinaryExpr(op=OR)` 下同时出现两个恒真项）、
  白名单 action 语义、规则依赖/优先级；**常量折叠**（`1+1=2`、`0*1=0`
  等算术恒真需在 AST 层做常量表达式求值，当前是已知缺口）。
- **AST 覆盖面**：JOIN 语义、CTE、`BENCHMARK` 等更多函数族、
  XSS 走 HTML parser（`html.g4` -> DOM AST），RCE 走 shell/表达式解析器。
- **生产级容错词法**：已实现基础容错（引号不平衡、未知字符跳过）；
  生产仍需 libinjection 级能力：charset/双重编码、嵌套引号、MySQL 注释变体等。
- **插件治理**：插件签名校验（防投毒 .so）、沙箱/受限编译选项、
  插件元数据版本、性能预算（超时/调用次数上限）。
- **运行时形态**：常驻服务 + 请求上下文传递、规则热更（inotify）、
  匹配日志结构化输出、命中率/误报率统计。
- **引擎性能**：AST 节点对象池、规则按 AST 节点类型索引（只跑可能命中的插件）、
  并行规则求值。

## 11. 安全与健壮性考量

- **解析失败默认 UNKNOWN**：失败关闭（fail-closed）由部署策略决定；
  原型提供 `--fail-closed`，生产建议默认拦截并转人工复核。
- **插件隔离**：插件与引擎同进程，生产需对规则编译器做输入校验
  （rulec 只允许声明式模式，禁止任意代码注入——模式值统一走字符串转义）。
- **规则质量**：语义规则可读性好、误报面小（`2=2` 不误报即示例）；
  生产需要规则测试夹具（正/负样本回归）。
