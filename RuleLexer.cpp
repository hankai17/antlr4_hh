
// Generated from Rule.g4 by ANTLR 4.13.2


#include "RuleLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct RuleLexerStaticData final {
  RuleLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  RuleLexerStaticData(const RuleLexerStaticData&) = delete;
  RuleLexerStaticData(RuleLexerStaticData&&) = delete;
  RuleLexerStaticData& operator=(const RuleLexerStaticData&) = delete;
  RuleLexerStaticData& operator=(RuleLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag rulelexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<RuleLexerStaticData> rulelexerLexerStaticData = nullptr;

void rulelexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (rulelexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(rulelexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<RuleLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "RULE", "SEVERITY_KW", 
      "ACTION_KW", "PROFILE_KW", "DESCRIPTION_KW", "PATTERN_KW", "SEVERITY", 
      "ACTION", "PROFILE", "BOOL", "IDENT", "STRING", "WS", "LINE_COMMENT", 
      "BLOCK_COMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'{'", "'}'", "':'", "'('", "')'", "','", "'='", "'rule'", "'severity'", 
      "'action'", "'profile'", "'description'", "'pattern'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "RULE", "SEVERITY_KW", "ACTION_KW", 
      "PROFILE_KW", "DESCRIPTION_KW", "PATTERN_KW", "SEVERITY", "ACTION", 
      "PROFILE", "BOOL", "IDENT", "STRING", "WS", "LINE_COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,22,221,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,
  	1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,130,8,13,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,142,8,14,1,15,1,15,1,15,1,15,
  	1,15,1,15,3,15,150,8,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	3,16,161,8,16,1,17,1,17,5,17,165,8,17,10,17,12,17,168,9,17,1,18,1,18,
  	1,18,1,18,5,18,174,8,18,10,18,12,18,177,9,18,1,18,1,18,1,19,4,19,182,
  	8,19,11,19,12,19,183,1,19,1,19,1,20,1,20,1,20,1,20,5,20,192,8,20,10,20,
  	12,20,195,9,20,1,20,1,20,5,20,199,8,20,10,20,12,20,202,9,20,3,20,204,
  	8,20,1,20,1,20,1,21,1,21,1,21,1,21,5,21,212,8,21,10,21,12,21,215,9,21,
  	1,21,1,21,1,21,1,21,1,21,1,213,0,22,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,
  	8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,
  	20,41,21,43,22,1,0,5,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,
  	122,2,0,34,34,92,92,3,0,9,10,13,13,32,32,2,0,10,10,13,13,234,0,1,1,0,
  	0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,
  	1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,
  	0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,
  	0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,1,45,
  	1,0,0,0,3,47,1,0,0,0,5,49,1,0,0,0,7,51,1,0,0,0,9,53,1,0,0,0,11,55,1,0,
  	0,0,13,57,1,0,0,0,15,59,1,0,0,0,17,64,1,0,0,0,19,73,1,0,0,0,21,80,1,0,
  	0,0,23,88,1,0,0,0,25,100,1,0,0,0,27,129,1,0,0,0,29,141,1,0,0,0,31,149,
  	1,0,0,0,33,160,1,0,0,0,35,162,1,0,0,0,37,169,1,0,0,0,39,181,1,0,0,0,41,
  	203,1,0,0,0,43,207,1,0,0,0,45,46,5,123,0,0,46,2,1,0,0,0,47,48,5,125,0,
  	0,48,4,1,0,0,0,49,50,5,58,0,0,50,6,1,0,0,0,51,52,5,40,0,0,52,8,1,0,0,
  	0,53,54,5,41,0,0,54,10,1,0,0,0,55,56,5,44,0,0,56,12,1,0,0,0,57,58,5,61,
  	0,0,58,14,1,0,0,0,59,60,5,114,0,0,60,61,5,117,0,0,61,62,5,108,0,0,62,
  	63,5,101,0,0,63,16,1,0,0,0,64,65,5,115,0,0,65,66,5,101,0,0,66,67,5,118,
  	0,0,67,68,5,101,0,0,68,69,5,114,0,0,69,70,5,105,0,0,70,71,5,116,0,0,71,
  	72,5,121,0,0,72,18,1,0,0,0,73,74,5,97,0,0,74,75,5,99,0,0,75,76,5,116,
  	0,0,76,77,5,105,0,0,77,78,5,111,0,0,78,79,5,110,0,0,79,20,1,0,0,0,80,
  	81,5,112,0,0,81,82,5,114,0,0,82,83,5,111,0,0,83,84,5,102,0,0,84,85,5,
  	105,0,0,85,86,5,108,0,0,86,87,5,101,0,0,87,22,1,0,0,0,88,89,5,100,0,0,
  	89,90,5,101,0,0,90,91,5,115,0,0,91,92,5,99,0,0,92,93,5,114,0,0,93,94,
  	5,105,0,0,94,95,5,112,0,0,95,96,5,116,0,0,96,97,5,105,0,0,97,98,5,111,
  	0,0,98,99,5,110,0,0,99,24,1,0,0,0,100,101,5,112,0,0,101,102,5,97,0,0,
  	102,103,5,116,0,0,103,104,5,116,0,0,104,105,5,101,0,0,105,106,5,114,0,
  	0,106,107,5,110,0,0,107,26,1,0,0,0,108,109,5,76,0,0,109,110,5,79,0,0,
  	110,130,5,87,0,0,111,112,5,77,0,0,112,113,5,69,0,0,113,114,5,68,0,0,114,
  	115,5,73,0,0,115,116,5,85,0,0,116,130,5,77,0,0,117,118,5,72,0,0,118,119,
  	5,73,0,0,119,120,5,71,0,0,120,130,5,72,0,0,121,122,5,67,0,0,122,123,5,
  	82,0,0,123,124,5,73,0,0,124,125,5,84,0,0,125,126,5,73,0,0,126,127,5,67,
  	0,0,127,128,5,65,0,0,128,130,5,76,0,0,129,108,1,0,0,0,129,111,1,0,0,0,
  	129,117,1,0,0,0,129,121,1,0,0,0,130,28,1,0,0,0,131,132,5,65,0,0,132,133,
  	5,76,0,0,133,134,5,76,0,0,134,135,5,79,0,0,135,142,5,87,0,0,136,137,5,
  	66,0,0,137,138,5,76,0,0,138,139,5,79,0,0,139,140,5,67,0,0,140,142,5,75,
  	0,0,141,131,1,0,0,0,141,136,1,0,0,0,142,30,1,0,0,0,143,144,5,115,0,0,
  	144,145,5,113,0,0,145,150,5,108,0,0,146,147,5,114,0,0,147,148,5,97,0,
  	0,148,150,5,119,0,0,149,143,1,0,0,0,149,146,1,0,0,0,150,32,1,0,0,0,151,
  	152,5,116,0,0,152,153,5,114,0,0,153,154,5,117,0,0,154,161,5,101,0,0,155,
  	156,5,102,0,0,156,157,5,97,0,0,157,158,5,108,0,0,158,159,5,115,0,0,159,
  	161,5,101,0,0,160,151,1,0,0,0,160,155,1,0,0,0,161,34,1,0,0,0,162,166,
  	7,0,0,0,163,165,7,1,0,0,164,163,1,0,0,0,165,168,1,0,0,0,166,164,1,0,0,
  	0,166,167,1,0,0,0,167,36,1,0,0,0,168,166,1,0,0,0,169,175,5,34,0,0,170,
  	171,5,92,0,0,171,174,9,0,0,0,172,174,8,2,0,0,173,170,1,0,0,0,173,172,
  	1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,175,176,1,0,0,0,176,178,1,0,0,
  	0,177,175,1,0,0,0,178,179,5,34,0,0,179,38,1,0,0,0,180,182,7,3,0,0,181,
  	180,1,0,0,0,182,183,1,0,0,0,183,181,1,0,0,0,183,184,1,0,0,0,184,185,1,
  	0,0,0,185,186,6,19,0,0,186,40,1,0,0,0,187,188,5,47,0,0,188,189,5,47,0,
  	0,189,193,1,0,0,0,190,192,8,4,0,0,191,190,1,0,0,0,192,195,1,0,0,0,193,
  	191,1,0,0,0,193,194,1,0,0,0,194,204,1,0,0,0,195,193,1,0,0,0,196,200,5,
  	35,0,0,197,199,8,4,0,0,198,197,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,
  	0,200,201,1,0,0,0,201,204,1,0,0,0,202,200,1,0,0,0,203,187,1,0,0,0,203,
  	196,1,0,0,0,204,205,1,0,0,0,205,206,6,20,0,0,206,42,1,0,0,0,207,208,5,
  	47,0,0,208,209,5,42,0,0,209,213,1,0,0,0,210,212,9,0,0,0,211,210,1,0,0,
  	0,212,215,1,0,0,0,213,214,1,0,0,0,213,211,1,0,0,0,214,216,1,0,0,0,215,
  	213,1,0,0,0,216,217,5,42,0,0,217,218,5,47,0,0,218,219,1,0,0,0,219,220,
  	6,21,0,0,220,44,1,0,0,0,13,0,129,141,149,160,166,173,175,183,193,200,
  	203,213,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  rulelexerLexerStaticData = std::move(staticData);
}

}

RuleLexer::RuleLexer(CharStream *input) : Lexer(input) {
  RuleLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *rulelexerLexerStaticData->atn, rulelexerLexerStaticData->decisionToDFA, rulelexerLexerStaticData->sharedContextCache);
}

RuleLexer::~RuleLexer() {
  delete _interpreter;
}

std::string RuleLexer::getGrammarFileName() const {
  return "Rule.g4";
}

const std::vector<std::string>& RuleLexer::getRuleNames() const {
  return rulelexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& RuleLexer::getChannelNames() const {
  return rulelexerLexerStaticData->channelNames;
}

const std::vector<std::string>& RuleLexer::getModeNames() const {
  return rulelexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& RuleLexer::getVocabulary() const {
  return rulelexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView RuleLexer::getSerializedATN() const {
  return rulelexerLexerStaticData->serializedATN;
}

const atn::ATN& RuleLexer::getATN() const {
  return *rulelexerLexerStaticData->atn;
}




void RuleLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  rulelexerLexerInitialize();
#else
  ::antlr4::internal::call_once(rulelexerLexerOnceFlag, rulelexerLexerInitialize);
#endif
}
