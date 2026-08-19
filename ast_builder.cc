#include "ast_builder.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>

namespace waf {

namespace {

enum class CompKind { NONE, BINARY, UNARY };

CompKind comparisonKind(MiniSQLParser::ComparisonExpressionContext* ctx) {
    if (ctx->comparisonOperator() || ctx->IN() || ctx->LIKE() || ctx->BETWEEN()) {
        return CompKind::BINARY;
    }
    if (ctx->IS() || ctx->EXISTS()) return CompKind::UNARY;
    return CompKind::NONE;
}

// 数字字面量规范化：1 / 1.0 / 1.00 -> "1"，保证 1 = 1.0 语义相等。
// 用 17 位有效数字往返（round-trip）避免精度碰撞。
std::string canonicalNumber(const std::string& raw) {
    char* end = nullptr;
    double v = std::strtod(raw.c_str(), &end);
    if (end == raw.c_str() || *end != '\0') return raw;  // 解析失败原样返回
    char buf[64];
    std::snprintf(buf, sizeof(buf), "%.17g", v);
    return buf;
}

}  // namespace

AstPtr AstBuilder::result() {
    return std::move(root_);
}

AstNode* AstBuilder::top() {
    return stack_.empty() ? nullptr : stack_.back();
}

AstNode* AstBuilder::pushNode(const std::string& kind) {
    auto node = std::make_unique<AstNode>(kind);
    AstNode* raw = node.get();
    if (stack_.empty()) {
        root_ = std::move(node);
    } else {
        stack_.back()->addChild(std::move(node));
    }
    stack_.push_back(raw);
    return raw;
}

void AstBuilder::pop() {
    stack_.pop_back();
}

void AstBuilder::foldBinaryChain(const std::vector<std::string>& ops) {
    AstNode* root = top();
    if (!root || root->children.size() < 2) return;

    std::vector<AstPtr> items;
    for (auto& c : root->children) items.push_back(std::move(c));
    root->children.clear();
    root->named.clear();

    AstPtr acc = std::move(items[0]);
    for (size_t i = 1; i < items.size(); ++i) {
        auto b = std::make_unique<AstNode>("BinaryExpr");
        std::string op = ops.size() > i - 1 ? ops[i - 1] : "";
        b->setAttr("op", op);
        b->addNamed("left", std::move(acc));
        b->addNamed("right", std::move(items[i]));
        acc = std::move(b);
    }
    root->addChild(std::move(acc));
}

// ------------------------------------------------------------
// Query / 顶层
// ------------------------------------------------------------

void AstBuilder::enterQueryStatement(MiniSQLParser::QueryStatementContext*) {
    pushNode("Query");
}

void AstBuilder::exitQueryStatement(MiniSQLParser::QueryStatementContext*) {
    pop();
}

void AstBuilder::enterQueryExpression(MiniSQLParser::QueryExpressionContext* ctx) {
    // UNION 出现在 queryTerm (UNION ALL? queryTerm)* 中。
    if (ctx->queryTerm().size() > 1 && top() && top()->kind == "Query") {
        top()->setAttr("union", "true");
    }
    // 顶层 queryStatement 下的 queryExpression 以 Query 为父；其余都是子查询上下文。
    subqueryStack_.push_back(top() && top()->kind != "Query");
}

void AstBuilder::exitQueryExpression(MiniSQLParser::QueryExpressionContext*) {
    subqueryStack_.pop_back();
}

void AstBuilder::enterQuerySpecification(MiniSQLParser::QuerySpecificationContext*) {
    pushNode("Select");
    if (!subqueryStack_.empty() && subqueryStack_.back()) {
        top()->setAttr("subquery", "true");
    }
}

void AstBuilder::exitQuerySpecification(MiniSQLParser::QuerySpecificationContext*) {
    pop();
}

void AstBuilder::enterSetQuantifier(MiniSQLParser::SetQuantifierContext* ctx) {
    if (ctx->DISTINCT() && top()) top()->setAttr("distinct", "true");
}

void AstBuilder::enterSelectList(MiniSQLParser::SelectListContext* ctx) {
    if (ctx->STAR() && top()) top()->setAttr("star", "*");
}

void AstBuilder::enterSelectItem(MiniSQLParser::SelectItemContext*) {
    pushNode("SelectItem");
}

void AstBuilder::exitSelectItem(MiniSQLParser::SelectItemContext*) {
    pop();
}

// ------------------------------------------------------------
// FROM / 表引用
// ------------------------------------------------------------

void AstBuilder::enterFromClause(MiniSQLParser::FromClauseContext*) {
    pushNode("From");
}

void AstBuilder::exitFromClause(MiniSQLParser::FromClauseContext*) {
    pop();
}

void AstBuilder::enterTablePrimary(MiniSQLParser::TablePrimaryContext* ctx) {
    // 子查询表（LPAREN queryExpression RPAREN）不创建节点，Select 直接挂到 From。
    if (ctx->identifier().empty()) return;
    AstNode* n = pushNode("TableRef");
    n->setAttr("name", ctx->identifier(0)->getText());
    if (ctx->identifier().size() > 1) {
        n->setAttr("alias", ctx->identifier(1)->getText());
    }
}

void AstBuilder::exitTablePrimary(MiniSQLParser::TablePrimaryContext* ctx) {
    if (!ctx->identifier().empty()) pop();
}

// ------------------------------------------------------------
// WHERE / GROUP BY / HAVING / ORDER BY / LIMIT
// ------------------------------------------------------------

void AstBuilder::enterWhereClause(MiniSQLParser::WhereClauseContext*) {
    pushNode("Where");
}

void AstBuilder::exitWhereClause(MiniSQLParser::WhereClauseContext*) {
    pop();
}

void AstBuilder::enterGroupByClause(MiniSQLParser::GroupByClauseContext*) {
    pushNode("GroupBy");
}

void AstBuilder::exitGroupByClause(MiniSQLParser::GroupByClauseContext*) {
    pop();
}

void AstBuilder::enterHavingClause(MiniSQLParser::HavingClauseContext*) {
    pushNode("Having");
}

void AstBuilder::exitHavingClause(MiniSQLParser::HavingClauseContext*) {
    pop();
}

void AstBuilder::enterOrderByClause(MiniSQLParser::OrderByClauseContext*) {
    pushNode("OrderBy");
}

void AstBuilder::exitOrderByClause(MiniSQLParser::OrderByClauseContext*) {
    pop();
}

void AstBuilder::enterOrderItem(MiniSQLParser::OrderItemContext* ctx) {
    AstNode* n = pushNode("OrderItem");
    if (ctx->ASC()) n->setAttr("dir", "ASC");
    if (ctx->DESC()) n->setAttr("dir", "DESC");
}

void AstBuilder::exitOrderItem(MiniSQLParser::OrderItemContext*) {
    pop();
}

void AstBuilder::enterLimitClause(MiniSQLParser::LimitClauseContext*) {
    pushNode("Limit");
}

void AstBuilder::exitLimitClause(MiniSQLParser::LimitClauseContext*) {
    pop();
}

// ------------------------------------------------------------
// 布尔表达式
// ------------------------------------------------------------

void AstBuilder::enterOrExpression(MiniSQLParser::OrExpressionContext* ctx) {
    if (ctx->andExpression().size() > 1) pushNode("BinaryExpr");
}

void AstBuilder::exitOrExpression(MiniSQLParser::OrExpressionContext* ctx) {
    if (ctx->andExpression().size() > 1) {
        top()->setAttr("op", "OR");
        foldBinaryChain(std::vector<std::string>(ctx->andExpression().size() - 1, "OR"));
        pop();
    }
}

void AstBuilder::enterAndExpression(MiniSQLParser::AndExpressionContext* ctx) {
    if (ctx->notExpression().size() > 1) pushNode("BinaryExpr");
}

void AstBuilder::exitAndExpression(MiniSQLParser::AndExpressionContext* ctx) {
    if (ctx->notExpression().size() > 1) {
        top()->setAttr("op", "AND");
        foldBinaryChain(std::vector<std::string>(ctx->notExpression().size() - 1, "AND"));
        pop();
    }
}

void AstBuilder::enterNotExpression(MiniSQLParser::NotExpressionContext* ctx) {
    if (ctx->NOT()) pushNode("UnaryExpr");
}

void AstBuilder::exitNotExpression(MiniSQLParser::NotExpressionContext* ctx) {
    if (ctx->NOT() && top()) {
        top()->setAttr("op", "NOT");
        if (!top()->children.empty()) top()->named["operand"] = top()->children[0].get();
        pop();
    }
}

// ------------------------------------------------------------
// 比较表达式
// ------------------------------------------------------------

void AstBuilder::enterComparisonExpression(MiniSQLParser::ComparisonExpressionContext* ctx) {
    switch (comparisonKind(ctx)) {
        case CompKind::BINARY: pushNode("BinaryExpr"); break;
        case CompKind::UNARY: pushNode("UnaryExpr"); break;
        case CompKind::NONE: break;
    }
    // 否则：单个 additive 子表达式，透传（不建节点）。
}

void AstBuilder::exitComparisonExpression(MiniSQLParser::ComparisonExpressionContext* ctx) {
    AstNode* n = top();
    if (!n) return;
    if (n->kind != "BinaryExpr" && n->kind != "UnaryExpr") return;

    const std::vector<MiniSQLParser::AdditiveExpressionContext*>& add = ctx->additiveExpression();

    if (ctx->comparisonOperator()) {
        n->setAttr("op", ctx->comparisonOperator()->getText());
        if (add.size() >= 2) {
            n->named["left"] = n->children[0].get();
            n->named["right"] = n->children[1].get();
        }
    } else if (ctx->IS()) {
        std::string op = "IS ";
        if (ctx->NOT()) op += "NOT ";
        if (ctx->NULL_()) op += "NULL";
        else if (ctx->TRUE()) op += "TRUE";
        else if (ctx->FALSE()) op += "FALSE";
        n->setAttr("op", op);
        if (!n->children.empty()) n->named["operand"] = n->children[0].get();
    } else if (ctx->IN()) {
        n->setAttr("op", ctx->NOT() ? "NOT IN" : "IN");
        if (n->children.size() >= 2) {
            n->named["left"] = n->children[0].get();
            n->named["right"] = n->children[1].get();
        }
    } else if (ctx->LIKE()) {
        n->setAttr("op", ctx->NOT() ? "NOT LIKE" : "LIKE");
        if (n->children.size() >= 2) {
            n->named["left"] = n->children[0].get();
            n->named["right"] = n->children[1].get();
        }
    } else if (ctx->BETWEEN()) {
        n->setAttr("op", ctx->NOT() ? "NOT BETWEEN" : "BETWEEN");
        if (n->children.size() >= 3) {
            n->named["left"] = n->children[0].get();
            n->named["low"] = n->children[1].get();
            n->named["high"] = n->children[2].get();
        }
    } else if (ctx->EXISTS()) {
        n->setAttr("op", ctx->NOT() ? "NOT EXISTS" : "EXISTS");
        if (!n->children.empty()) n->named["operand"] = n->children[0].get();
    }
    if (comparisonKind(ctx) != CompKind::NONE) pop();
}

// ------------------------------------------------------------
// 算术表达式
// ------------------------------------------------------------

void AstBuilder::enterAdditiveExpression(MiniSQLParser::AdditiveExpressionContext* ctx) {
    if (ctx->multiplicativeExpression().size() > 1) pushNode("BinaryExpr");
}

void AstBuilder::exitAdditiveExpression(MiniSQLParser::AdditiveExpressionContext* ctx) {
    size_t k = ctx->multiplicativeExpression().size();
    if (k <= 1) return;
    std::string op = ctx->PLUS(0) ? "+" : "-";
    top()->setAttr("op", op);
    std::vector<std::string> ops;
    for (size_t i = 0; i + 1 < k; ++i) ops.push_back(ctx->PLUS(i) ? "+" : "-");
    foldBinaryChain(ops);
    pop();
}

void AstBuilder::enterMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext* ctx) {
    if (ctx->unaryExpression().size() > 1) pushNode("BinaryExpr");
}

