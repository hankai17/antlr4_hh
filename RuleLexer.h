
// Generated from Rule.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  RuleLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    RULE = 8, SEVERITY_KW = 9, ACTION_KW = 10, PROFILE_KW = 11, DESCRIPTION_KW = 12, 
    PATTERN_KW = 13, SEVERITY = 14, ACTION = 15, PROFILE = 16, BOOL = 17, 
    IDENT = 18, STRING = 19, WS = 20, LINE_COMMENT = 21, BLOCK_COMMENT = 22
  };

  explicit RuleLexer(antlr4::CharStream *input);

  ~RuleLexer() override;


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

