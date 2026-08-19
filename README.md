# 编译型 WAF 规则系统

安全人员用 ANTLR 风格 `.g4` 写检测规则 → `rulec` 编译成独立 C++ 插件（.so）→
WAF 主引擎 `dlopen` 热加载，在**语义层（AST）**判定 ALLOW / BLOCK。

```
HTTP payload
  -> Normalization         解码 / 去注释 / 空白折叠
  -> Fast Path             廉价预筛（原型：子串表；生产：yanshi DFA）
  -> MiniSQL Parser        ANTLR4（SQL.g4）
  -> AST                   语义中间层（规则唯一可见数据）
  -> Rule Engine           逐个执行规则插件 waf_rule_check(ast)
  -> ALLOW / BLOCK / UNKNOWN
```

设计文档见 [DESIGN.md](DESIGN.md)，需求原文见 [README](README)。

## 快速开始

```bash
make          # 构建 waf 引擎 + rulec 编译器 + 全部规则插件
make demo     # 端到端演示（良性 / SQLi / XSS）
```

手工检测：

```bash
./waf "SELECT * FROM users WHERE 1=1"                    # BLOCK: always_true
./waf "SELECT SLEEP(5)"                                  # BLOCK: sleep
./waf "SELECT id FROM a UNION SELECT pwd FROM admin"     # BLOCK: union_select
./waf "GET /q?x=<script>alert(1)</script>"               # BLOCK: script_tag（raw）
./waf "SELECT name FROM users WHERE id = 1"              # ALLOW
./waf --fail-closed "hello union world"                  # 解析失败 -> BLOCK（默认 UNKNOWN）
```

## 新增一条规则（安全人员视角，不碰 C++）

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
make plugins
./waf --rules build/plugins "SELECT BENCHMARK(10000000, MD5('x'))"
```

## 目录结构

```
├── MiniSQL.g4           # SQL 结构语法
├── Rule.g4              # 规则语言语法
├── ast.h                # AST 中间层（插件与引擎共享）
├── ast_builder.{h,cc}   # 解析树 -> 语义 AST
├── rule_plugin.h        # 插件 ABI
├── rule_compiler.cc     # rulec：规则 -> C++ -> .so
├── waf.cc               # 主引擎
├── rules/               # 规则源文件（sqli/ xss/）
└── build/plugins/       # 编译出的 .so（热加载目录）
```

## 规则语言速览

```g4
rule always_true {
    severity: HIGH
    description: "恒真条件：WHERE 1=1"
    pattern: BinaryExpr(op = "=",
                        left = Constant(value = "1"),
                        right = Constant(value = "1"))
}
```

模式语义：`Kind(...)` 全树搜索；`attr = "value"` 属性相等；
`role = Pattern` 语义角色递归匹配；`contains = "s"` 文本包含（raw 画像）。
