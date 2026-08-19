
// Generated from MiniSQL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MiniSQLListener.h"


/**
 * This class provides an empty implementation of MiniSQLListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  MiniSQLBaseListener : public MiniSQLListener {
public:

  virtual void enterSql(MiniSQLParser::SqlContext * /*ctx*/) override { }
  virtual void exitSql(MiniSQLParser::SqlContext * /*ctx*/) override { }

  virtual void enterStatement(MiniSQLParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(MiniSQLParser::StatementContext * /*ctx*/) override { }

  virtual void enterQueryStatement(MiniSQLParser::QueryStatementContext * /*ctx*/) override { }
  virtual void exitQueryStatement(MiniSQLParser::QueryStatementContext * /*ctx*/) override { }

  virtual void enterWithClause(MiniSQLParser::WithClauseContext * /*ctx*/) override { }
  virtual void exitWithClause(MiniSQLParser::WithClauseContext * /*ctx*/) override { }

  virtual void enterCte(MiniSQLParser::CteContext * /*ctx*/) override { }
  virtual void exitCte(MiniSQLParser::CteContext * /*ctx*/) override { }

  virtual void enterColumnAliasList(MiniSQLParser::ColumnAliasListContext * /*ctx*/) override { }
  virtual void exitColumnAliasList(MiniSQLParser::ColumnAliasListContext * /*ctx*/) override { }

  virtual void enterQueryExpression(MiniSQLParser::QueryExpressionContext * /*ctx*/) override { }
  virtual void exitQueryExpression(MiniSQLParser::QueryExpressionContext * /*ctx*/) override { }

  virtual void enterQueryTerm(MiniSQLParser::QueryTermContext * /*ctx*/) override { }
  virtual void exitQueryTerm(MiniSQLParser::QueryTermContext * /*ctx*/) override { }

  virtual void enterQuerySpecification(MiniSQLParser::QuerySpecificationContext * /*ctx*/) override { }
  virtual void exitQuerySpecification(MiniSQLParser::QuerySpecificationContext * /*ctx*/) override { }

  virtual void enterSetQuantifier(MiniSQLParser::SetQuantifierContext * /*ctx*/) override { }
  virtual void exitSetQuantifier(MiniSQLParser::SetQuantifierContext * /*ctx*/) override { }

  virtual void enterSelectList(MiniSQLParser::SelectListContext * /*ctx*/) override { }
  virtual void exitSelectList(MiniSQLParser::SelectListContext * /*ctx*/) override { }

  virtual void enterSelectItem(MiniSQLParser::SelectItemContext * /*ctx*/) override { }
  virtual void exitSelectItem(MiniSQLParser::SelectItemContext * /*ctx*/) override { }

  virtual void enterFromClause(MiniSQLParser::FromClauseContext * /*ctx*/) override { }
  virtual void exitFromClause(MiniSQLParser::FromClauseContext * /*ctx*/) override { }

  virtual void enterTableReference(MiniSQLParser::TableReferenceContext * /*ctx*/) override { }
  virtual void exitTableReference(MiniSQLParser::TableReferenceContext * /*ctx*/) override { }

  virtual void enterTablePrimary(MiniSQLParser::TablePrimaryContext * /*ctx*/) override { }
  virtual void exitTablePrimary(MiniSQLParser::TablePrimaryContext * /*ctx*/) override { }

  virtual void enterJoinClause(MiniSQLParser::JoinClauseContext * /*ctx*/) override { }
  virtual void exitJoinClause(MiniSQLParser::JoinClauseContext * /*ctx*/) override { }

  virtual void enterJoinType(MiniSQLParser::JoinTypeContext * /*ctx*/) override { }
  virtual void exitJoinType(MiniSQLParser::JoinTypeContext * /*ctx*/) override { }

  virtual void enterJoinCondition(MiniSQLParser::JoinConditionContext * /*ctx*/) override { }
  virtual void exitJoinCondition(MiniSQLParser::JoinConditionContext * /*ctx*/) override { }

  virtual void enterWhereClause(MiniSQLParser::WhereClauseContext * /*ctx*/) override { }
  virtual void exitWhereClause(MiniSQLParser::WhereClauseContext * /*ctx*/) override { }

  virtual void enterGroupByClause(MiniSQLParser::GroupByClauseContext * /*ctx*/) override { }
  virtual void exitGroupByClause(MiniSQLParser::GroupByClauseContext * /*ctx*/) override { }

  virtual void enterHavingClause(MiniSQLParser::HavingClauseContext * /*ctx*/) override { }
  virtual void exitHavingClause(MiniSQLParser::HavingClauseContext * /*ctx*/) override { }

  virtual void enterOrderByClause(MiniSQLParser::OrderByClauseContext * /*ctx*/) override { }
  virtual void exitOrderByClause(MiniSQLParser::OrderByClauseContext * /*ctx*/) override { }

  virtual void enterOrderItem(MiniSQLParser::OrderItemContext * /*ctx*/) override { }
  virtual void exitOrderItem(MiniSQLParser::OrderItemContext * /*ctx*/) override { }

  virtual void enterLimitClause(MiniSQLParser::LimitClauseContext * /*ctx*/) override { }
  virtual void exitLimitClause(MiniSQLParser::LimitClauseContext * /*ctx*/) override { }

  virtual void enterExpression(MiniSQLParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(MiniSQLParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterOrExpression(MiniSQLParser::OrExpressionContext * /*ctx*/) override { }
  virtual void exitOrExpression(MiniSQLParser::OrExpressionContext * /*ctx*/) override { }

  virtual void enterAndExpression(MiniSQLParser::AndExpressionContext * /*ctx*/) override { }
  virtual void exitAndExpression(MiniSQLParser::AndExpressionContext * /*ctx*/) override { }

  virtual void enterNotExpression(MiniSQLParser::NotExpressionContext * /*ctx*/) override { }
  virtual void exitNotExpression(MiniSQLParser::NotExpressionContext * /*ctx*/) override { }

  virtual void enterComparisonExpression(MiniSQLParser::ComparisonExpressionContext * /*ctx*/) override { }
  virtual void exitComparisonExpression(MiniSQLParser::ComparisonExpressionContext * /*ctx*/) override { }

  virtual void enterComparisonOperator(MiniSQLParser::ComparisonOperatorContext * /*ctx*/) override { }
  virtual void exitComparisonOperator(MiniSQLParser::ComparisonOperatorContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(MiniSQLParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(MiniSQLParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(MiniSQLParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(MiniSQLParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(MiniSQLParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(MiniSQLParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(MiniSQLParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterColumnReference(MiniSQLParser::ColumnReferenceContext * /*ctx*/) override { }
  virtual void exitColumnReference(MiniSQLParser::ColumnReferenceContext * /*ctx*/) override { }

  virtual void enterFunctionCall(MiniSQLParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(MiniSQLParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterFunctionArguments(MiniSQLParser::FunctionArgumentsContext * /*ctx*/) override { }
  virtual void exitFunctionArguments(MiniSQLParser::FunctionArgumentsContext * /*ctx*/) override { }

  virtual void enterCaseExpression(MiniSQLParser::CaseExpressionContext * /*ctx*/) override { }
  virtual void exitCaseExpression(MiniSQLParser::CaseExpressionContext * /*ctx*/) override { }

  virtual void enterWhenClause(MiniSQLParser::WhenClauseContext * /*ctx*/) override { }
  virtual void exitWhenClause(MiniSQLParser::WhenClauseContext * /*ctx*/) override { }

  virtual void enterInExpression(MiniSQLParser::InExpressionContext * /*ctx*/) override { }
  virtual void exitInExpression(MiniSQLParser::InExpressionContext * /*ctx*/) override { }

  virtual void enterExpressionList(MiniSQLParser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(MiniSQLParser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterLiteral(MiniSQLParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(MiniSQLParser::LiteralContext * /*ctx*/) override { }

  virtual void enterIdentifier(MiniSQLParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(MiniSQLParser::IdentifierContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

