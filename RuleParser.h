
// Generated from Rule.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  RuleParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    RULE = 8, SEVERITY_KW = 9, ACTION_KW = 10, PROFILE_KW = 11, DESCRIPTION_KW = 12, 
    PATTERN_KW = 13, SEVERITY = 14, ACTION = 15, PROFILE = 16, BOOL = 17, 
    IDENT = 18, STRING = 19, WS = 20, LINE_COMMENT = 21, BLOCK_COMMENT = 22
  };

  enum {
    RuleRuleFile = 0, RuleRuleDef = 1, RuleProperty = 2, RulePatternDef = 3, 
    RuleNodePattern = 4, RulePatternArgList = 5, RulePatternArg = 6
  };

  explicit RuleParser(antlr4::TokenStream *input);

  RuleParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~RuleParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RuleFileContext;
  class RuleDefContext;
  class PropertyContext;
  class PatternDefContext;
  class NodePatternContext;
  class PatternArgListContext;
  class PatternArgContext; 

  class  RuleFileContext : public antlr4::ParserRuleContext {
  public:
    RuleFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RuleDefContext *> ruleDef();
    RuleDefContext* ruleDef(size_t i);

   
  };

  RuleFileContext* ruleFile();

  class  RuleDefContext : public antlr4::ParserRuleContext {
  public:
    RuleDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *IDENT();
    PatternDefContext *patternDef();
    std::vector<PropertyContext *> property();
    PropertyContext* property(size_t i);

   
  };

  RuleDefContext* ruleDef();

  class  PropertyContext : public antlr4::ParserRuleContext {
  public:
    PropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEVERITY_KW();
    antlr4::tree::TerminalNode *SEVERITY();
    antlr4::tree::TerminalNode *ACTION_KW();
    antlr4::tree::TerminalNode *ACTION();
    antlr4::tree::TerminalNode *PROFILE_KW();
    antlr4::tree::TerminalNode *PROFILE();
    antlr4::tree::TerminalNode *DESCRIPTION_KW();
    antlr4::tree::TerminalNode *STRING();

   
  };

  PropertyContext* property();

  class  PatternDefContext : public antlr4::ParserRuleContext {
  public:
    PatternDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PATTERN_KW();
    NodePatternContext *nodePattern();

   
  };

  PatternDefContext* patternDef();

  class  NodePatternContext : public antlr4::ParserRuleContext {
  public:
    NodePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    PatternArgListContext *patternArgList();

   
  };

  NodePatternContext* nodePattern();

  class  PatternArgListContext : public antlr4::ParserRuleContext {
  public:
    PatternArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PatternArgContext *> patternArg();
    PatternArgContext* patternArg(size_t i);

   
  };

  PatternArgListContext* patternArgList();

  class  PatternArgContext : public antlr4::ParserRuleContext {
  public:
    PatternArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BOOL();
    NodePatternContext *nodePattern();

   
  };

  PatternArgContext* patternArg();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

