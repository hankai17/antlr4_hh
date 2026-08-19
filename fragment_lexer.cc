#include "fragment_lexer.h"

#include <cctype>
#include <unordered_map>

namespace waf {
namespace frag {
namespace {

std::string lower(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

const std::unordered_map<std::string, Tok>& keywords() {
    static const std::unordered_map<std::string, Tok> map = {
        {"and", Tok::AND},       {"or", Tok::OR},         {"not", Tok::NOT},
        {"select", Tok::KW_SELECT}, {"union", Tok::KW_UNION}, {"all", Tok::KW_ALL},
        {"from", Tok::KW_FROM},  {"where", Tok::KW_WHERE},
        {"order", Tok::KW_ORDER}, {"by", Tok::KW_BY},     {"limit", Tok::KW_LIMIT},
        {"offset", Tok::KW_OFFSET}, {"insert", Tok::KW_INSERT}, {"into", Tok::KW_INTO},
        {"values", Tok::KW_VALUES}, {"update", Tok::KW_UPDATE}, {"set", Tok::KW_SET},
        {"delete", Tok::KW_DELETE}, {"drop", Tok::KW_DROP}, {"alter", Tok::KW_ALTER},
        {"create", Tok::KW_CREATE}, {"exists", Tok::KW_EXISTS}, {"in", Tok::KW_IN},
        {"like", Tok::KW_LIKE},  {"between", Tok::KW_BETWEEN}, {"is", Tok::KW_IS},
        {"null", Tok::KW_NULL},  {"true", Tok::KW_TRUE},  {"false", Tok::KW_FALSE},
        {"asc", Tok::KW_ASC},    {"desc", Tok::KW_DESC},
    };
    return map;
}

}  // namespace

std::vector<Token> lex(const std::string& s) {
    std::vector<Token> toks;
    size_t i = 0;
    const size_t n = s.size();

    while (i < n) {
        char c = s[i];

        // 空白与注释
        if (std::isspace(static_cast<unsigned char>(c))) { ++i; continue; }
        if (c == '-' && i + 1 < n && s[i + 1] == '-') {
            while (i < n && s[i] != '\n') ++i;
            continue;
        }
        if (c == '/' && i + 1 < n && s[i + 1] == '*') {
            size_t end = s.find("*/", i + 2);
            i = (end == std::string::npos) ? n : end + 2;
            continue;
        }

        // 字符串 / 引号：
        //   * 引号内容"像字面量"（无空白、无操作符）-> STRING token
        //   * 否则（跨注入边界，如 admin' OR ...）-> QUOTE 标记，只消费引号本身，
        //     后续内容继续正常识别
        if (c == '\'') {
            size_t close = s.find('\'', i + 1);
            bool literalLike = false;
            if (close != std::string::npos) {
                std::string content = s.substr(i + 1, close - i - 1);
                literalLike = content.find_first_of(" \t\r\n=<>!()+-*/%,;") == std::string::npos;
            }
            if (literalLike) {
                toks.push_back({Tok::STRING, s.substr(i + 1, close - i - 1)});
                i = close + 1;
            } else {
                toks.push_back({Tok::QUOTE, "'"});
                i = i + 1;  // 只消费引号本身，后面内容继续正常识别
            }
            continue;
        }

        // 双引号标识符
        if (c == '"') {
            size_t end = s.find('"', i + 1);
            if (end == std::string::npos) {
                toks.push_back({Tok::IDENT, s.substr(i + 1)});
                i = n;
            } else {
                toks.push_back({Tok::IDENT, s.substr(i + 1, end - i - 1)});
                i = end + 1;
            }
            continue;
        }

        // 数字
        if (std::isdigit(static_cast<unsigned char>(c)) ||
            (c == '.' && i + 1 < n && std::isdigit(static_cast<unsigned char>(s[i + 1])))) {
            size_t j = i;
            while (j < n && std::isdigit(static_cast<unsigned char>(s[j]))) ++j;
            if (j < n && s[j] == '.') {
                ++j;
                while (j < n && std::isdigit(static_cast<unsigned char>(s[j]))) ++j;
            }
            toks.push_back({Tok::NUMBER, s.substr(i, j - i)});
            i = j;
            continue;
        }

        // 标识符 / 关键字
        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            size_t j = i;
            while (j < n && (std::isalnum(static_cast<unsigned char>(s[j])) || s[j] == '_')) ++j;
            std::string word = s.substr(i, j - i);
            auto it = keywords().find(lower(word));
            toks.push_back({it == keywords().end() ? Tok::IDENT : it->second, word});
            i = j;
            continue;
        }

        // 操作符
        auto emit = [&](Tok t, size_t len) { toks.push_back({t, s.substr(i, len)}); i += len; };
        if (c == '=') { emit(Tok::EQ, 1); continue; }
        if (c == '!' && i + 1 < n && s[i + 1] == '=') { emit(Tok::NE, 2); continue; }
        if (c == '<' && i + 1 < n && s[i + 1] == '>') { emit(Tok::NE, 2); continue; }
        if (c == '<' && i + 1 < n && s[i + 1] == '=') { emit(Tok::LE, 2); continue; }
        if (c == '>' && i + 1 < n && s[i + 1] == '=') { emit(Tok::GE, 2); continue; }
        if (c == '<') { emit(Tok::LT, 1); continue; }
        if (c == '>') { emit(Tok::GT, 1); continue; }
        if (c == '|' && i + 1 < n && s[i + 1] == '|') { emit(Tok::PIPE2, 2); continue; }
        if (c == '+') { emit(Tok::PLUS, 1); continue; }
        if (c == '-') { emit(Tok::MINUS, 1); continue; }
        if (c == '*') { emit(Tok::STAR, 1); continue; }
        if (c == '/') { emit(Tok::DIV, 1); continue; }
        if (c == '%') { emit(Tok::MOD, 1); continue; }
        if (c == '(') { emit(Tok::LPAREN, 1); continue; }
        if (c == ')') { emit(Tok::RPAREN, 1); continue; }
        if (c == ',') { emit(Tok::COMMA, 1); continue; }
        if (c == ';') { emit(Tok::SEMI, 1); continue; }

        ++i;  // 未知字符容错跳过
    }
    toks.push_back({Tok::END, ""});
    return toks;
}

}  // namespace frag
}  // namespace waf
