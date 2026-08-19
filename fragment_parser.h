#pragma once

// ============================================================
// 容错片段解析器
// ------------------------------------------------------------
// 把不完整 SQL 片段直接解析成与完整解析同构的 AstNode：
//   * 表达式片段：1 OR 1=1 / admin' OR '1'='1' / x = (SELECT 1)
//   * 语句片段：UNION SELECT / SELECT..FROM / INSERT INTO / UPDATE..SET /
//     DELETE FROM / ORDER BY / LIMIT / 堆叠查询
// 所有节点带 fragment="true" 标记；识别不出任何结构时返回 nullptr。
// 语义规则无需改造即可复用（相同 kind/attrs/named）。
// ============================================================

#include "ast.h"

#include <string>

namespace waf {
namespace frag {

AstPtr parseFragment(const std::string& input);

}  // namespace frag
}  // namespace waf