void AstBuilder::exitMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext* ctx) {
    size_t k = ctx->unaryExpression().size();
    if (k <= 1) return;
    std::string op = "*";
    if (ctx->DIV(0)) op = "/";
    if (ctx->MOD(0)) op = "%";
    top()->setAttr("op", op);
    std::vector<std::string> ops;
    for (size_t i = 0; i + 1 < k; ++i) {
        if (ctx->DIV(i)) ops.push_back("/");
        else if (ctx->MOD(i)) ops.push_back("%");
        else ops.push_back("*");
    }
    foldBinaryChain(ops);
    pop();
}

void AstBuilder::enterUnaryExpression(MiniSQLParser::UnaryExpressionContext* ctx) {
    if (ctx->PLUS() || ctx->MINUS()) pushNode("UnaryExpr");
}

void AstBuilder::exitUnaryExpression(MiniSQLParser::UnaryExpressionContext* ctx) {
    if (ctx->PLUS() || ctx->MINUS()) {
        top()->setAttr("op", ctx->MINUS() ? "-" : "+");
        if (!top()->children.empty()) top()->named["operand"] = top()->children[0].get();
        pop();
    }
}

// ------------------------------------------------------------
// 原子表达式
// ------------------------------------------------------------

void AstBuilder::enterLiteral(MiniSQLParser::LiteralContext* ctx) {
    AstNode* n = pushNode("Constant");
    if (ctx->NUMBER()) {
        n->setAttr("type", "NUMBER");
        n->setAttr("value", canonicalNumber(ctx->NUMBER()->getText()));
    } else if (ctx->STRING()) {
        std::string s = ctx->STRING()->getText();
        if (s.size() >= 2 && s.front() == '\'' && s.back() == '\'') {
            s = s.substr(1, s.size() - 2);
        }
        // '' -> '（MySQL 字符串转义）
        std::string unescaped;
        for (size_t i = 0; i < s.size(); ++i) {
            if (i + 1 < s.size() && s[i] == '\'' && s[i + 1] == '\'') {
                unescaped += '\'';
                ++i;
            } else {
                unescaped += s[i];
            }
        }
        n->setAttr("type", "STRING");
        n->setAttr("value", unescaped);
    } else if (ctx->NULL_()) {
        n->setAttr("type", "NULL");
        n->setAttr("value", "NULL");
    } else if (ctx->TRUE()) {
        n->setAttr("type", "BOOL");
        n->setAttr("value", "true");
    } else if (ctx->FALSE()) {
        n->setAttr("type", "BOOL");
        n->setAttr("value", "false");
    }
}

