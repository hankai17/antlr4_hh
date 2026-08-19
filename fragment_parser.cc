#include "fragment_parser.h"

#include "fragment_lexer.h"

#include <algorithm>
#include <cctype>
#include <memory>

namespace waf {
namespace frag {
namespace {

std::string lower(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

AstPtr makeNode(const std::string& kind) {
    auto n = std::make_unique<AstNode>(kind);
    n->setAttr("fragment", "true");
    return n;
}

struct Parser {
    const std::vector<Token>& toks;
    size_t pos = 0;

    explicit Parser(const std::vector<Token>& t) : toks(t) {}

    const Token& peek(size_t off = 0) const {
        size_t p = pos + off;
        return p < toks.size() ? toks[p] : toks.back();
    }

    const Token& next() {
        const Token& t = peek();
        if (pos < toks.size()) ++pos;
        return t;
    }

    bool at(Tok t) const { return peek().type == t; }

    bool match(Tok t) {
        if (at(t)) { ++pos; return true; }
        return false;
    }

    // ----------------------------------------------------------
    // 表达式（优先级自低向高）
    // ----------------------------------------------------------

    AstPtr parseExpr() { return parseOr(); }

    AstPtr parseOr() {
        AstPtr left = parseAnd();
        while (at(Tok::OR)) {
            next();
            AstPtr right = parseAnd();
            if (!right) { skipJunk(); continue; }
            auto b = makeNode("BinaryExpr");
            b->setAttr("op", "OR");
            b->addNamed("left", std::move(left));
            b->addNamed("right", std::move(right));
            left = std::move(b);
        }
        return left;
    }

    AstPtr parseAnd() {
        AstPtr left = parseNot();
        while (at(Tok::AND)) {
            next();
            AstPtr right = parseNot();
            if (!right) { skipJunk(); continue; }
            auto b = makeNode("BinaryExpr");
            b->setAttr("op", "AND");
            b->addNamed("left", std::move(left));
            b->addNamed("right", std::move(right));
            left = std::move(b);
        }
        return left;
    }

    AstPtr parseNot() {
        if (at(Tok::NOT)) {
            next();
            AstPtr operand = parseNot();
            if (!operand) return nullptr;
            auto u = makeNode("UnaryExpr");
            u->setAttr("op", "NOT");
            u->addNamed("operand", std::move(operand));
            return u;
        }
        return parseCmp();
    }

    AstPtr parseCmp() {
        // EXISTS (...) 可作为比较表达式的起点（对应完整语法的 EXISTS 分支）
        if (at(Tok::KW_EXISTS)) {
            next();
            AstPtr operand;
            if (match(Tok::LPAREN)) {
                if (at(Tok::KW_SELECT)) {
                    operand = parseSelect();
                    if (operand) operand->setAttr("subquery", "true");
                } else {
                    operand = parseExpr();
                }
                match(Tok::RPAREN);
            }
            auto u = makeNode("UnaryExpr");
            u->setAttr("op", "EXISTS");
            if (operand) u->addNamed("operand", std::move(operand));
            return u;
        }

        AstPtr left = parseAdd();
        if (!left) return nullptr;

        while (true) {
            Tok t = peek().type;
            if (t == Tok::EQ || t == Tok::NE || t == Tok::LT || t == Tok::LE ||
                t == Tok::GT || t == Tok::GE) {
                std::string op = next().text;
                AstPtr right = parseAdd();
                if (!right) { skipJunk(); continue; }
                auto b = makeNode("BinaryExpr");
                b->setAttr("op", op);
                b->addNamed("left", std::move(left));
                b->addNamed("right", std::move(right));
                left = std::move(b);
                continue;
            }

            bool negated = false;
            if (at(Tok::NOT) && (peek(1).type == Tok::KW_IN || peek(1).type == Tok::KW_LIKE ||
                                 peek(1).type == Tok::KW_BETWEEN || peek(1).type == Tok::KW_EXISTS)) {
                next();
                negated = true;
            }

            if (at(Tok::KW_IN)) {
                next();
                std::string op = negated ? "NOT IN" : "IN";
                match(Tok::LPAREN);
                AstPtr right;
                if (at(Tok::KW_SELECT)) {
                    right = parseSelect();
                    if (right) right->setAttr("subquery", "true");
                } else {
                    auto list = makeNode("List");
                    while (AstPtr e = parseExpr()) {
                        list->addChild(std::move(e));
                        if (!match(Tok::COMMA)) break;
                    }
                    right = std::move(list);
                }
                match(Tok::RPAREN);
                auto b = makeNode("BinaryExpr");
                b->setAttr("op", op);
                b->addNamed("left", std::move(left));
                b->addNamed("right", std::move(right));
                left = std::move(b);
                continue;
            }

            if (at(Tok::KW_LIKE)) {
                next();
                std::string op = negated ? "NOT LIKE" : "LIKE";
                AstPtr right = parseAdd();
                if (!right) { skipJunk(); continue; }
                auto b = makeNode("BinaryExpr");
                b->setAttr("op", op);
                b->addNamed("left", std::move(left));
                b->addNamed("right", std::move(right));
                left = std::move(b);
                continue;
            }

            if (at(Tok::KW_BETWEEN)) {
                next();
                std::string op = negated ? "NOT BETWEEN" : "BETWEEN";
                AstPtr low = parseAdd();
                match(Tok::AND);
                AstPtr high = parseAdd();
                auto b = makeNode("BinaryExpr");
                b->setAttr("op", op);
                b->addNamed("left", std::move(left));
                if (low) b->addNamed("low", std::move(low));
                if (high) b->addNamed("high", std::move(high));
                left = std::move(b);
                continue;
            }

            if (at(Tok::KW_EXISTS)) {
                next();
                std::string op = negated ? "NOT EXISTS" : "EXISTS";
                AstPtr operand;
                if (match(Tok::LPAREN)) {
                    if (at(Tok::KW_SELECT)) {
                        operand = parseSelect();
                        if (operand) operand->setAttr("subquery", "true");
                    } else {
                        operand = parseExpr();
                    }
                    match(Tok::RPAREN);
                } else {
                    operand = parsePrimary();
                }
                auto u = makeNode("UnaryExpr");
                u->setAttr("op", op);
                if (operand) u->addNamed("operand", std::move(operand));
                left = std::move(u);
                continue;
            }

            if (at(Tok::KW_IS)) {
                next();
                std::string op = "IS ";
                if (match(Tok::NOT)) op += "NOT ";
                if (match(Tok::KW_NULL)) op += "NULL";
                else if (match(Tok::KW_TRUE)) op += "TRUE";
                else if (match(Tok::KW_FALSE)) op += "FALSE";
                auto u = makeNode("UnaryExpr");
                u->setAttr("op", op);
                u->addNamed("operand", std::move(left));
                left = std::move(u);
                continue;
            }

            break;
        }
        return left;
    }

    AstPtr parseAdd() {
        AstPtr left = parseMul();
        while (at(Tok::PLUS) || at(Tok::MINUS) || at(Tok::PIPE2)) {
            std::string op = next().text;
            AstPtr right = parseMul();
            if (!right) { skipJunk(); continue; }
            auto b = makeNode("BinaryExpr");
            b->setAttr("op", op);
            b->addNamed("left", std::move(left));
            b->addNamed("right", std::move(right));
            left = std::move(b);
        }
        return left;
    }

    AstPtr parseMul() {
        AstPtr left = parseUnary();
        while (at(Tok::STAR) || at(Tok::DIV) || at(Tok::MOD)) {
            std::string op = next().text;
            AstPtr right = parseUnary();
            if (!right) { skipJunk(); continue; }
            auto b = makeNode("BinaryExpr");
            b->setAttr("op", op);
            b->addNamed("left", std::move(left));
            b->addNamed("right", std::move(right));
            left = std::move(b);
        }
        return left;
    }

    AstPtr parseUnary() {
        if (at(Tok::PLUS) || at(Tok::MINUS)) {
            std::string op = next().text;
            AstPtr operand = parseUnary();
            if (!operand) return nullptr;
            auto u = makeNode("UnaryExpr");
            u->setAttr("op", op);
            u->addNamed("operand", std::move(operand));
            return u;
        }
        return parsePrimary();
    }

    AstPtr parsePrimary() {
        const Token& t = peek();
        switch (t.type) {
            case Tok::NUMBER: {
                next();
                auto n = makeNode("Constant");
                n->setAttr("type", "NUMBER");
                n->setAttr("value", t.text);
                return n;
            }
            case Tok::STRING: {
                next();
                auto n = makeNode("Constant");
                n->setAttr("type", "STRING");
                n->setAttr("value", t.text);
                return n;
            }
            case Tok::KW_TRUE:
            case Tok::KW_FALSE: {
                next();
                auto n = makeNode("Constant");
                n->setAttr("type", "BOOL");
                n->setAttr("value", lower(t.text));
                return n;
            }
            case Tok::KW_NULL: {
                next();
                auto n = makeNode("Constant");
                n->setAttr("type", "NULL");
                n->setAttr("value", "NULL");
                return n;
            }
            case Tok::IDENT: {
                next();
                if (at(Tok::LPAREN)) {
                    next();
                    auto f = makeNode("FunctionCall");
                    f->setAttr("name", lower(t.text));
                    while (AstPtr e = parseExpr()) {
                        f->addChild(std::move(e));
                        if (!match(Tok::COMMA)) break;
                    }
                    match(Tok::RPAREN);
                    return f;
                }
                auto c = makeNode("ColumnRef");
                c->setAttr("name", t.text);
                return c;
            }
            case Tok::LPAREN: {
                next();
                AstPtr inner;
                if (at(Tok::KW_SELECT)) {
                    inner = parseSelect();
                    if (inner) inner->setAttr("subquery", "true");
                } else {
                    inner = parseExpr();
                }
                match(Tok::RPAREN);
                return inner;
            }
            case Tok::QUOTE:
                // 未闭合引号：容错跳过，继续解析后续内容
                next();
                return nullptr;
            default:
                return nullptr;
        }
    }

    void skipJunk() {
        while (pos < toks.size() && peek().type != Tok::END) ++pos;
    }

    // ----------------------------------------------------------
    // 语句片段
    // ----------------------------------------------------------

    AstPtr parseSelect() {
        match(Tok::KW_SELECT);
        auto s = makeNode("Select");
        if (match(Tok::STAR)) {
            s->setAttr("star", "*");
        } else {
            while (AstPtr e = parseExpr()) {
                s->addChild(std::move(e));
                if (!match(Tok::COMMA)) break;
            }
        }
        if (match(Tok::KW_FROM)) {
            s->setAttr("from", "true");
            auto from = makeNode("From");
            if (at(Tok::IDENT)) {
                auto t = makeNode("TableRef");
                t->setAttr("name", next().text);
                from->addChild(std::move(t));
            } else if (at(Tok::LPAREN)) {
                next();
                AstPtr sub = parseSelect();
                if (sub) {
                    sub->setAttr("subquery", "true");
                    from->addChild(std::move(sub));
                }
                match(Tok::RPAREN);
            }
            s->addChild(std::move(from));
        }
        if (match(Tok::KW_WHERE)) {
            s->setAttr("where", "true");
            auto w = makeNode("Where");
            if (AstPtr e = parseExpr()) w->addChild(std::move(e));
            s->addChild(std::move(w));
        }
        if (match(Tok::KW_ORDER)) {
            match(Tok::KW_BY);
            s->setAttr("orderBy", "true");
            auto o = makeNode("OrderBy");
            if (AstPtr e = parseExpr()) o->addChild(std::move(e));
            s->addChild(std::move(o));
        }
        if (match(Tok::KW_LIMIT)) {
            s->setAttr("limit", "true");
            auto l = makeNode("Limit");
            if (AstPtr e = parseExpr()) l->addChild(std::move(e));
            s->addChild(std::move(l));
        }
        return s;
    }

    // 在 token 流中寻找第一个语句模式，找不到返回 nullptr
    AstPtr scanStatement(size_t start = 0) {
        int depth = 0;
        for (size_t i = start; i + 1 < toks.size(); ++i) {
            Tok t = toks[i].type;
            if (t == Tok::LPAREN) { ++depth; continue; }
            if (t == Tok::RPAREN) { if (depth > 0) --depth; continue; }
            if (depth > 0) continue;  // 括号内不当作语句起点（子查询属于表达式上下文）
            if (t == Tok::SEMI) {
                pos = i;
                next();  // 消费分号
                auto st = makeNode("Stacked");
                if (AstPtr child = scanStatement(pos)) st->addChild(std::move(child));
                return st;
            }
            if (t == Tok::KW_UNION && toks[i + 1].type == Tok::KW_SELECT) {
                pos = i;
                next();  // UNION
                match(Tok::KW_ALL);
                auto q = makeNode("Query");
                q->setAttr("union", "true");
                if (AstPtr s = parseSelect()) q->addChild(std::move(s));
                return q;
            }
            if (t == Tok::KW_SELECT) {
                pos = i;
                return parseSelect();
            }
            if (t == Tok::KW_INSERT) {
                pos = i;
                next();
                match(Tok::KW_INTO);
                auto st = makeNode("StmtInsert");
                if (at(Tok::IDENT)) st->setAttr("table", next().text);
                if (match(Tok::LPAREN)) {
                    while (AstPtr e = parseExpr()) {
                        st->addChild(std::move(e));
                        if (!match(Tok::COMMA)) break;
                    }
                    match(Tok::RPAREN);
                }
                if (match(Tok::KW_VALUES)) {
                    match(Tok::LPAREN);
                    while (AstPtr e = parseExpr()) {
                        st->addChild(std::move(e));
                        if (!match(Tok::COMMA)) break;
                    }
                    match(Tok::RPAREN);
                }
                return st;
            }
            if (t == Tok::KW_UPDATE) {
                pos = i;
                next();
                auto st = makeNode("StmtUpdate");
                if (at(Tok::IDENT)) st->setAttr("table", next().text);
                if (match(Tok::KW_SET)) {
                    while (AstPtr e = parseExpr()) {
                        st->addChild(std::move(e));
                        if (!match(Tok::COMMA)) break;
                    }
                }
                return st;
            }
            if (t == Tok::KW_DELETE) {
                pos = i;
                next();
                match(Tok::KW_FROM);
                auto st = makeNode("StmtDelete");
                if (at(Tok::IDENT)) st->setAttr("table", next().text);
                return st;
            }
            if (t == Tok::KW_ORDER && toks[i + 1].type == Tok::KW_BY) {
                pos = i;
                next();
                next();
                auto o = makeNode("OrderBy");
                if (AstPtr e = parseExpr()) o->addChild(std::move(e));
                if (at(Tok::KW_ASC) || at(Tok::KW_DESC)) {
                    o->setAttr("dir", next().text);
                }
                return o;
            }
            if (t == Tok::KW_LIMIT) {
                pos = i;
                next();
                auto l = makeNode("Limit");
                if (AstPtr e = parseExpr()) l->addChild(std::move(e));
                if (match(Tok::KW_OFFSET)) {
                    if (AstPtr e = parseExpr()) l->addChild(std::move(e));
                }
                return l;
            }
        }
        return nullptr;
    }
};

// 表达式是否"有意义"：至少含一个操作符/函数/子查询，纯标识符不算结构。
bool meaningful(const AstNode* n) {
    if (!n) return false;
    if (n->kind == "BinaryExpr" || n->kind == "UnaryExpr" ||
        n->kind == "FunctionCall" || n->kind == "Select") {
        return true;
    }
    return !n->children.empty();
}

}  // namespace

AstPtr parseFragment(const std::string& input) {
    std::vector<Token> toks = lex(input);
    // 片段里的引号只作分隔标记，不参与表达式结构，直接滤除。
    std::vector<Token> filtered;
    for (const auto& t : toks) {
        if (t.type != Tok::QUOTE) filtered.push_back(t);
    }

    Parser q(filtered);

    if (AstPtr st = q.scanStatement()) return st;

    q.pos = 0;
    AstPtr expr = q.parseExpr();
    if (meaningful(expr.get())) return expr;
    return nullptr;
}

}  // namespace frag
}  // namespace waf
