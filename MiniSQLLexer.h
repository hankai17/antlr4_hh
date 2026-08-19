
// Generated from MiniSQL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MiniSQLLexer : public antlr4::Lexer {
public:
  enum {
    WITH = 1, RECURSIVE = 2, SELECT = 3, FROM = 4, WHERE = 5, GROUP = 6, 
    BY = 7, HAVING = 8, ORDER = 9, LIMIT = 10, OFFSET = 11, UNION = 12, 
    ALL = 13, DISTINCT = 14, JOIN = 15, INNER = 16, LEFT = 17, RIGHT = 18, 
    FULL = 19, OUTER = 20, CROSS = 21, ON = 22, USING = 23, AS = 24, AND = 25, 
    OR = 26, NOT = 27, IN = 28, LIKE = 29, BETWEEN = 30, EXISTS = 31, IS = 32, 
    NULL_ = 33, TRUE = 34, FALSE = 35, ASC = 36, DESC = 37, CASE = 38, WHEN = 39, 
    THEN = 40, ELSE = 41, END = 42, EQ = 43, NE = 44, LE = 45, GE = 46, 
    LT = 47, GT = 48, PLUS = 49, MINUS = 50, STAR = 51, DIV = 52, MOD = 53, 
    LPAREN = 54, RPAREN = 55, COMMA = 56, DOT = 57, NUMBER = 58, STRING = 59, 
    QUOTED_IDENTIFIER = 60, IDENTIFIER = 61, WS = 62, COMMENT = 63, BLOCK_COMMENT = 64
  };

  explicit MiniSQLLexer(antlr4::CharStream *input);

  ~MiniSQLLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

