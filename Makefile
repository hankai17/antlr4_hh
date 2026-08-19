# ============================================================
# 编译型 WAF 规则系统构建
# ------------------------------------------------------------
#   make          # 构建 waf 引擎 + rulec 编译器 + 全部规则插件
#   make demo     # 端到端演示（良性 / SQLi / XSS 样本）
#   make clean    # 清理产物
#
# 规则编译流水线：
#   rules/<cat>/<name>.g4
#     -> rulec（Rule.g4 解析 + C++ 代码生成）
#     -> build/plugins/lib<name>_rule.so（独立插件，dlopen 加载）
# ============================================================

ANTLR_JAR  := antlr-4.13.2-complete.jar
ANTLR_RT   := /root/CLionProjects/antlr4-4.13.2/runtime/Cpp
ANTLR_INC  := $(ANTLR_RT)/runtime/src
ANTLR_LIB  := $(ANTLR_RT)/build/runtime

CXX        := g++
CXXFLAGS   := -std=c++17 -O2 -Wall -Wextra -I$(ANTLR_INC) -I.
LDLIBS     := -L$(ANTLR_LIB) -lantlr4-runtime -Wl,-rpath,$(ANTLR_LIB)

MINISQL_SRC := MiniSQLLexer.cpp MiniSQLParser.cpp MiniSQLBaseListener.cpp
RULE_SRC    := RuleLexer.cpp RuleParser.cpp

.PHONY: all plugins demo clean

all: waf rulec plugins

# ------------------------------------------------------------
# 引擎
# ------------------------------------------------------------

waf: waf.cc ast_builder.cc $(MINISQL_SRC) ast.h ast_builder.h rule_plugin.h
	$(CXX) $(CXXFLAGS) waf.cc ast_builder.cc $(MINISQL_SRC) $(LDLIBS) -ldl -o waf

# ------------------------------------------------------------
# 规则编译器
# ------------------------------------------------------------

rulec: rule_compiler.cc $(RULE_SRC) ast.h rule_plugin.h
	$(CXX) $(CXXFLAGS) rule_compiler.cc $(RULE_SRC) $(LDLIBS) -o rulec

# ------------------------------------------------------------
# 规则插件（每次重编，规则量小、编译快）
# ------------------------------------------------------------

plugins: rulec
	mkdir -p build/plugins
	@set -e; for f in rules/sqli/*.g4 rules/xss/*.g4; do \
		echo "== compile $$f"; \
		./rulec --include . -o build/plugins "$$f"; \
	done

# ------------------------------------------------------------
# 演示
# ------------------------------------------------------------

demo: all
	@echo; echo "#### 1. 良性 SQL（期望 ALLOW）";   ./waf --dump-ast "SELECT name FROM users WHERE id = 1" || true
	@echo; echo "#### 2. WHERE 1=1 恒真（期望 BLOCK: always_true）"; ./waf "SELECT * FROM users WHERE 1=1" || true
	@echo; echo "#### 3. UNION SELECT（期望 BLOCK: union_select）";  ./waf "SELECT id, name FROM users UNION SELECT user, password FROM admin" || true
	@echo; echo "#### 4. SLEEP 时间盲注（期望 BLOCK: sleep）";        ./waf "SELECT SLEEP(5)" || true
	@echo; echo "#### 5. LOAD_FILE 文件读取（期望 BLOCK: load_file）"; ./waf "SELECT LOAD_FILE('/etc/passwd')" || true
	@echo; echo "#### 6. XSS <script>（期望 BLOCK: script_tag）";     ./waf "GET /q?x=<script>alert(1)</script>" || true
	@echo; echo "#### 7. 非 SQL 良性请求（期望 FAST PATH ALLOW）";    ./waf "GET /index.html HTTP/1.1" || true
	@echo; echo "#### 8. BENCHMARK 性能消耗（期望 BLOCK: benchmark）"; ./waf "SELECT BENCHMARK(10000000, MD5('x'))" || true

# ------------------------------------------------------------

clean:
	rm -rf build waf rulec