void AstBuilder::exitLiteral(MiniSQLParser::LiteralContext*) {
    pop();
}

void AstBuilder::enterColumnReference(MiniSQLParser::ColumnReferenceContext* ctx) {
    AstNode* n = pushNode("ColumnRef");
    const auto& ids = ctx->identifier();
    if (ids.empty()) return;
    n->setAttr("name", ids.back()->getText());
    if (ids.size() >= 2) n->setAttr("table", ids[ids.size() - 2]->getText());
    if (ids.size() >= 3) n->setAttr("schema", ids[ids.size() - 3]->getText());
}

void AstBuilder::exitColumnReference(MiniSQLParser::ColumnReferenceContext*) {
    pop();
}

void AstBuilder::enterFunctionCall(MiniSQLParser::FunctionCallContext* ctx) {
    AstNode* n = pushNode("FunctionCall");
    std::string name = ctx->identifier()->getText();
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    n->setAttr("name", name);
}

void AstBuilder::enterFunctionArguments(MiniSQLParser::FunctionArgumentsContext* ctx) {
    if (ctx->STAR() && top()) top()->setAttr("star", "*");
}

void AstBuilder::exitFunctionCall(MiniSQLParser::FunctionCallContext*) {
    pop();
}

void AstBuilder::enterInExpression(MiniSQLParser::InExpressionContext* ctx) {
    if (ctx->expressionList()) pushNode("List");
    // 子查询：透传，Select 直接挂到上层 BinaryExpr 的 right 角色。
}

void AstBuilder::exitInExpression(MiniSQLParser::InExpressionContext* ctx) {
    if (ctx->expressionList()) pop();
}

void AstBuilder::enterCaseExpression(MiniSQLParser::CaseExpressionContext*) {
    pushNode("CaseExpr");
}

void AstBuilder::exitCaseExpression(MiniSQLParser::CaseExpressionContext*) {
    pop();
}

void AstBuilder::enterWhenClause(MiniSQLParser::WhenClauseContext*) {
    pushNode("WhenClause");
}

void AstBuilder::exitWhenClause(MiniSQLParser::WhenClauseContext*) {
    pop();
}

}  // namespace waf
