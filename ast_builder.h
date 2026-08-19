#pragma once

#include "ast.h"

#include "MiniSQLBaseListener.h"

namespace waf {

// 把 MiniSQL 解析树折叠成语义 AST。
// 规则引擎只消费 AstNode，不依赖 ANTLR 类型。
class AstBuilder : public MiniSQLBaseListener {
public:
    AstPtr result();

    void enterQueryStatement(MiniSQLParser::QueryStatementContext* ctx) override;
    void exitQueryStatement(MiniSQLParser::QueryStatementContext* ctx) override;

    void enterQueryExpression(MiniSQLParser::QueryExpressionContext* ctx) override;
    void exitQueryExpression(MiniSQLParser::QueryExpressionContext* ctx) override;

    void enterQuerySpecification(MiniSQLParser::QuerySpecificationContext* ctx) override;
    void exitQuerySpecification(MiniSQLParser::QuerySpecificationContext* ctx) override;

    void enterSetQuantifier(MiniSQLParser::SetQuantifierContext* ctx) override;
    void enterSelectList(MiniSQLParser::SelectListContext* ctx) override;
    void enterSelectItem(MiniSQLParser::SelectItemContext* ctx) override;
    void exitSelectItem(MiniSQLParser::SelectItemContext* ctx) override;

    void enterFromClause(MiniSQLParser::FromClauseContext* ctx) override;
    void exitFromClause(MiniSQLParser::FromClauseContext* ctx) override;
    void enterTablePrimary(MiniSQLParser::TablePrimaryContext* ctx) override;
    void exitTablePrimary(MiniSQLParser::TablePrimaryContext* ctx) override;

    void enterWhereClause(MiniSQLParser::WhereClauseContext* ctx) override;
    void exitWhereClause(MiniSQLParser::WhereClauseContext* ctx) override;

    void enterGroupByClause(MiniSQLParser::GroupByClauseContext* ctx) override;
    void exitGroupByClause(MiniSQLParser::GroupByClauseContext* ctx) override;

    void enterHavingClause(MiniSQLParser::HavingClauseContext* ctx) override;
    void exitHavingClause(MiniSQLParser::HavingClauseContext* ctx) override;

    void enterOrderByClause(MiniSQLParser::OrderByClauseContext* ctx) override;
    void exitOrderByClause(MiniSQLParser::OrderByClauseContext* ctx) override;
    void enterOrderItem(MiniSQLParser::OrderItemContext* ctx) override;
    void exitOrderItem(MiniSQLParser::OrderItemContext* ctx) override;

    void enterLimitClause(MiniSQLParser::LimitClauseContext* ctx) override;
    void exitLimitClause(MiniSQLParser::LimitClauseContext* ctx) override;

    void enterOrExpression(MiniSQLParser::OrExpressionContext* ctx) override;
    void exitOrExpression(MiniSQLParser::OrExpressionContext* ctx) override;
    void enterAndExpression(MiniSQLParser::AndExpressionContext* ctx) override;
    void exitAndExpression(MiniSQLParser::AndExpressionContext* ctx) override;
    void enterNotExpression(MiniSQLParser::NotExpressionContext* ctx) override;
    void exitNotExpression(MiniSQLParser::NotExpressionContext* ctx) override;

    void enterComparisonExpression(MiniSQLParser::ComparisonExpressionContext* ctx) override;
    void exitComparisonExpression(MiniSQLParser::ComparisonExpressionContext* ctx) override;

    void enterAdditiveExpression(MiniSQLParser::AdditiveExpressionContext* ctx) override;
    void exitAdditiveExpression(MiniSQLParser::AdditiveExpressionContext* ctx) override;
    void enterMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext* ctx) override;
    void exitMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext* ctx) override;
    void enterUnaryExpression(MiniSQLParser::UnaryExpressionContext* ctx) override;
    void exitUnaryExpression(MiniSQLParser::UnaryExpressionContext* ctx) override;

    void enterLiteral(MiniSQLParser::LiteralContext* ctx) override;
    void exitLiteral(MiniSQLParser::LiteralContext* ctx) override;
    void enterColumnReference(MiniSQLParser::ColumnReferenceContext* ctx) override;
    void exitColumnReference(MiniSQLParser::ColumnReferenceContext* ctx) override;
    void enterFunctionCall(MiniSQLParser::FunctionCallContext* ctx) override;
    void enterFunctionArguments(MiniSQLParser::FunctionArgumentsContext* ctx) override;
    void exitFunctionCall(MiniSQLParser::FunctionCallContext* ctx) override;

    void enterInExpression(MiniSQLParser::InExpressionContext* ctx) override;
    void exitInExpression(MiniSQLParser::InExpressionContext* ctx) override;

    void enterCaseExpression(MiniSQLParser::CaseExpressionContext* ctx) override;
    void exitCaseExpression(MiniSQLParser::CaseExpressionContext* ctx) override;
    void enterWhenClause(MiniSQLParser::WhenClauseContext* ctx) override;
    void exitWhenClause(MiniSQLParser::WhenClauseContext* ctx) override;

private:
    AstPtr root_;
    std::vector<AstNode*> stack_;
    std::vector<bool> subqueryStack_;  // 顶层 Query 之外出现的 queryExpression = 子查询

    AstNode* top();
    AstNode* pushNode(const std::string& kind);
    void pop();

    // 把当前 top 上 n 个平铺子节点折叠成左结合二元链（a OP1 b OP2 c -> ((a OP1 b) OP2 c)）。
    void foldBinaryChain(const std::vector<std::string>& ops);
};

}  // namespace waf
