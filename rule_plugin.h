#pragma once

// ============================================================
// 规则插件 ABI（waf_rule_abi / waf_rule_info / waf_rule_check_text）
// ------------------------------------------------------------
// 每条攻击规则（标准 ANTLR 语法）经 rulec 编译后生成一个 .so，
// 导出以下三个 C 符号：
//
//   int         waf_rule_abi()          版本号，不匹配则拒绝加载
//   RuleInfo*   waf_rule_info()         规则元信息（名称/级别/动作/描述/输入画像）
//   bool        waf_rule_check_text(const char*)  对归一化文本做 token 匹配
//
// 主引擎通过 dlopen/dlsym 加载插件，热插拔；插件只需头文件，无需链接引擎。
// ============================================================

namespace waf {

constexpr int WAF_RULE_ABI = 3;

struct RuleInfo {
    const char* name;        // 规则名，如 "sleep"
    const char* severity;    // LOW / MEDIUM / HIGH / CRITICAL
    const char* action;      // ALLOW / BLOCK（命中 BLOCK 规则 => 拦截）
    const char* description; // 人类可读描述
    const char* profile;     // "sql"（始终）/ "fragment"（仅非完整 SQL）/ "raw"（仅非完整 SQL）
};

}  // namespace waf
