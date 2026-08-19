
// Generated from MiniSQL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MiniSQLParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by MiniSQLParser.
 */
class  MiniSQLListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSql(MiniSQLParser::SqlContext *ctx) = 0;
  virtual void exitSql(MiniSQLParser::SqlContext *ctx) = 0;

  virtual void enterStatement(MiniSQLParser::StatementContext *ctx) = 0;
  virtual void exitStatement(MiniSQLParser::StatementContext *ctx) = 0;

  virtual void enterQueryStatement(MiniSQLParser::QueryStatementContext *ctx) = 0;
  virtual void exitQueryStatement(MiniSQLParser::QueryStatementContext *ctx) = 0;

  virtual void enterWithClause(MiniSQLParser::WithClauseContext *ctx) = 0;
  virtual void exitWithClause(MiniSQLParser::WithClauseContext *ctx) = 0;

  virtual void enterCte(MiniSQLParser::CteContext *ctx) = 0;
  virtual void exitCte(MiniSQLParser::CteContext *ctx) = 0;

  virtual void enterColumnAliasList(MiniSQLParser::ColumnAliasListContext *ctx) = 0;
  virtual void exitColumnAliasList(MiniSQLParser::ColumnAliasListContext *ctx) = 0;

  virtual void enterQueryExpression(MiniSQLParser::QueryExpressionContext *ctx) = 0;
  virtual void exitQueryExpression(MiniSQLParser::QueryExpressionContext *ctx) = 0;

  virtual void enterQueryTerm(MiniSQLParser::QueryTermContext *ctx) = 0;
  virtual void exitQueryTerm(MiniSQLParser::QueryTermContext *ctx) = 0;

  virtual void enterQuerySpecification(MiniSQLParser::QuerySpecificationContext *ctx) = 0;
  virtual void exitQuerySpecification(MiniSQLParser::QuerySpecificationContext *ctx) = 0;

  virtual void enterSetQuantifier(MiniSQLParser::SetQuantifierContext *ctx) = 0;
  virtual void exitSetQuantifier(MiniSQLParser::SetQuantifierContext *ctx) = 0;

  virtual void enterSelectList(MiniSQLParser::SelectListContext *ctx) = 0;
  virtual void exitSelectList(MiniSQLParser::SelectListContext *ctx) = 0;

  virtual void enterSelectItem(MiniSQLParser::SelectItemContext *ctx) = 0;
  virtual void exitSelectItem(MiniSQLParser::SelectItemContext *ctx) = 0;

  virtual void enterFromClause(MiniSQLParser::FromClauseContext *ctx) = 0;
  virtual void exitFromClause(MiniSQLParser::FromClauseContext *ctx) = 0;

  virtual void enterTableReference(MiniSQLParser::TableReferenceContext *ctx) = 0;
  virtual void exitTableReference(MiniSQLParser::TableReferenceContext *ctx) = 0;

  virtual void enterTablePrimary(MiniSQLParser::TablePrimaryContext *ctx) = 0;
  virtual void exitTablePrimary(MiniSQLParser::TablePrimaryContext *ctx) = 0;

  virtual void enterJoinClause(MiniSQLParser::JoinClauseContext *ctx) = 0;
  virtual void exitJoinClause(MiniSQLParser::JoinClauseContext *ctx) = 0;

  virtual void enterJoinType(MiniSQLParser::JoinTypeContext *ctx) = 0;
  virtual void exitJoinType(MiniSQLParser::JoinTypeContext *ctx) = 0;

  virtual void enterJoinCondition(MiniSQLParser::JoinConditionContext *ctx) = 0;
  virtual void exitJoinCondition(MiniSQLParser::JoinConditionContext *ctx) = 0;

  virtual void enterWhereClause(MiniSQLParser::WhereClauseContext *ctx) = 0;
  virtual void exitWhereClause(MiniSQLParser::WhereClauseContext *ctx) = 0;

  virtual void enterGroupByClause(MiniSQLParser::GroupByClauseContext *ctx) = 0;
  virtual void exitGroupByClause(MiniSQLParser::GroupByClauseContext *ctx) = 0;

  virtual void enterHavingClause(MiniSQLParser::HavingClauseContext *ctx) = 0;
  virtual void exitHavingClause(MiniSQLParser::HavingClauseContext *ctx) = 0;

  virtual void enterOrderByClause(MiniSQLParser::OrderByClauseContext *ctx) = 0;
  virtual void exitOrderByClause(MiniSQLParser::OrderByClauseContext *ctx) = 0;

  virtual void enterOrderItem(MiniSQLParser::OrderItemContext *ctx) = 0;
  virtual void exitOrderItem(MiniSQLParser::OrderItemContext *ctx) = 0;

  virtual void enterLimitClause(MiniSQLParser::LimitClauseContext *ctx) = 0;
  virtual void exitLimitClause(MiniSQLParser::LimitClauseContext *ctx) = 0;

  virtual void enterExpression(MiniSQLParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(MiniSQLParser::ExpressionContext *ctx) = 0;

  virtual void enterOrExpression(MiniSQLParser::OrExpressionContext *ctx) = 0;
  virtual void exitOrExpression(MiniSQLParser::OrExpressionContext *ctx) = 0;

  virtual void enterAndExpression(MiniSQLParser::AndExpressionContext *ctx) = 0;
  virtual void exitAndExpression(MiniSQLParser::AndExpressionContext *ctx) = 0;

  virtual void enterNotExpression(MiniSQLParser::NotExpressionContext *ctx) = 0;
  virtual void exitNotExpression(MiniSQLParser::NotExpressionContext *ctx) = 0;

  virtual void enterComparisonExpression(MiniSQLParser::ComparisonExpressionContext *ctx) = 0;
  virtual void exitComparisonExpression(MiniSQLParser::ComparisonExpressionContext *ctx) = 0;

  virtual void enterComparisonOperator(MiniSQLParser::ComparisonOperatorContext *ctx) = 0;
  virtual void exitComparisonOperator(MiniSQLParser::ComparisonOperatorContext *ctx) = 0;

  virtual void enterAdditiveExpression(MiniSQLParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(MiniSQLParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(MiniSQLParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(MiniSQLParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpression(MiniSQLParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(MiniSQLParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterColumnReference(MiniSQLParser::ColumnReferenceContext *ctx) = 0;
  virtual void exitColumnReference(MiniSQLParser::ColumnReferenceContext *ctx) = 0;

  virtual void enterFunctionCall(MiniSQLParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(MiniSQLParser::FunctionCallContext *ctx) = 0;

  virtual void enterFunctionArguments(MiniSQLParser::FunctionArgumentsContext *ctx) = 0;
  virtual void exitFunctionArguments(MiniSQLParser::FunctionArgumentsContext *ctx) = 0;

  virtual void enterCaseExpression(MiniSQLParser::CaseExpressionContext *ctx) = 0;
  virtual void exitCaseExpression(MiniSQLParser::CaseExpressionContext *ctx) = 0;

  virtual void enterWhenClause(MiniSQLParser::WhenClauseContext *ctx) = 0;
  virtual void exitWhenClause(MiniSQLParser::WhenClauseContext *ctx) = 0;

  virtual void enterInExpression(MiniSQLParser::InExpressionContext *ctx) = 0;
  virtual void exitInExpression(MiniSQLParser::InExpressionContext *ctx) = 0;

  virtual void enterExpressionList(MiniSQLParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(MiniSQLParser::ExpressionListContext *ctx) = 0;

  virtual void enterLiteral(MiniSQLParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(MiniSQLParser::LiteralContext *ctx) = 0;

  virtual void enterIdentifier(MiniSQLParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(MiniSQLParser::IdentifierContext *ctx) = 0;


};

