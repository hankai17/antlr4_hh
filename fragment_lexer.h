#pragma once

// ============================================================
// 容错片段词法器
// ------------------------------------------------------------
// 真实请求里的载荷常是不完整 SQL，且可能引号不平衡（admin' OR '1'='1'）。
// 本词法器不追求"一次成功"，而是尽力产出 token 流：
//   * 未闭合字符串 -> 吐出 QUOTE 标记，继续扫描后续内容（不吞掉整段）
//   * 未知字符/注释 -> 直接跳过
//   * 关键字大小写不敏感（统一小写比较）
// ============================================================

#include <string>
#include <vector>

namespace waf {
namespace frag {

enum class Tok {
    IDENT, NUMBER, STRING, QUOTE,
    EQ, NE, LT, LE, GT, GE,
    PLUS, MINUS, STAR, DIV, MOD, PIPE2,
    LPAREN, RPAREN, COMMA, SEMI,
    AND, OR, NOT,
    KW_SELECT, KW_UNION, KW_ALL, KW_FROM, KW_WHERE,
    KW_ORDER, KW_BY, KW_LIMIT, KW_OFFSET,
    KW_INSERT, KW_INTO, KW_VALUES, KW_UPDATE, KW_SET, KW_DELETE,
    KW_DROP, KW_ALTER, KW_CREATE,
    KW_EXISTS, KW_IN, KW_LIKE, KW_BETWEEN, KW_IS,
    KW_NULL, KW_TRUE, KW_FALSE, KW_ASC, KW_DESC,
    END
};

struct Token {
    Tok type = Tok::END;
    std::string text;   // 原始文本（字符串为去引号后的内容）
};

std::vector<Token> lex(const std::string& input);

}  // namespace frag
}  // namespace waf
