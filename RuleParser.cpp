
// Generated from Rule.g4 by ANTLR 4.13.2



#include "RuleParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct RuleParserStaticData final {
  RuleParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  RuleParserStaticData(const RuleParserStaticData&) = delete;
  RuleParserStaticData(RuleParserStaticData&&) = delete;
  RuleParserStaticData& operator=(const RuleParserStaticData&) = delete;
  RuleParserStaticData& operator=(RuleParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ruleParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<RuleParserStaticData> ruleParserStaticData = nullptr;

void ruleParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ruleParserStaticData != nullptr) {
    return;
  }
#else
  assert(ruleParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<RuleParserStaticData>(
    std::vector<std::string>{
      "ruleFile", "ruleDef", "property", "patternDef", "nodePattern", "patternArgList", 
      "patternArg"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "':'", "'('", "')'", "','", "'rule'", "'severity'", 
      "'action'", "'profile'", "'description'", "'pattern'", "'='", "'.'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "RULE", "SEVERITY_KW", "ACTION_KW", "PROFILE_KW", 
      "DESCRIPTION_KW", "PATTERN_KW", "EQ", "DOT", "SEVERITY", "ACTION", 
      "PROFILE", "BOOL", "IDENT", "STRING", "WS", "LINE_COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,23,87,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,1,0,
  	4,0,16,8,0,11,0,12,0,17,1,1,1,1,1,1,1,1,5,1,24,8,1,10,1,12,1,27,9,1,1,
  	1,4,1,30,8,1,11,1,12,1,31,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,48,8,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,3,4,57,8,4,1,4,1,4,
  	1,5,1,5,1,5,5,5,64,8,5,10,5,12,5,67,9,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,85,8,6,1,6,0,0,7,0,2,4,6,8,10,12,
  	0,0,90,0,15,1,0,0,0,2,19,1,0,0,0,4,47,1,0,0,0,6,49,1,0,0,0,8,53,1,0,0,
  	0,10,60,1,0,0,0,12,84,1,0,0,0,14,16,3,2,1,0,15,14,1,0,0,0,16,17,1,0,0,
  	0,17,15,1,0,0,0,17,18,1,0,0,0,18,1,1,0,0,0,19,20,5,7,0,0,20,21,5,19,0,
  	0,21,25,5,1,0,0,22,24,3,4,2,0,23,22,1,0,0,0,24,27,1,0,0,0,25,23,1,0,0,
  	0,25,26,1,0,0,0,26,29,1,0,0,0,27,25,1,0,0,0,28,30,3,6,3,0,29,28,1,0,0,
  	0,30,31,1,0,0,0,31,29,1,0,0,0,31,32,1,0,0,0,32,33,1,0,0,0,33,34,5,2,0,
  	0,34,3,1,0,0,0,35,36,5,8,0,0,36,37,5,3,0,0,37,48,5,15,0,0,38,39,5,9,0,
  	0,39,40,5,3,0,0,40,48,5,16,0,0,41,42,5,10,0,0,42,43,5,3,0,0,43,48,5,17,
  	0,0,44,45,5,11,0,0,45,46,5,3,0,0,46,48,5,20,0,0,47,35,1,0,0,0,47,38,1,
  	0,0,0,47,41,1,0,0,0,47,44,1,0,0,0,48,5,1,0,0,0,49,50,5,12,0,0,50,51,5,
  	3,0,0,51,52,3,8,4,0,52,7,1,0,0,0,53,54,5,19,0,0,54,56,5,4,0,0,55,57,3,
  	10,5,0,56,55,1,0,0,0,56,57,1,0,0,0,57,58,1,0,0,0,58,59,5,5,0,0,59,9,1,
  	0,0,0,60,65,3,12,6,0,61,62,5,6,0,0,62,64,3,12,6,0,63,61,1,0,0,0,64,67,
  	1,0,0,0,65,63,1,0,0,0,65,66,1,0,0,0,66,11,1,0,0,0,67,65,1,0,0,0,68,69,
  	5,19,0,0,69,70,5,13,0,0,70,85,5,20,0,0,71,72,5,19,0,0,72,73,5,13,0,0,
  	73,85,5,18,0,0,74,75,5,19,0,0,75,76,5,13,0,0,76,85,3,8,4,0,77,78,5,19,
  	0,0,78,79,5,14,0,0,79,80,5,19,0,0,80,81,5,13,0,0,81,82,5,19,0,0,82,83,
  	5,14,0,0,83,85,5,19,0,0,84,68,1,0,0,0,84,71,1,0,0,0,84,74,1,0,0,0,84,
  	77,1,0,0,0,85,13,1,0,0,0,7,17,25,31,47,56,65,84
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ruleParserStaticData = std::move(staticData);
}

}

RuleParser::RuleParser(TokenStream *input) : RuleParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

RuleParser::RuleParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  RuleParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ruleParserStaticData->atn, ruleParserStaticData->decisionToDFA, ruleParserStaticData->sharedContextCache, options);
}

