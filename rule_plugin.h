#pragma once

// ============================================================
// 规则插件 ABI（waf_rule_abi / waf_rule_info / waf_rule_check）
// ------------------------------------------------------------
// 每个规则 .g4 经 rulec 编译后生成一个 .so，导出以下三个 C 符号：
//
//   int         waf_rule_abi()          版本号，不匹配则拒绝加载
//   RuleInfo*   waf_rule_info()         规则元信息（名称/级别/动作/描述/输入画像）
//   bool        waf_rule_check(const AstNode& root)  全树语义匹配
//
// 主引擎通过 dlopen/dlsym 加载插件，热插拔；插件只需头文件，无需链接引擎。
// ============================================================

#include "ast.h"

namespace waf {

constexpr int WAF_RULE_ABI = 1;

struct RuleInfo {
    const char* name;        // 规则名，如 "sleep"
    const char* severity;    // LOW / MEDIUM / HIGH / CRITICAL
    const char* action;      // ALLOW / BLOCK（命中 BLOCK 规则 => 拦截）
    const char* description; // 人类可读描述
    const char* profile;     // "sql"（走 SQL 解析 AST）/ "raw"（原始文本节点）
};

// 深度优先遍历整棵 AST，任一节点命中 matcher 即返回 true。
template <typename Matcher>
bool matchAny(const AstNode& node, Matcher&& matcher) {
    if (matcher(node)) return true;
    for (const auto& child : node.children) {
        if (matchAny(*child, matcher)) return true;
    }
    return false;
}

}  // namespace waf
