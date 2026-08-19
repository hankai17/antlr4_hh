cmake_minimum_required(VERSION 3.16)

project(compiled_waf LANGUAGES CXX)

# ------------------------------------------------------------
# 全局编译选项
# ------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
add_compile_options(-Wall -Wextra)

# ------------------------------------------------------------
# ANTLR4 C++ 运行时（可 -D 覆盖路径）
# ------------------------------------------------------------

set(ANTLR4_RUNTIME_INC
    "/root/CLionProjects/antlr4-4.13.2/runtime/Cpp/runtime/src"
    CACHE PATH "ANTLR4 C++ runtime headers dir")
set(ANTLR4_RUNTIME_LIB_DIR
    "/root/CLionProjects/antlr4-4.13.2/runtime/Cpp/build/runtime"
    CACHE PATH "ANTLR4 C++ runtime library dir")

find_path(ANTLR4_RUNTIME_INC_FOUND
    antlr4-runtime.h
    HINTS ${ANTLR4_RUNTIME_INC})
find_library(ANTLR4_RUNTIME_LIB_FOUND
    antlr4-runtime
    HINTS ${ANTLR4_RUNTIME_LIB_DIR})

if(NOT ANTLR4_RUNTIME_INC_FOUND OR NOT ANTLR4_RUNTIME_LIB_FOUND)
    message(FATAL_ERROR
        "ANTLR4 C++ runtime not found. Pass -DANTLR4_RUNTIME_INC=... "
        "and -DANTLR4_RUNTIME_LIB_DIR=...")
endif()

include_directories(${ANTLR4_RUNTIME_INC_FOUND} ${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${ANTLR4_RUNTIME_LIB_DIR})
set(CMAKE_BUILD_RPATH ${ANTLR4_RUNTIME_LIB_DIR})

# ------------------------------------------------------------
# 目标 1：WAF 主引擎
# ------------------------------------------------------------

add_executable(waf
    waf.cc
    ast_builder.cc
    fragment_lexer.cc
    fragment_parser.cc
    MiniSQLLexer.cpp
    MiniSQLParser.cpp
    MiniSQLBaseListener.cpp
)
target_link_libraries(waf PRIVATE antlr4-runtime ${CMAKE_DL_LIBS})

# ------------------------------------------------------------
# 目标 2：规则编译器 rulec
# ------------------------------------------------------------

add_executable(rulec
    rule_compiler.cc
    RuleLexer.cpp
    RuleParser.cpp
)
target_link_libraries(rulec PRIVATE antlr4-runtime)

# ------------------------------------------------------------
# 目标 3：规则插件（每条 .g4 编译为独立 .so）
# ------------------------------------------------------------

file(GLOB RULE_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/rules/sqli/*.g4
    ${CMAKE_CURRENT_SOURCE_DIR}/rules/xss/*.g4
)

set(PLUGIN_OUT_DIR ${CMAKE_BINARY_DIR}/plugins)
file(MAKE_DIRECTORY ${PLUGIN_OUT_DIR})

set(PLUGIN_SOS "")
foreach(rule_file ${RULE_FILES})
    get_filename_component(rule_name ${rule_file} NAME_WE)
    set(plugin_so ${PLUGIN_OUT_DIR}/lib${rule_name}_rule.so)
    add_custom_command(
        OUTPUT ${plugin_so}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PLUGIN_OUT_DIR}
        COMMAND $<TARGET_FILE:rulec>
                --include ${CMAKE_CURRENT_SOURCE_DIR}
                -o ${PLUGIN_OUT_DIR}
                ${rule_file}
        DEPENDS rulec
                ${rule_file}
                ${CMAKE_CURRENT_SOURCE_DIR}/ast.h
                ${CMAKE_CURRENT_SOURCE_DIR}/rule_plugin.h
        COMMENT "compile rule ${rule_file} -> ${plugin_so}"
        VERBATIM
    )
    list(APPEND PLUGIN_SOS ${plugin_so})
endforeach()

add_custom_target(plugins ALL DEPENDS ${PLUGIN_SOS})

# ------------------------------------------------------------
# 目标 4：端到端演示
# ------------------------------------------------------------

add_custom_target(demo
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/demo.sh
            $<TARGET_FILE:waf>
            ${PLUGIN_OUT_DIR}
    DEPENDS waf plugins
    COMMENT "run end-to-end demo (benign / SQLi / XSS samples)"
    VERBATIM
)

# ------------------------------------------------------------
# 目标 5：规则校验（正/负样本断言）
# ------------------------------------------------------------

add_custom_target(validate
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/validate_sqli.sh
            $<TARGET_FILE:waf>
            ${PLUGIN_OUT_DIR}
    DEPENDS waf plugins
    COMMENT "validate sqli rules against positive/negative samples"
    VERBATIM
)

# ------------------------------------------------------------
# 目标 6：重新生成 ANTLR 解析器（需要 java + antlr jar）
# ------------------------------------------------------------

add_custom_target(grammars
    COMMAND java -jar ${CMAKE_CURRENT_SOURCE_DIR}/antlr-4.13.2-complete.jar
            -Dlanguage=Cpp -no-listener
            ${CMAKE_CURRENT_SOURCE_DIR}/Rule.g4
    COMMAND java -jar ${CMAKE_CURRENT_SOURCE_DIR}/antlr-4.13.2-complete.jar
            -Dlanguage=Cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/MiniSQL.g4
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "regenerate ANTLR lexer/parser sources"
    VERBATIM
)