RuleParser::~RuleParser() {
  delete _interpreter;
}

const atn::ATN& RuleParser::getATN() const {
  return *ruleParserStaticData->atn;
}

std::string RuleParser::getGrammarFileName() const {
  return "Rule.g4";
}

const std::vector<std::string>& RuleParser::getRuleNames() const {
  return ruleParserStaticData->ruleNames;
}

const dfa::Vocabulary& RuleParser::getVocabulary() const {
  return ruleParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView RuleParser::getSerializedATN() const {
  return ruleParserStaticData->serializedATN;
}


//----------------- RuleFileContext ------------------------------------------------------------------

RuleParser::RuleFileContext::RuleFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RuleParser::RuleDefContext *> RuleParser::RuleFileContext::ruleDef() {
  return getRuleContexts<RuleParser::RuleDefContext>();
}

RuleParser::RuleDefContext* RuleParser::RuleFileContext::ruleDef(size_t i) {
  return getRuleContext<RuleParser::RuleDefContext>(i);
}


size_t RuleParser::RuleFileContext::getRuleIndex() const {
  return RuleParser::RuleRuleFile;
}


RuleParser::RuleFileContext* RuleParser::ruleFile() {
  RuleFileContext *_localctx = _tracker.createInstance<RuleFileContext>(_ctx, getState());
  enterRule(_localctx, 0, RuleParser::RuleRuleFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(15); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(14);
      ruleDef();
      setState(17); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == RuleParser::RULE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuleDefContext ------------------------------------------------------------------

RuleParser::RuleDefContext::RuleDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RuleParser::RuleDefContext::RULE() {
  return getToken(RuleParser::RULE, 0);
}

tree::TerminalNode* RuleParser::RuleDefContext::IDENT() {
  return getToken(RuleParser::IDENT, 0);
}

std::vector<RuleParser::PropertyContext *> RuleParser::RuleDefContext::property() {
  return getRuleContexts<RuleParser::PropertyContext>();
}

RuleParser::PropertyContext* RuleParser::RuleDefContext::property(size_t i) {
  return getRuleContext<RuleParser::PropertyContext>(i);
}

std::vector<RuleParser::PatternDefContext *> RuleParser::RuleDefContext::patternDef() {
  return getRuleContexts<RuleParser::PatternDefContext>();
}

RuleParser::PatternDefContext* RuleParser::RuleDefContext::patternDef(size_t i) {
  return getRuleContext<RuleParser::PatternDefContext>(i);
}


size_t RuleParser::RuleDefContext::getRuleIndex() const {
  return RuleParser::RuleRuleDef;
}


RuleParser::RuleDefContext* RuleParser::ruleDef() {
  RuleDefContext *_localctx = _tracker.createInstance<RuleDefContext>(_ctx, getState());
  enterRule(_localctx, 2, RuleParser::RuleRuleDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(19);
    match(RuleParser::RULE);
    setState(20);
    match(RuleParser::IDENT);
    setState(21);
    match(RuleParser::T__0);
    setState(25);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3840) != 0)) {
      setState(22);
      property();
      setState(27);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(29); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(28);
      patternDef();
      setState(31); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == RuleParser::PATTERN_KW);
    setState(33);
    match(RuleParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyContext ------------------------------------------------------------------

RuleParser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RuleParser::PropertyContext::SEVERITY_KW() {
  return getToken(RuleParser::SEVERITY_KW, 0);
}

tree::TerminalNode* RuleParser::PropertyContext::SEVERITY() {
  return getToken(RuleParser::SEVERITY, 0);
}

tree::TerminalNode* RuleParser::PropertyContext::ACTION_KW() {
  return getToken(RuleParser::ACTION_KW, 0);
}

tree::TerminalNode* RuleParser::PropertyContext::ACTION() {
  return getToken(RuleParser::ACTION, 0);
}

tree::TerminalNode* RuleParser::PropertyContext::PROFILE_KW() {
  return getToken(RuleParser::PROFILE_KW, 0);
}

tree::TerminalNode* RuleParser::PropertyContext::PROFILE() {
  return getToken(RuleParser::PROFILE, 0);
}

tree::TerminalNode* RuleParser::PropertyContext::DESCRIPTION_KW() {
  return getToken(RuleParser::DESCRIPTION_KW, 0);
}

tree::TerminalNode* RuleParser::PropertyContext::STRING() {
  return getToken(RuleParser::STRING, 0);
}


size_t RuleParser::PropertyContext::getRuleIndex() const {
  return RuleParser::RuleProperty;
}


RuleParser::PropertyContext* RuleParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 4, RuleParser::RuleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(47);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case RuleParser::SEVERITY_KW: {
        enterOuterAlt(_localctx, 1);
        setState(35);
        match(RuleParser::SEVERITY_KW);
        setState(36);
        match(RuleParser::T__2);
        setState(37);
        match(RuleParser::SEVERITY);
        break;
      }

      case RuleParser::ACTION_KW: {
        enterOuterAlt(_localctx, 2);
        setState(38);
        match(RuleParser::ACTION_KW);
        setState(39);
        match(RuleParser::T__2);
        setState(40);
        match(RuleParser::ACTION);
        break;
      }

      case RuleParser::PROFILE_KW: {
        enterOuterAlt(_localctx, 3);
        setState(41);
        match(RuleParser::PROFILE_KW);
        setState(42);
        match(RuleParser::T__2);
        setState(43);
        match(RuleParser::PROFILE);
        break;
      }

      case RuleParser::DESCRIPTION_KW: {
        enterOuterAlt(_localctx, 4);
        setState(44);
        match(RuleParser::DESCRIPTION_KW);
        setState(45);
        match(RuleParser::T__2);
        setState(46);
        match(RuleParser::STRING);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternDefContext ------------------------------------------------------------------

RuleParser::PatternDefContext::PatternDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RuleParser::PatternDefContext::PATTERN_KW() {
  return getToken(RuleParser::PATTERN_KW, 0);
}

RuleParser::NodePatternContext* RuleParser::PatternDefContext::nodePattern() {
  return getRuleContext<RuleParser::NodePatternContext>(0);
}


size_t RuleParser::PatternDefContext::getRuleIndex() const {
  return RuleParser::RulePatternDef;
}


RuleParser::PatternDefContext* RuleParser::patternDef() {
  PatternDefContext *_localctx = _tracker.createInstance<PatternDefContext>(_ctx, getState());
  enterRule(_localctx, 6, RuleParser::RulePatternDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    match(RuleParser::PATTERN_KW);
    setState(50);
    match(RuleParser::T__2);
    setState(51);
    nodePattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NodePatternContext ------------------------------------------------------------------

RuleParser::NodePatternContext::NodePatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* RuleParser::NodePatternContext::IDENT() {
  return getToken(RuleParser::IDENT, 0);
}

RuleParser::PatternArgListContext* RuleParser::NodePatternContext::patternArgList() {
  return getRuleContext<RuleParser::PatternArgListContext>(0);
}


size_t RuleParser::NodePatternContext::getRuleIndex() const {
  return RuleParser::RuleNodePattern;
}


RuleParser::NodePatternContext* RuleParser::nodePattern() {
  NodePatternContext *_localctx = _tracker.createInstance<NodePatternContext>(_ctx, getState());
  enterRule(_localctx, 8, RuleParser::RuleNodePattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    match(RuleParser::IDENT);
    setState(54);
    match(RuleParser::T__3);
    setState(56);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == RuleParser::IDENT) {
      setState(55);
      patternArgList();
    }
    setState(58);
    match(RuleParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternArgListContext ------------------------------------------------------------------

RuleParser::PatternArgListContext::PatternArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<RuleParser::PatternArgContext *> RuleParser::PatternArgListContext::patternArg() {
  return getRuleContexts<RuleParser::PatternArgContext>();
}

RuleParser::PatternArgContext* RuleParser::PatternArgListContext::patternArg(size_t i) {
  return getRuleContext<RuleParser::PatternArgContext>(i);
}


size_t RuleParser::PatternArgListContext::getRuleIndex() const {
  return RuleParser::RulePatternArgList;
}


RuleParser::PatternArgListContext* RuleParser::patternArgList() {
  PatternArgListContext *_localctx = _tracker.createInstance<PatternArgListContext>(_ctx, getState());
  enterRule(_localctx, 10, RuleParser::RulePatternArgList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(60);
    patternArg();
    setState(65);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == RuleParser::T__5) {
      setState(61);
      match(RuleParser::T__5);
      setState(62);
      patternArg();
      setState(67);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternArgContext ------------------------------------------------------------------

RuleParser::PatternArgContext::PatternArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> RuleParser::PatternArgContext::IDENT() {
  return getTokens(RuleParser::IDENT);
}

tree::TerminalNode* RuleParser::PatternArgContext::IDENT(size_t i) {
  return getToken(RuleParser::IDENT, i);
}

tree::TerminalNode* RuleParser::PatternArgContext::EQ() {
  return getToken(RuleParser::EQ, 0);
}

tree::TerminalNode* RuleParser::PatternArgContext::STRING() {
  return getToken(RuleParser::STRING, 0);
}

tree::TerminalNode* RuleParser::PatternArgContext::BOOL() {
  return getToken(RuleParser::BOOL, 0);
}

RuleParser::NodePatternContext* RuleParser::PatternArgContext::nodePattern() {
  return getRuleContext<RuleParser::NodePatternContext>(0);
}

std::vector<tree::TerminalNode *> RuleParser::PatternArgContext::DOT() {
  return getTokens(RuleParser::DOT);
}

tree::TerminalNode* RuleParser::PatternArgContext::DOT(size_t i) {
  return getToken(RuleParser::DOT, i);
}


size_t RuleParser::PatternArgContext::getRuleIndex() const {
  return RuleParser::RulePatternArg;
}


RuleParser::PatternArgContext* RuleParser::patternArg() {
  PatternArgContext *_localctx = _tracker.createInstance<PatternArgContext>(_ctx, getState());
  enterRule(_localctx, 12, RuleParser::RulePatternArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(84);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(68);
      match(RuleParser::IDENT);
      setState(69);
      match(RuleParser::EQ);
      setState(70);
      match(RuleParser::STRING);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(71);
      match(RuleParser::IDENT);
      setState(72);
      match(RuleParser::EQ);
      setState(73);
      match(RuleParser::BOOL);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(74);
      match(RuleParser::IDENT);
      setState(75);
      match(RuleParser::EQ);
      setState(76);
      nodePattern();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(77);
      match(RuleParser::IDENT);
      setState(78);
      match(RuleParser::DOT);
      setState(79);
      match(RuleParser::IDENT);
      setState(80);
      match(RuleParser::EQ);
      setState(81);
      match(RuleParser::IDENT);
      setState(82);
      match(RuleParser::DOT);
      setState(83);
      match(RuleParser::IDENT);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void RuleParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ruleParserInitialize();
#else
  ::antlr4::internal::call_once(ruleParserOnceFlag, ruleParserInitialize);
#endif
}
