
// Generated from MiniSQL.g4 by ANTLR 4.13.2


#include "MiniSQLListener.h"

#include "MiniSQLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MiniSQLParserStaticData final {
  MiniSQLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniSQLParserStaticData(const MiniSQLParserStaticData&) = delete;
  MiniSQLParserStaticData(MiniSQLParserStaticData&&) = delete;
  MiniSQLParserStaticData& operator=(const MiniSQLParserStaticData&) = delete;
  MiniSQLParserStaticData& operator=(MiniSQLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag minisqlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MiniSQLParserStaticData> minisqlParserStaticData = nullptr;

void minisqlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (minisqlParserStaticData != nullptr) {
    return;
  }
#else
  assert(minisqlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MiniSQLParserStaticData>(
    std::vector<std::string>{
      "sql", "statement", "queryStatement", "withClause", "cte", "columnAliasList", 
      "queryExpression", "queryTerm", "querySpecification", "setQuantifier", 
      "selectList", "selectItem", "fromClause", "tableReference", "tablePrimary", 
      "joinClause", "joinType", "joinCondition", "whereClause", "groupByClause", 
      "havingClause", "orderByClause", "orderItem", "limitClause", "expression", 
      "orExpression", "andExpression", "notExpression", "comparisonExpression", 
      "comparisonOperator", "additiveExpression", "multiplicativeExpression", 
      "unaryExpression", "primaryExpression", "columnReference", "functionCall", 
      "functionArguments", "caseExpression", "whenClause", "inExpression", 
      "expressionList", "literal", "identifier"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "'='", "", "'<='", "'>='", "'<'", 
      "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'('", "')'", "','", "'.'"
    },
    std::vector<std::string>{
      "", "WITH", "RECURSIVE", "SELECT", "FROM", "WHERE", "GROUP", "BY", 
      "HAVING", "ORDER", "LIMIT", "OFFSET", "UNION", "ALL", "DISTINCT", 
      "JOIN", "INNER", "LEFT", "RIGHT", "FULL", "OUTER", "CROSS", "ON", 
      "USING", "AS", "AND", "OR", "NOT", "IN", "LIKE", "BETWEEN", "EXISTS", 
      "IS", "NULL", "TRUE", "FALSE", "ASC", "DESC", "CASE", "WHEN", "THEN", 
      "ELSE", "END", "EQ", "NE", "LE", "GE", "LT", "GT", "PLUS", "MINUS", 
      "STAR", "DIV", "MOD", "LPAREN", "RPAREN", "COMMA", "DOT", "NUMBER", 
      "STRING", "QUOTED_IDENTIFIER", "IDENTIFIER", "WS", "COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,64,475,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,1,0,1,0,1,0,1,1,1,1,1,2,3,2,93,8,2,1,2,1,2,1,3,1,3,3,3,99,8,3,1,3,
  	1,3,1,3,5,3,104,8,3,10,3,12,3,107,9,3,1,4,1,4,3,4,111,8,4,1,4,1,4,1,4,
  	1,4,1,4,1,5,1,5,1,5,1,5,5,5,122,8,5,10,5,12,5,125,9,5,1,5,1,5,1,6,1,6,
  	1,6,3,6,132,8,6,1,6,5,6,135,8,6,10,6,12,6,138,9,6,1,7,1,7,1,7,1,7,1,7,
  	3,7,145,8,7,1,8,1,8,3,8,149,8,8,1,8,1,8,3,8,153,8,8,1,8,3,8,156,8,8,1,
  	8,3,8,159,8,8,1,8,3,8,162,8,8,1,8,3,8,165,8,8,1,8,3,8,168,8,8,1,9,1,9,
  	1,10,1,10,1,10,1,10,5,10,176,8,10,10,10,12,10,179,9,10,3,10,181,8,10,
  	1,11,1,11,3,11,185,8,11,1,11,3,11,188,8,11,1,12,1,12,1,12,1,12,5,12,194,
  	8,12,10,12,12,12,197,9,12,1,13,1,13,5,13,201,8,13,10,13,12,13,204,9,13,
  	1,14,1,14,3,14,208,8,14,1,14,3,14,211,8,14,1,14,1,14,1,14,1,14,3,14,217,
  	8,14,1,14,3,14,220,8,14,3,14,222,8,14,1,15,3,15,225,8,15,1,15,1,15,1,
  	15,3,15,230,8,15,1,16,1,16,1,16,3,16,235,8,16,1,16,1,16,3,16,239,8,16,
  	1,16,1,16,3,16,243,8,16,1,16,3,16,246,8,16,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,5,17,255,8,17,10,17,12,17,258,9,17,1,17,1,17,3,17,262,8,17,1,
  	18,1,18,1,18,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,
  	21,5,21,279,8,21,10,21,12,21,282,9,21,1,22,1,22,3,22,286,8,22,1,23,1,
  	23,1,23,1,23,3,23,292,8,23,1,24,1,24,1,25,1,25,1,25,5,25,299,8,25,10,
  	25,12,25,302,9,25,1,26,1,26,1,26,5,26,307,8,26,10,26,12,26,310,9,26,1,
  	27,1,27,1,27,3,27,315,8,27,1,28,1,28,1,28,1,28,1,28,1,28,3,28,323,8,28,
  	1,28,1,28,1,28,3,28,328,8,28,1,28,1,28,1,28,3,28,333,8,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,3,28,374,8,28,1,29,1,29,1,
  	30,1,30,1,30,5,30,381,8,30,10,30,12,30,384,9,30,1,31,1,31,1,31,5,31,389,
  	8,31,10,31,12,31,392,9,31,1,32,1,32,1,32,1,32,1,32,3,32,399,8,32,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,3,33,413,8,33,
  	1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,1,34,3,34,426,8,34,
  	1,35,1,35,1,35,3,35,431,8,35,1,35,1,35,1,36,1,36,3,36,437,8,36,1,37,1,
  	37,3,37,441,8,37,1,37,4,37,444,8,37,11,37,12,37,445,1,37,1,37,3,37,450,
  	8,37,1,37,1,37,1,38,1,38,1,38,1,38,1,38,1,39,1,39,3,39,461,8,39,1,40,
  	1,40,1,40,5,40,466,8,40,10,40,12,40,469,9,40,1,41,1,41,1,42,1,42,1,42,
  	0,0,43,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,0,7,1,0,13,
  	14,1,0,36,37,1,0,43,48,1,0,49,50,1,0,51,53,2,0,33,35,58,59,1,0,60,61,
  	507,0,86,1,0,0,0,2,89,1,0,0,0,4,92,1,0,0,0,6,96,1,0,0,0,8,108,1,0,0,0,
  	10,117,1,0,0,0,12,128,1,0,0,0,14,144,1,0,0,0,16,146,1,0,0,0,18,169,1,
  	0,0,0,20,180,1,0,0,0,22,182,1,0,0,0,24,189,1,0,0,0,26,198,1,0,0,0,28,
  	221,1,0,0,0,30,224,1,0,0,0,32,245,1,0,0,0,34,261,1,0,0,0,36,263,1,0,0,
  	0,38,266,1,0,0,0,40,270,1,0,0,0,42,273,1,0,0,0,44,283,1,0,0,0,46,287,
  	1,0,0,0,48,293,1,0,0,0,50,295,1,0,0,0,52,303,1,0,0,0,54,314,1,0,0,0,56,
  	316,1,0,0,0,58,375,1,0,0,0,60,377,1,0,0,0,62,385,1,0,0,0,64,398,1,0,0,
  	0,66,412,1,0,0,0,68,425,1,0,0,0,70,427,1,0,0,0,72,436,1,0,0,0,74,438,
  	1,0,0,0,76,453,1,0,0,0,78,460,1,0,0,0,80,462,1,0,0,0,82,470,1,0,0,0,84,
  	472,1,0,0,0,86,87,3,2,1,0,87,88,5,0,0,1,88,1,1,0,0,0,89,90,3,4,2,0,90,
  	3,1,0,0,0,91,93,3,6,3,0,92,91,1,0,0,0,92,93,1,0,0,0,93,94,1,0,0,0,94,
  	95,3,12,6,0,95,5,1,0,0,0,96,98,5,1,0,0,97,99,5,2,0,0,98,97,1,0,0,0,98,
  	99,1,0,0,0,99,100,1,0,0,0,100,105,3,8,4,0,101,102,5,56,0,0,102,104,3,
  	8,4,0,103,101,1,0,0,0,104,107,1,0,0,0,105,103,1,0,0,0,105,106,1,0,0,0,
  	106,7,1,0,0,0,107,105,1,0,0,0,108,110,3,84,42,0,109,111,3,10,5,0,110,
  	109,1,0,0,0,110,111,1,0,0,0,111,112,1,0,0,0,112,113,5,24,0,0,113,114,
  	5,54,0,0,114,115,3,12,6,0,115,116,5,55,0,0,116,9,1,0,0,0,117,118,5,54,
  	0,0,118,123,3,84,42,0,119,120,5,56,0,0,120,122,3,84,42,0,121,119,1,0,
  	0,0,122,125,1,0,0,0,123,121,1,0,0,0,123,124,1,0,0,0,124,126,1,0,0,0,125,
  	123,1,0,0,0,126,127,5,55,0,0,127,11,1,0,0,0,128,136,3,14,7,0,129,131,
  	5,12,0,0,130,132,5,13,0,0,131,130,1,0,0,0,131,132,1,0,0,0,132,133,1,0,
  	0,0,133,135,3,14,7,0,134,129,1,0,0,0,135,138,1,0,0,0,136,134,1,0,0,0,
  	136,137,1,0,0,0,137,13,1,0,0,0,138,136,1,0,0,0,139,145,3,16,8,0,140,141,
  	5,54,0,0,141,142,3,12,6,0,142,143,5,55,0,0,143,145,1,0,0,0,144,139,1,
  	0,0,0,144,140,1,0,0,0,145,15,1,0,0,0,146,148,5,3,0,0,147,149,3,18,9,0,
  	148,147,1,0,0,0,148,149,1,0,0,0,149,150,1,0,0,0,150,152,3,20,10,0,151,
  	153,3,24,12,0,152,151,1,0,0,0,152,153,1,0,0,0,153,155,1,0,0,0,154,156,
  	3,36,18,0,155,154,1,0,0,0,155,156,1,0,0,0,156,158,1,0,0,0,157,159,3,38,
  	19,0,158,157,1,0,0,0,158,159,1,0,0,0,159,161,1,0,0,0,160,162,3,40,20,
  	0,161,160,1,0,0,0,161,162,1,0,0,0,162,164,1,0,0,0,163,165,3,42,21,0,164,
  	163,1,0,0,0,164,165,1,0,0,0,165,167,1,0,0,0,166,168,3,46,23,0,167,166,
  	1,0,0,0,167,168,1,0,0,0,168,17,1,0,0,0,169,170,7,0,0,0,170,19,1,0,0,0,
  	171,181,5,51,0,0,172,177,3,22,11,0,173,174,5,56,0,0,174,176,3,22,11,0,
  	175,173,1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,0,177,178,1,0,0,0,178,181,
  	1,0,0,0,179,177,1,0,0,0,180,171,1,0,0,0,180,172,1,0,0,0,181,21,1,0,0,
  	0,182,187,3,48,24,0,183,185,5,24,0,0,184,183,1,0,0,0,184,185,1,0,0,0,
  	185,186,1,0,0,0,186,188,3,84,42,0,187,184,1,0,0,0,187,188,1,0,0,0,188,
  	23,1,0,0,0,189,190,5,4,0,0,190,195,3,26,13,0,191,192,5,56,0,0,192,194,
  	3,26,13,0,193,191,1,0,0,0,194,197,1,0,0,0,195,193,1,0,0,0,195,196,1,0,
  	0,0,196,25,1,0,0,0,197,195,1,0,0,0,198,202,3,28,14,0,199,201,3,30,15,
  	0,200,199,1,0,0,0,201,204,1,0,0,0,202,200,1,0,0,0,202,203,1,0,0,0,203,
  	27,1,0,0,0,204,202,1,0,0,0,205,210,3,84,42,0,206,208,5,24,0,0,207,206,
  	1,0,0,0,207,208,1,0,0,0,208,209,1,0,0,0,209,211,3,84,42,0,210,207,1,0,
  	0,0,210,211,1,0,0,0,211,222,1,0,0,0,212,213,5,54,0,0,213,214,3,12,6,0,
  	214,219,5,55,0,0,215,217,5,24,0,0,216,215,1,0,0,0,216,217,1,0,0,0,217,
  	218,1,0,0,0,218,220,3,84,42,0,219,216,1,0,0,0,219,220,1,0,0,0,220,222,
  	1,0,0,0,221,205,1,0,0,0,221,212,1,0,0,0,222,29,1,0,0,0,223,225,3,32,16,
  	0,224,223,1,0,0,0,224,225,1,0,0,0,225,226,1,0,0,0,226,227,5,15,0,0,227,
  	229,3,28,14,0,228,230,3,34,17,0,229,228,1,0,0,0,229,230,1,0,0,0,230,31,
  	1,0,0,0,231,246,5,16,0,0,232,234,5,17,0,0,233,235,5,20,0,0,234,233,1,
  	0,0,0,234,235,1,0,0,0,235,246,1,0,0,0,236,238,5,18,0,0,237,239,5,20,0,
  	0,238,237,1,0,0,0,238,239,1,0,0,0,239,246,1,0,0,0,240,242,5,19,0,0,241,
  	243,5,20,0,0,242,241,1,0,0,0,242,243,1,0,0,0,243,246,1,0,0,0,244,246,
  	5,21,0,0,245,231,1,0,0,0,245,232,1,0,0,0,245,236,1,0,0,0,245,240,1,0,
  	0,0,245,244,1,0,0,0,246,33,1,0,0,0,247,248,5,22,0,0,248,262,3,48,24,0,
  	249,250,5,23,0,0,250,251,5,54,0,0,251,256,3,84,42,0,252,253,5,56,0,0,
  	253,255,3,84,42,0,254,252,1,0,0,0,255,258,1,0,0,0,256,254,1,0,0,0,256,
  	257,1,0,0,0,257,259,1,0,0,0,258,256,1,0,0,0,259,260,5,55,0,0,260,262,
  	1,0,0,0,261,247,1,0,0,0,261,249,1,0,0,0,262,35,1,0,0,0,263,264,5,5,0,
  	0,264,265,3,48,24,0,265,37,1,0,0,0,266,267,5,6,0,0,267,268,5,7,0,0,268,
  	269,3,80,40,0,269,39,1,0,0,0,270,271,5,8,0,0,271,272,3,48,24,0,272,41,
  	1,0,0,0,273,274,5,9,0,0,274,275,5,7,0,0,275,280,3,44,22,0,276,277,5,56,
  	0,0,277,279,3,44,22,0,278,276,1,0,0,0,279,282,1,0,0,0,280,278,1,0,0,0,
  	280,281,1,0,0,0,281,43,1,0,0,0,282,280,1,0,0,0,283,285,3,48,24,0,284,
  	286,7,1,0,0,285,284,1,0,0,0,285,286,1,0,0,0,286,45,1,0,0,0,287,288,5,
  	10,0,0,288,291,3,48,24,0,289,290,5,11,0,0,290,292,3,48,24,0,291,289,1,
  	0,0,0,291,292,1,0,0,0,292,47,1,0,0,0,293,294,3,50,25,0,294,49,1,0,0,0,
  	295,300,3,52,26,0,296,297,5,26,0,0,297,299,3,52,26,0,298,296,1,0,0,0,
  	299,302,1,0,0,0,300,298,1,0,0,0,300,301,1,0,0,0,301,51,1,0,0,0,302,300,
  	1,0,0,0,303,308,3,54,27,0,304,305,5,25,0,0,305,307,3,54,27,0,306,304,
  	1,0,0,0,307,310,1,0,0,0,308,306,1,0,0,0,308,309,1,0,0,0,309,53,1,0,0,
  	0,310,308,1,0,0,0,311,312,5,27,0,0,312,315,3,54,27,0,313,315,3,56,28,
  	0,314,311,1,0,0,0,314,313,1,0,0,0,315,55,1,0,0,0,316,373,3,60,30,0,317,
  	318,3,58,29,0,318,319,3,60,30,0,319,374,1,0,0,0,320,322,5,32,0,0,321,
  	323,5,27,0,0,322,321,1,0,0,0,322,323,1,0,0,0,323,324,1,0,0,0,324,374,
  	5,33,0,0,325,327,5,32,0,0,326,328,5,27,0,0,327,326,1,0,0,0,327,328,1,
  	0,0,0,328,329,1,0,0,0,329,374,5,34,0,0,330,332,5,32,0,0,331,333,5,27,
  	0,0,332,331,1,0,0,0,332,333,1,0,0,0,333,334,1,0,0,0,334,374,5,35,0,0,
  	335,336,5,28,0,0,336,337,5,54,0,0,337,338,3,78,39,0,338,339,5,55,0,0,
  	339,374,1,0,0,0,340,341,5,27,0,0,341,342,5,28,0,0,342,343,5,54,0,0,343,
  	344,3,78,39,0,344,345,5,55,0,0,345,374,1,0,0,0,346,347,5,29,0,0,347,374,
  	3,60,30,0,348,349,5,27,0,0,349,350,5,29,0,0,350,374,3,60,30,0,351,352,
  	5,30,0,0,352,353,3,60,30,0,353,354,5,25,0,0,354,355,3,60,30,0,355,374,
  	1,0,0,0,356,357,5,27,0,0,357,358,5,30,0,0,358,359,3,60,30,0,359,360,5,
  	25,0,0,360,361,3,60,30,0,361,374,1,0,0,0,362,363,5,31,0,0,363,364,5,54,
  	0,0,364,365,3,12,6,0,365,366,5,55,0,0,366,374,1,0,0,0,367,368,5,27,0,
  	0,368,369,5,31,0,0,369,370,5,54,0,0,370,371,3,12,6,0,371,372,5,55,0,0,
  	372,374,1,0,0,0,373,317,1,0,0,0,373,320,1,0,0,0,373,325,1,0,0,0,373,330,
  	1,0,0,0,373,335,1,0,0,0,373,340,1,0,0,0,373,346,1,0,0,0,373,348,1,0,0,
  	0,373,351,1,0,0,0,373,356,1,0,0,0,373,362,1,0,0,0,373,367,1,0,0,0,373,
  	374,1,0,0,0,374,57,1,0,0,0,375,376,7,2,0,0,376,59,1,0,0,0,377,382,3,62,
  	31,0,378,379,7,3,0,0,379,381,3,62,31,0,380,378,1,0,0,0,381,384,1,0,0,
  	0,382,380,1,0,0,0,382,383,1,0,0,0,383,61,1,0,0,0,384,382,1,0,0,0,385,
  	390,3,64,32,0,386,387,7,4,0,0,387,389,3,64,32,0,388,386,1,0,0,0,389,392,
  	1,0,0,0,390,388,1,0,0,0,390,391,1,0,0,0,391,63,1,0,0,0,392,390,1,0,0,
  	0,393,394,5,49,0,0,394,399,3,64,32,0,395,396,5,50,0,0,396,399,3,64,32,
  	0,397,399,3,66,33,0,398,393,1,0,0,0,398,395,1,0,0,0,398,397,1,0,0,0,399,
  	65,1,0,0,0,400,413,3,82,41,0,401,413,3,68,34,0,402,413,3,70,35,0,403,
  	413,3,74,37,0,404,405,5,54,0,0,405,406,3,48,24,0,406,407,5,55,0,0,407,
  	413,1,0,0,0,408,409,5,54,0,0,409,410,3,12,6,0,410,411,5,55,0,0,411,413,
  	1,0,0,0,412,400,1,0,0,0,412,401,1,0,0,0,412,402,1,0,0,0,412,403,1,0,0,
  	0,412,404,1,0,0,0,412,408,1,0,0,0,413,67,1,0,0,0,414,426,3,84,42,0,415,
  	416,3,84,42,0,416,417,5,57,0,0,417,418,3,84,42,0,418,426,1,0,0,0,419,
  	420,3,84,42,0,420,421,5,57,0,0,421,422,3,84,42,0,422,423,5,57,0,0,423,
  	424,3,84,42,0,424,426,1,0,0,0,425,414,1,0,0,0,425,415,1,0,0,0,425,419,
  	1,0,0,0,426,69,1,0,0,0,427,428,3,84,42,0,428,430,5,54,0,0,429,431,3,72,
  	36,0,430,429,1,0,0,0,430,431,1,0,0,0,431,432,1,0,0,0,432,433,5,55,0,0,
  	433,71,1,0,0,0,434,437,5,51,0,0,435,437,3,80,40,0,436,434,1,0,0,0,436,
  	435,1,0,0,0,437,73,1,0,0,0,438,440,5,38,0,0,439,441,3,48,24,0,440,439,
  	1,0,0,0,440,441,1,0,0,0,441,443,1,0,0,0,442,444,3,76,38,0,443,442,1,0,
  	0,0,444,445,1,0,0,0,445,443,1,0,0,0,445,446,1,0,0,0,446,449,1,0,0,0,447,
  	448,5,41,0,0,448,450,3,48,24,0,449,447,1,0,0,0,449,450,1,0,0,0,450,451,
  	1,0,0,0,451,452,5,42,0,0,452,75,1,0,0,0,453,454,5,39,0,0,454,455,3,48,
  	24,0,455,456,5,40,0,0,456,457,3,48,24,0,457,77,1,0,0,0,458,461,3,80,40,
  	0,459,461,3,12,6,0,460,458,1,0,0,0,460,459,1,0,0,0,461,79,1,0,0,0,462,
  	467,3,48,24,0,463,464,5,56,0,0,464,466,3,48,24,0,465,463,1,0,0,0,466,
  	469,1,0,0,0,467,465,1,0,0,0,467,468,1,0,0,0,468,81,1,0,0,0,469,467,1,
  	0,0,0,470,471,7,5,0,0,471,83,1,0,0,0,472,473,7,6,0,0,473,85,1,0,0,0,56,
  	92,98,105,110,123,131,136,144,148,152,155,158,161,164,167,177,180,184,
  	187,195,202,207,210,216,219,221,224,229,234,238,242,245,256,261,280,285,
  	291,300,308,314,322,327,332,373,382,390,398,412,425,430,436,440,445,449,
  	460,467
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  minisqlParserStaticData = std::move(staticData);
}

}

MiniSQLParser::MiniSQLParser(TokenStream *input) : MiniSQLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MiniSQLParser::MiniSQLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MiniSQLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *minisqlParserStaticData->atn, minisqlParserStaticData->decisionToDFA, minisqlParserStaticData->sharedContextCache, options);
}

MiniSQLParser::~MiniSQLParser() {
  delete _interpreter;
}

const atn::ATN& MiniSQLParser::getATN() const {
  return *minisqlParserStaticData->atn;
}

std::string MiniSQLParser::getGrammarFileName() const {
  return "MiniSQL.g4";
}

const std::vector<std::string>& MiniSQLParser::getRuleNames() const {
  return minisqlParserStaticData->ruleNames;
}

const dfa::Vocabulary& MiniSQLParser::getVocabulary() const {
  return minisqlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MiniSQLParser::getSerializedATN() const {
  return minisqlParserStaticData->serializedATN;
}


//----------------- SqlContext ------------------------------------------------------------------

MiniSQLParser::SqlContext::SqlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::StatementContext* MiniSQLParser::SqlContext::statement() {
  return getRuleContext<MiniSQLParser::StatementContext>(0);
}

tree::TerminalNode* MiniSQLParser::SqlContext::EOF() {
  return getToken(MiniSQLParser::EOF, 0);
}


size_t MiniSQLParser::SqlContext::getRuleIndex() const {
  return MiniSQLParser::RuleSql;
}

void MiniSQLParser::SqlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSql(this);
}

void MiniSQLParser::SqlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSql(this);
}

MiniSQLParser::SqlContext* MiniSQLParser::sql() {
  SqlContext *_localctx = _tracker.createInstance<SqlContext>(_ctx, getState());
  enterRule(_localctx, 0, MiniSQLParser::RuleSql);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    statement();
    setState(87);
    match(MiniSQLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MiniSQLParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::QueryStatementContext* MiniSQLParser::StatementContext::queryStatement() {
  return getRuleContext<MiniSQLParser::QueryStatementContext>(0);
}


size_t MiniSQLParser::StatementContext::getRuleIndex() const {
  return MiniSQLParser::RuleStatement;
}

void MiniSQLParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void MiniSQLParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

MiniSQLParser::StatementContext* MiniSQLParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, MiniSQLParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    queryStatement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryStatementContext ------------------------------------------------------------------

MiniSQLParser::QueryStatementContext::QueryStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::QueryStatementContext::queryExpression() {
  return getRuleContext<MiniSQLParser::QueryExpressionContext>(0);
}

MiniSQLParser::WithClauseContext* MiniSQLParser::QueryStatementContext::withClause() {
  return getRuleContext<MiniSQLParser::WithClauseContext>(0);
}


size_t MiniSQLParser::QueryStatementContext::getRuleIndex() const {
  return MiniSQLParser::RuleQueryStatement;
}

void MiniSQLParser::QueryStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQueryStatement(this);
}

void MiniSQLParser::QueryStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQueryStatement(this);
}

MiniSQLParser::QueryStatementContext* MiniSQLParser::queryStatement() {
  QueryStatementContext *_localctx = _tracker.createInstance<QueryStatementContext>(_ctx, getState());
  enterRule(_localctx, 4, MiniSQLParser::RuleQueryStatement);
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
    setState(92);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::WITH) {
      setState(91);
      withClause();
    }
    setState(94);
    queryExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithClauseContext ------------------------------------------------------------------

MiniSQLParser::WithClauseContext::WithClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::WithClauseContext::WITH() {
  return getToken(MiniSQLParser::WITH, 0);
}

std::vector<MiniSQLParser::CteContext *> MiniSQLParser::WithClauseContext::cte() {
  return getRuleContexts<MiniSQLParser::CteContext>();
}

MiniSQLParser::CteContext* MiniSQLParser::WithClauseContext::cte(size_t i) {
  return getRuleContext<MiniSQLParser::CteContext>(i);
}

tree::TerminalNode* MiniSQLParser::WithClauseContext::RECURSIVE() {
  return getToken(MiniSQLParser::RECURSIVE, 0);
}

std::vector<tree::TerminalNode *> MiniSQLParser::WithClauseContext::COMMA() {
  return getTokens(MiniSQLParser::COMMA);
}

tree::TerminalNode* MiniSQLParser::WithClauseContext::COMMA(size_t i) {
  return getToken(MiniSQLParser::COMMA, i);
}


size_t MiniSQLParser::WithClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleWithClause;
}

void MiniSQLParser::WithClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWithClause(this);
}

void MiniSQLParser::WithClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWithClause(this);
}

MiniSQLParser::WithClauseContext* MiniSQLParser::withClause() {
  WithClauseContext *_localctx = _tracker.createInstance<WithClauseContext>(_ctx, getState());
  enterRule(_localctx, 6, MiniSQLParser::RuleWithClause);
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
    setState(96);
    match(MiniSQLParser::WITH);
    setState(98);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::RECURSIVE) {
      setState(97);
      match(MiniSQLParser::RECURSIVE);
    }
    setState(100);
    cte();
    setState(105);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::COMMA) {
      setState(101);
      match(MiniSQLParser::COMMA);
      setState(102);
      cte();
      setState(107);
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

//----------------- CteContext ------------------------------------------------------------------

MiniSQLParser::CteContext::CteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::IdentifierContext* MiniSQLParser::CteContext::identifier() {
  return getRuleContext<MiniSQLParser::IdentifierContext>(0);
}

tree::TerminalNode* MiniSQLParser::CteContext::AS() {
  return getToken(MiniSQLParser::AS, 0);
}

tree::TerminalNode* MiniSQLParser::CteContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::CteContext::queryExpression() {
  return getRuleContext<MiniSQLParser::QueryExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::CteContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}

MiniSQLParser::ColumnAliasListContext* MiniSQLParser::CteContext::columnAliasList() {
  return getRuleContext<MiniSQLParser::ColumnAliasListContext>(0);
}


size_t MiniSQLParser::CteContext::getRuleIndex() const {
  return MiniSQLParser::RuleCte;
}

void MiniSQLParser::CteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCte(this);
}

void MiniSQLParser::CteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCte(this);
}

MiniSQLParser::CteContext* MiniSQLParser::cte() {
  CteContext *_localctx = _tracker.createInstance<CteContext>(_ctx, getState());
  enterRule(_localctx, 8, MiniSQLParser::RuleCte);
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
    setState(108);
    identifier();
    setState(110);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::LPAREN) {
      setState(109);
      columnAliasList();
    }
    setState(112);
    match(MiniSQLParser::AS);
    setState(113);
    match(MiniSQLParser::LPAREN);
    setState(114);
    queryExpression();
    setState(115);
    match(MiniSQLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnAliasListContext ------------------------------------------------------------------

MiniSQLParser::ColumnAliasListContext::ColumnAliasListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::ColumnAliasListContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

std::vector<MiniSQLParser::IdentifierContext *> MiniSQLParser::ColumnAliasListContext::identifier() {
  return getRuleContexts<MiniSQLParser::IdentifierContext>();
}

MiniSQLParser::IdentifierContext* MiniSQLParser::ColumnAliasListContext::identifier(size_t i) {
  return getRuleContext<MiniSQLParser::IdentifierContext>(i);
}

tree::TerminalNode* MiniSQLParser::ColumnAliasListContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> MiniSQLParser::ColumnAliasListContext::COMMA() {
  return getTokens(MiniSQLParser::COMMA);
}

tree::TerminalNode* MiniSQLParser::ColumnAliasListContext::COMMA(size_t i) {
  return getToken(MiniSQLParser::COMMA, i);
}


size_t MiniSQLParser::ColumnAliasListContext::getRuleIndex() const {
  return MiniSQLParser::RuleColumnAliasList;
}

void MiniSQLParser::ColumnAliasListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnAliasList(this);
}

void MiniSQLParser::ColumnAliasListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnAliasList(this);
}

MiniSQLParser::ColumnAliasListContext* MiniSQLParser::columnAliasList() {
  ColumnAliasListContext *_localctx = _tracker.createInstance<ColumnAliasListContext>(_ctx, getState());
  enterRule(_localctx, 10, MiniSQLParser::RuleColumnAliasList);
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
    setState(117);
    match(MiniSQLParser::LPAREN);
    setState(118);
    identifier();
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::COMMA) {
      setState(119);
      match(MiniSQLParser::COMMA);
      setState(120);
      identifier();
      setState(125);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(126);
    match(MiniSQLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryExpressionContext ------------------------------------------------------------------

MiniSQLParser::QueryExpressionContext::QueryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::QueryTermContext *> MiniSQLParser::QueryExpressionContext::queryTerm() {
  return getRuleContexts<MiniSQLParser::QueryTermContext>();
}

MiniSQLParser::QueryTermContext* MiniSQLParser::QueryExpressionContext::queryTerm(size_t i) {
  return getRuleContext<MiniSQLParser::QueryTermContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::QueryExpressionContext::UNION() {
  return getTokens(MiniSQLParser::UNION);
}

tree::TerminalNode* MiniSQLParser::QueryExpressionContext::UNION(size_t i) {
  return getToken(MiniSQLParser::UNION, i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::QueryExpressionContext::ALL() {
  return getTokens(MiniSQLParser::ALL);
}

tree::TerminalNode* MiniSQLParser::QueryExpressionContext::ALL(size_t i) {
  return getToken(MiniSQLParser::ALL, i);
}


size_t MiniSQLParser::QueryExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleQueryExpression;
}

void MiniSQLParser::QueryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQueryExpression(this);
}

void MiniSQLParser::QueryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQueryExpression(this);
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::queryExpression() {
  QueryExpressionContext *_localctx = _tracker.createInstance<QueryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 12, MiniSQLParser::RuleQueryExpression);
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
    setState(128);
    queryTerm();
    setState(136);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::UNION) {
      setState(129);
      match(MiniSQLParser::UNION);
      setState(131);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MiniSQLParser::ALL) {
        setState(130);
        match(MiniSQLParser::ALL);
      }
      setState(133);
      queryTerm();
      setState(138);
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

//----------------- QueryTermContext ------------------------------------------------------------------

MiniSQLParser::QueryTermContext::QueryTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::QuerySpecificationContext* MiniSQLParser::QueryTermContext::querySpecification() {
  return getRuleContext<MiniSQLParser::QuerySpecificationContext>(0);
}

tree::TerminalNode* MiniSQLParser::QueryTermContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::QueryTermContext::queryExpression() {
  return getRuleContext<MiniSQLParser::QueryExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::QueryTermContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}


size_t MiniSQLParser::QueryTermContext::getRuleIndex() const {
  return MiniSQLParser::RuleQueryTerm;
}

void MiniSQLParser::QueryTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQueryTerm(this);
}

void MiniSQLParser::QueryTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQueryTerm(this);
}

MiniSQLParser::QueryTermContext* MiniSQLParser::queryTerm() {
  QueryTermContext *_localctx = _tracker.createInstance<QueryTermContext>(_ctx, getState());
  enterRule(_localctx, 14, MiniSQLParser::RuleQueryTerm);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(144);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::SELECT: {
        enterOuterAlt(_localctx, 1);
        setState(139);
        querySpecification();
        break;
      }

      case MiniSQLParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(140);
        match(MiniSQLParser::LPAREN);
        setState(141);
        queryExpression();
        setState(142);
        match(MiniSQLParser::RPAREN);
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

//----------------- QuerySpecificationContext ------------------------------------------------------------------

MiniSQLParser::QuerySpecificationContext::QuerySpecificationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::QuerySpecificationContext::SELECT() {
  return getToken(MiniSQLParser::SELECT, 0);
}

MiniSQLParser::SelectListContext* MiniSQLParser::QuerySpecificationContext::selectList() {
  return getRuleContext<MiniSQLParser::SelectListContext>(0);
}

MiniSQLParser::SetQuantifierContext* MiniSQLParser::QuerySpecificationContext::setQuantifier() {
  return getRuleContext<MiniSQLParser::SetQuantifierContext>(0);
}

MiniSQLParser::FromClauseContext* MiniSQLParser::QuerySpecificationContext::fromClause() {
  return getRuleContext<MiniSQLParser::FromClauseContext>(0);
}

MiniSQLParser::WhereClauseContext* MiniSQLParser::QuerySpecificationContext::whereClause() {
  return getRuleContext<MiniSQLParser::WhereClauseContext>(0);
}

MiniSQLParser::GroupByClauseContext* MiniSQLParser::QuerySpecificationContext::groupByClause() {
  return getRuleContext<MiniSQLParser::GroupByClauseContext>(0);
}

MiniSQLParser::HavingClauseContext* MiniSQLParser::QuerySpecificationContext::havingClause() {
  return getRuleContext<MiniSQLParser::HavingClauseContext>(0);
}

MiniSQLParser::OrderByClauseContext* MiniSQLParser::QuerySpecificationContext::orderByClause() {
  return getRuleContext<MiniSQLParser::OrderByClauseContext>(0);
}

MiniSQLParser::LimitClauseContext* MiniSQLParser::QuerySpecificationContext::limitClause() {
  return getRuleContext<MiniSQLParser::LimitClauseContext>(0);
}


size_t MiniSQLParser::QuerySpecificationContext::getRuleIndex() const {
  return MiniSQLParser::RuleQuerySpecification;
}

void MiniSQLParser::QuerySpecificationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterQuerySpecification(this);
}

void MiniSQLParser::QuerySpecificationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitQuerySpecification(this);
}

MiniSQLParser::QuerySpecificationContext* MiniSQLParser::querySpecification() {
  QuerySpecificationContext *_localctx = _tracker.createInstance<QuerySpecificationContext>(_ctx, getState());
  enterRule(_localctx, 16, MiniSQLParser::RuleQuerySpecification);
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
    setState(146);
    match(MiniSQLParser::SELECT);
    setState(148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::ALL

    || _la == MiniSQLParser::DISTINCT) {
      setState(147);
      setQuantifier();
    }
    setState(150);
    selectList();
    setState(152);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::FROM) {
      setState(151);
      fromClause();
    }
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::WHERE) {
      setState(154);
      whereClause();
    }
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::GROUP) {
      setState(157);
      groupByClause();
    }
    setState(161);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::HAVING) {
      setState(160);
      havingClause();
    }
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::ORDER) {
      setState(163);
      orderByClause();
    }
    setState(167);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::LIMIT) {
      setState(166);
      limitClause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetQuantifierContext ------------------------------------------------------------------

MiniSQLParser::SetQuantifierContext::SetQuantifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::SetQuantifierContext::DISTINCT() {
  return getToken(MiniSQLParser::DISTINCT, 0);
}

tree::TerminalNode* MiniSQLParser::SetQuantifierContext::ALL() {
  return getToken(MiniSQLParser::ALL, 0);
}


size_t MiniSQLParser::SetQuantifierContext::getRuleIndex() const {
  return MiniSQLParser::RuleSetQuantifier;
}

void MiniSQLParser::SetQuantifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetQuantifier(this);
}

void MiniSQLParser::SetQuantifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetQuantifier(this);
}

MiniSQLParser::SetQuantifierContext* MiniSQLParser::setQuantifier() {
  SetQuantifierContext *_localctx = _tracker.createInstance<SetQuantifierContext>(_ctx, getState());
  enterRule(_localctx, 18, MiniSQLParser::RuleSetQuantifier);
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
    setState(169);
    _la = _input->LA(1);
    if (!(_la == MiniSQLParser::ALL

    || _la == MiniSQLParser::DISTINCT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectListContext ------------------------------------------------------------------

MiniSQLParser::SelectListContext::SelectListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::SelectListContext::STAR() {
  return getToken(MiniSQLParser::STAR, 0);
}

std::vector<MiniSQLParser::SelectItemContext *> MiniSQLParser::SelectListContext::selectItem() {
  return getRuleContexts<MiniSQLParser::SelectItemContext>();
}

MiniSQLParser::SelectItemContext* MiniSQLParser::SelectListContext::selectItem(size_t i) {
  return getRuleContext<MiniSQLParser::SelectItemContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::SelectListContext::COMMA() {
  return getTokens(MiniSQLParser::COMMA);
}

tree::TerminalNode* MiniSQLParser::SelectListContext::COMMA(size_t i) {
  return getToken(MiniSQLParser::COMMA, i);
}


size_t MiniSQLParser::SelectListContext::getRuleIndex() const {
  return MiniSQLParser::RuleSelectList;
}

void MiniSQLParser::SelectListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectList(this);
}

void MiniSQLParser::SelectListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectList(this);
}

MiniSQLParser::SelectListContext* MiniSQLParser::selectList() {
  SelectListContext *_localctx = _tracker.createInstance<SelectListContext>(_ctx, getState());
  enterRule(_localctx, 20, MiniSQLParser::RuleSelectList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::STAR: {
        enterOuterAlt(_localctx, 1);
        setState(171);
        match(MiniSQLParser::STAR);
        break;
      }

      case MiniSQLParser::NOT:
      case MiniSQLParser::NULL_:
      case MiniSQLParser::TRUE:
      case MiniSQLParser::FALSE:
      case MiniSQLParser::CASE:
      case MiniSQLParser::PLUS:
      case MiniSQLParser::MINUS:
      case MiniSQLParser::LPAREN:
      case MiniSQLParser::NUMBER:
      case MiniSQLParser::STRING:
      case MiniSQLParser::QUOTED_IDENTIFIER:
      case MiniSQLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(172);
        selectItem();
        setState(177);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MiniSQLParser::COMMA) {
          setState(173);
          match(MiniSQLParser::COMMA);
          setState(174);
          selectItem();
          setState(179);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
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

//----------------- SelectItemContext ------------------------------------------------------------------

MiniSQLParser::SelectItemContext::SelectItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::ExpressionContext* MiniSQLParser::SelectItemContext::expression() {
  return getRuleContext<MiniSQLParser::ExpressionContext>(0);
}

MiniSQLParser::IdentifierContext* MiniSQLParser::SelectItemContext::identifier() {
  return getRuleContext<MiniSQLParser::IdentifierContext>(0);
}

tree::TerminalNode* MiniSQLParser::SelectItemContext::AS() {
  return getToken(MiniSQLParser::AS, 0);
}


size_t MiniSQLParser::SelectItemContext::getRuleIndex() const {
  return MiniSQLParser::RuleSelectItem;
}

void MiniSQLParser::SelectItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectItem(this);
}

void MiniSQLParser::SelectItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectItem(this);
}

MiniSQLParser::SelectItemContext* MiniSQLParser::selectItem() {
  SelectItemContext *_localctx = _tracker.createInstance<SelectItemContext>(_ctx, getState());
  enterRule(_localctx, 22, MiniSQLParser::RuleSelectItem);
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
    setState(182);
    expression();
    setState(187);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3458764513837318144) != 0)) {
      setState(184);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MiniSQLParser::AS) {
        setState(183);
        match(MiniSQLParser::AS);
      }
      setState(186);
      identifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromClauseContext ------------------------------------------------------------------

MiniSQLParser::FromClauseContext::FromClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::FromClauseContext::FROM() {
  return getToken(MiniSQLParser::FROM, 0);
}

std::vector<MiniSQLParser::TableReferenceContext *> MiniSQLParser::FromClauseContext::tableReference() {
  return getRuleContexts<MiniSQLParser::TableReferenceContext>();
}

MiniSQLParser::TableReferenceContext* MiniSQLParser::FromClauseContext::tableReference(size_t i) {
  return getRuleContext<MiniSQLParser::TableReferenceContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::FromClauseContext::COMMA() {
  return getTokens(MiniSQLParser::COMMA);
}

tree::TerminalNode* MiniSQLParser::FromClauseContext::COMMA(size_t i) {
  return getToken(MiniSQLParser::COMMA, i);
}


size_t MiniSQLParser::FromClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleFromClause;
}

void MiniSQLParser::FromClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromClause(this);
}

void MiniSQLParser::FromClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromClause(this);
}

MiniSQLParser::FromClauseContext* MiniSQLParser::fromClause() {
  FromClauseContext *_localctx = _tracker.createInstance<FromClauseContext>(_ctx, getState());
  enterRule(_localctx, 24, MiniSQLParser::RuleFromClause);
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
    setState(189);
    match(MiniSQLParser::FROM);
    setState(190);
    tableReference();
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::COMMA) {
      setState(191);
      match(MiniSQLParser::COMMA);
      setState(192);
      tableReference();
      setState(197);
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

//----------------- TableReferenceContext ------------------------------------------------------------------

MiniSQLParser::TableReferenceContext::TableReferenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::TablePrimaryContext* MiniSQLParser::TableReferenceContext::tablePrimary() {
  return getRuleContext<MiniSQLParser::TablePrimaryContext>(0);
}

std::vector<MiniSQLParser::JoinClauseContext *> MiniSQLParser::TableReferenceContext::joinClause() {
  return getRuleContexts<MiniSQLParser::JoinClauseContext>();
}

MiniSQLParser::JoinClauseContext* MiniSQLParser::TableReferenceContext::joinClause(size_t i) {
  return getRuleContext<MiniSQLParser::JoinClauseContext>(i);
}


size_t MiniSQLParser::TableReferenceContext::getRuleIndex() const {
  return MiniSQLParser::RuleTableReference;
}

void MiniSQLParser::TableReferenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTableReference(this);
}

void MiniSQLParser::TableReferenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTableReference(this);
}

MiniSQLParser::TableReferenceContext* MiniSQLParser::tableReference() {
  TableReferenceContext *_localctx = _tracker.createInstance<TableReferenceContext>(_ctx, getState());
  enterRule(_localctx, 26, MiniSQLParser::RuleTableReference);
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
    setState(198);
    tablePrimary();
    setState(202);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3112960) != 0)) {
      setState(199);
      joinClause();
      setState(204);
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

//----------------- TablePrimaryContext ------------------------------------------------------------------

MiniSQLParser::TablePrimaryContext::TablePrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::IdentifierContext *> MiniSQLParser::TablePrimaryContext::identifier() {
  return getRuleContexts<MiniSQLParser::IdentifierContext>();
}

MiniSQLParser::IdentifierContext* MiniSQLParser::TablePrimaryContext::identifier(size_t i) {
  return getRuleContext<MiniSQLParser::IdentifierContext>(i);
}

tree::TerminalNode* MiniSQLParser::TablePrimaryContext::AS() {
  return getToken(MiniSQLParser::AS, 0);
}

tree::TerminalNode* MiniSQLParser::TablePrimaryContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::TablePrimaryContext::queryExpression() {
  return getRuleContext<MiniSQLParser::QueryExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::TablePrimaryContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}


size_t MiniSQLParser::TablePrimaryContext::getRuleIndex() const {
  return MiniSQLParser::RuleTablePrimary;
}

void MiniSQLParser::TablePrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTablePrimary(this);
}

void MiniSQLParser::TablePrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTablePrimary(this);
}

MiniSQLParser::TablePrimaryContext* MiniSQLParser::tablePrimary() {
  TablePrimaryContext *_localctx = _tracker.createInstance<TablePrimaryContext>(_ctx, getState());
  enterRule(_localctx, 28, MiniSQLParser::RuleTablePrimary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(221);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::QUOTED_IDENTIFIER:
      case MiniSQLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(205);
        identifier();
        setState(210);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 3458764513837318144) != 0)) {
          setState(207);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == MiniSQLParser::AS) {
            setState(206);
            match(MiniSQLParser::AS);
          }
          setState(209);
          identifier();
        }
        break;
      }

      case MiniSQLParser::LPAREN: {
        enterOuterAlt(_localctx, 2);
        setState(212);
        match(MiniSQLParser::LPAREN);
        setState(213);
        queryExpression();
        setState(214);
        match(MiniSQLParser::RPAREN);
        setState(219);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 3458764513837318144) != 0)) {
          setState(216);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == MiniSQLParser::AS) {
            setState(215);
            match(MiniSQLParser::AS);
          }
          setState(218);
          identifier();
        }
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

//----------------- JoinClauseContext ------------------------------------------------------------------

MiniSQLParser::JoinClauseContext::JoinClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::JoinClauseContext::JOIN() {
  return getToken(MiniSQLParser::JOIN, 0);
}

MiniSQLParser::TablePrimaryContext* MiniSQLParser::JoinClauseContext::tablePrimary() {
  return getRuleContext<MiniSQLParser::TablePrimaryContext>(0);
}

MiniSQLParser::JoinTypeContext* MiniSQLParser::JoinClauseContext::joinType() {
  return getRuleContext<MiniSQLParser::JoinTypeContext>(0);
}

MiniSQLParser::JoinConditionContext* MiniSQLParser::JoinClauseContext::joinCondition() {
  return getRuleContext<MiniSQLParser::JoinConditionContext>(0);
}


size_t MiniSQLParser::JoinClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleJoinClause;
}

void MiniSQLParser::JoinClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinClause(this);
}

void MiniSQLParser::JoinClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinClause(this);
}

MiniSQLParser::JoinClauseContext* MiniSQLParser::joinClause() {
  JoinClauseContext *_localctx = _tracker.createInstance<JoinClauseContext>(_ctx, getState());
  enterRule(_localctx, 30, MiniSQLParser::RuleJoinClause);
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
    setState(224);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3080192) != 0)) {
      setState(223);
      joinType();
    }
    setState(226);
    match(MiniSQLParser::JOIN);
    setState(227);
    tablePrimary();
    setState(229);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::ON

    || _la == MiniSQLParser::USING) {
      setState(228);
      joinCondition();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JoinTypeContext ------------------------------------------------------------------

MiniSQLParser::JoinTypeContext::JoinTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::JoinTypeContext::INNER() {
  return getToken(MiniSQLParser::INNER, 0);
}

tree::TerminalNode* MiniSQLParser::JoinTypeContext::LEFT() {
  return getToken(MiniSQLParser::LEFT, 0);
}

tree::TerminalNode* MiniSQLParser::JoinTypeContext::OUTER() {
  return getToken(MiniSQLParser::OUTER, 0);
}

tree::TerminalNode* MiniSQLParser::JoinTypeContext::RIGHT() {
  return getToken(MiniSQLParser::RIGHT, 0);
}

tree::TerminalNode* MiniSQLParser::JoinTypeContext::FULL() {
  return getToken(MiniSQLParser::FULL, 0);
}

tree::TerminalNode* MiniSQLParser::JoinTypeContext::CROSS() {
  return getToken(MiniSQLParser::CROSS, 0);
}


size_t MiniSQLParser::JoinTypeContext::getRuleIndex() const {
  return MiniSQLParser::RuleJoinType;
}

void MiniSQLParser::JoinTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinType(this);
}

void MiniSQLParser::JoinTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinType(this);
}

MiniSQLParser::JoinTypeContext* MiniSQLParser::joinType() {
  JoinTypeContext *_localctx = _tracker.createInstance<JoinTypeContext>(_ctx, getState());
  enterRule(_localctx, 32, MiniSQLParser::RuleJoinType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(245);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::INNER: {
        enterOuterAlt(_localctx, 1);
        setState(231);
        match(MiniSQLParser::INNER);
        break;
      }

      case MiniSQLParser::LEFT: {
        enterOuterAlt(_localctx, 2);
        setState(232);
        match(MiniSQLParser::LEFT);
        setState(234);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MiniSQLParser::OUTER) {
          setState(233);
          match(MiniSQLParser::OUTER);
        }
        break;
      }

      case MiniSQLParser::RIGHT: {
        enterOuterAlt(_localctx, 3);
        setState(236);
        match(MiniSQLParser::RIGHT);
        setState(238);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MiniSQLParser::OUTER) {
          setState(237);
          match(MiniSQLParser::OUTER);
        }
        break;
      }

      case MiniSQLParser::FULL: {
        enterOuterAlt(_localctx, 4);
        setState(240);
        match(MiniSQLParser::FULL);
        setState(242);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == MiniSQLParser::OUTER) {
          setState(241);
          match(MiniSQLParser::OUTER);
        }
        break;
      }

      case MiniSQLParser::CROSS: {
        enterOuterAlt(_localctx, 5);
        setState(244);
        match(MiniSQLParser::CROSS);
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

//----------------- JoinConditionContext ------------------------------------------------------------------

MiniSQLParser::JoinConditionContext::JoinConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::JoinConditionContext::ON() {
  return getToken(MiniSQLParser::ON, 0);
}

MiniSQLParser::ExpressionContext* MiniSQLParser::JoinConditionContext::expression() {
  return getRuleContext<MiniSQLParser::ExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::JoinConditionContext::USING() {
  return getToken(MiniSQLParser::USING, 0);
}

tree::TerminalNode* MiniSQLParser::JoinConditionContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

std::vector<MiniSQLParser::IdentifierContext *> MiniSQLParser::JoinConditionContext::identifier() {
  return getRuleContexts<MiniSQLParser::IdentifierContext>();
}

MiniSQLParser::IdentifierContext* MiniSQLParser::JoinConditionContext::identifier(size_t i) {
  return getRuleContext<MiniSQLParser::IdentifierContext>(i);
}

tree::TerminalNode* MiniSQLParser::JoinConditionContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> MiniSQLParser::JoinConditionContext::COMMA() {
  return getTokens(MiniSQLParser::COMMA);
}

tree::TerminalNode* MiniSQLParser::JoinConditionContext::COMMA(size_t i) {
  return getToken(MiniSQLParser::COMMA, i);
}


size_t MiniSQLParser::JoinConditionContext::getRuleIndex() const {
  return MiniSQLParser::RuleJoinCondition;
}

void MiniSQLParser::JoinConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinCondition(this);
}

void MiniSQLParser::JoinConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinCondition(this);
}

MiniSQLParser::JoinConditionContext* MiniSQLParser::joinCondition() {
  JoinConditionContext *_localctx = _tracker.createInstance<JoinConditionContext>(_ctx, getState());
  enterRule(_localctx, 34, MiniSQLParser::RuleJoinCondition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(261);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::ON: {
        enterOuterAlt(_localctx, 1);
        setState(247);
        match(MiniSQLParser::ON);
        setState(248);
        expression();
        break;
      }

      case MiniSQLParser::USING: {
        enterOuterAlt(_localctx, 2);
        setState(249);
        match(MiniSQLParser::USING);
        setState(250);
        match(MiniSQLParser::LPAREN);
        setState(251);
        identifier();
        setState(256);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MiniSQLParser::COMMA) {
          setState(252);
          match(MiniSQLParser::COMMA);
          setState(253);
          identifier();
          setState(258);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(259);
        match(MiniSQLParser::RPAREN);
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

//----------------- WhereClauseContext ------------------------------------------------------------------

MiniSQLParser::WhereClauseContext::WhereClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::WhereClauseContext::WHERE() {
  return getToken(MiniSQLParser::WHERE, 0);
}

MiniSQLParser::ExpressionContext* MiniSQLParser::WhereClauseContext::expression() {
  return getRuleContext<MiniSQLParser::ExpressionContext>(0);
}


size_t MiniSQLParser::WhereClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleWhereClause;
}

void MiniSQLParser::WhereClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhereClause(this);
}

void MiniSQLParser::WhereClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhereClause(this);
}

MiniSQLParser::WhereClauseContext* MiniSQLParser::whereClause() {
  WhereClauseContext *_localctx = _tracker.createInstance<WhereClauseContext>(_ctx, getState());
  enterRule(_localctx, 36, MiniSQLParser::RuleWhereClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    match(MiniSQLParser::WHERE);
    setState(264);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupByClauseContext ------------------------------------------------------------------

MiniSQLParser::GroupByClauseContext::GroupByClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::GroupByClauseContext::GROUP() {
  return getToken(MiniSQLParser::GROUP, 0);
}

tree::TerminalNode* MiniSQLParser::GroupByClauseContext::BY() {
  return getToken(MiniSQLParser::BY, 0);
}

MiniSQLParser::ExpressionListContext* MiniSQLParser::GroupByClauseContext::expressionList() {
  return getRuleContext<MiniSQLParser::ExpressionListContext>(0);
}


size_t MiniSQLParser::GroupByClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleGroupByClause;
}

void MiniSQLParser::GroupByClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGroupByClause(this);
}

void MiniSQLParser::GroupByClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGroupByClause(this);
}

MiniSQLParser::GroupByClauseContext* MiniSQLParser::groupByClause() {
  GroupByClauseContext *_localctx = _tracker.createInstance<GroupByClauseContext>(_ctx, getState());
  enterRule(_localctx, 38, MiniSQLParser::RuleGroupByClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(266);
    match(MiniSQLParser::GROUP);
    setState(267);
    match(MiniSQLParser::BY);
    setState(268);
    expressionList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HavingClauseContext ------------------------------------------------------------------

MiniSQLParser::HavingClauseContext::HavingClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::HavingClauseContext::HAVING() {
  return getToken(MiniSQLParser::HAVING, 0);
}

MiniSQLParser::ExpressionContext* MiniSQLParser::HavingClauseContext::expression() {
  return getRuleContext<MiniSQLParser::ExpressionContext>(0);
}


size_t MiniSQLParser::HavingClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleHavingClause;
}

void MiniSQLParser::HavingClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHavingClause(this);
}

void MiniSQLParser::HavingClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHavingClause(this);
}

MiniSQLParser::HavingClauseContext* MiniSQLParser::havingClause() {
  HavingClauseContext *_localctx = _tracker.createInstance<HavingClauseContext>(_ctx, getState());
  enterRule(_localctx, 40, MiniSQLParser::RuleHavingClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    match(MiniSQLParser::HAVING);
    setState(271);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrderByClauseContext ------------------------------------------------------------------

MiniSQLParser::OrderByClauseContext::OrderByClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::OrderByClauseContext::ORDER() {
  return getToken(MiniSQLParser::ORDER, 0);
}

tree::TerminalNode* MiniSQLParser::OrderByClauseContext::BY() {
  return getToken(MiniSQLParser::BY, 0);
}

std::vector<MiniSQLParser::OrderItemContext *> MiniSQLParser::OrderByClauseContext::orderItem() {
  return getRuleContexts<MiniSQLParser::OrderItemContext>();
}

MiniSQLParser::OrderItemContext* MiniSQLParser::OrderByClauseContext::orderItem(size_t i) {
  return getRuleContext<MiniSQLParser::OrderItemContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::OrderByClauseContext::COMMA() {
  return getTokens(MiniSQLParser::COMMA);
}

tree::TerminalNode* MiniSQLParser::OrderByClauseContext::COMMA(size_t i) {
  return getToken(MiniSQLParser::COMMA, i);
}


size_t MiniSQLParser::OrderByClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleOrderByClause;
}

void MiniSQLParser::OrderByClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrderByClause(this);
}

void MiniSQLParser::OrderByClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrderByClause(this);
}

MiniSQLParser::OrderByClauseContext* MiniSQLParser::orderByClause() {
  OrderByClauseContext *_localctx = _tracker.createInstance<OrderByClauseContext>(_ctx, getState());
  enterRule(_localctx, 42, MiniSQLParser::RuleOrderByClause);
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
    setState(273);
    match(MiniSQLParser::ORDER);
    setState(274);
    match(MiniSQLParser::BY);
    setState(275);
    orderItem();
    setState(280);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::COMMA) {
      setState(276);
      match(MiniSQLParser::COMMA);
      setState(277);
      orderItem();
      setState(282);
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

//----------------- OrderItemContext ------------------------------------------------------------------

MiniSQLParser::OrderItemContext::OrderItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::ExpressionContext* MiniSQLParser::OrderItemContext::expression() {
  return getRuleContext<MiniSQLParser::ExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::OrderItemContext::ASC() {
  return getToken(MiniSQLParser::ASC, 0);
}

tree::TerminalNode* MiniSQLParser::OrderItemContext::DESC() {
  return getToken(MiniSQLParser::DESC, 0);
}


size_t MiniSQLParser::OrderItemContext::getRuleIndex() const {
  return MiniSQLParser::RuleOrderItem;
}

void MiniSQLParser::OrderItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrderItem(this);
}

void MiniSQLParser::OrderItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrderItem(this);
}

MiniSQLParser::OrderItemContext* MiniSQLParser::orderItem() {
  OrderItemContext *_localctx = _tracker.createInstance<OrderItemContext>(_ctx, getState());
  enterRule(_localctx, 44, MiniSQLParser::RuleOrderItem);
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
    setState(283);
    expression();
    setState(285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::ASC

    || _la == MiniSQLParser::DESC) {
      setState(284);
      _la = _input->LA(1);
      if (!(_la == MiniSQLParser::ASC

      || _la == MiniSQLParser::DESC)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LimitClauseContext ------------------------------------------------------------------

MiniSQLParser::LimitClauseContext::LimitClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::LimitClauseContext::LIMIT() {
  return getToken(MiniSQLParser::LIMIT, 0);
}

std::vector<MiniSQLParser::ExpressionContext *> MiniSQLParser::LimitClauseContext::expression() {
  return getRuleContexts<MiniSQLParser::ExpressionContext>();
}

MiniSQLParser::ExpressionContext* MiniSQLParser::LimitClauseContext::expression(size_t i) {
  return getRuleContext<MiniSQLParser::ExpressionContext>(i);
}

tree::TerminalNode* MiniSQLParser::LimitClauseContext::OFFSET() {
  return getToken(MiniSQLParser::OFFSET, 0);
}


size_t MiniSQLParser::LimitClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleLimitClause;
}

void MiniSQLParser::LimitClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLimitClause(this);
}

void MiniSQLParser::LimitClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLimitClause(this);
}

MiniSQLParser::LimitClauseContext* MiniSQLParser::limitClause() {
  LimitClauseContext *_localctx = _tracker.createInstance<LimitClauseContext>(_ctx, getState());
  enterRule(_localctx, 46, MiniSQLParser::RuleLimitClause);
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
    setState(287);
    match(MiniSQLParser::LIMIT);
    setState(288);
    expression();
    setState(291);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::OFFSET) {
      setState(289);
      match(MiniSQLParser::OFFSET);
      setState(290);
      expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

MiniSQLParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::OrExpressionContext* MiniSQLParser::ExpressionContext::orExpression() {
  return getRuleContext<MiniSQLParser::OrExpressionContext>(0);
}


size_t MiniSQLParser::ExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleExpression;
}

void MiniSQLParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void MiniSQLParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

MiniSQLParser::ExpressionContext* MiniSQLParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 48, MiniSQLParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    orExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrExpressionContext ------------------------------------------------------------------

MiniSQLParser::OrExpressionContext::OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::AndExpressionContext *> MiniSQLParser::OrExpressionContext::andExpression() {
  return getRuleContexts<MiniSQLParser::AndExpressionContext>();
}

MiniSQLParser::AndExpressionContext* MiniSQLParser::OrExpressionContext::andExpression(size_t i) {
  return getRuleContext<MiniSQLParser::AndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::OrExpressionContext::OR() {
  return getTokens(MiniSQLParser::OR);
}

tree::TerminalNode* MiniSQLParser::OrExpressionContext::OR(size_t i) {
  return getToken(MiniSQLParser::OR, i);
}


size_t MiniSQLParser::OrExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleOrExpression;
}

void MiniSQLParser::OrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrExpression(this);
}

void MiniSQLParser::OrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrExpression(this);
}

MiniSQLParser::OrExpressionContext* MiniSQLParser::orExpression() {
  OrExpressionContext *_localctx = _tracker.createInstance<OrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, MiniSQLParser::RuleOrExpression);
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
    setState(295);
    andExpression();
    setState(300);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::OR) {
      setState(296);
      match(MiniSQLParser::OR);
      setState(297);
      andExpression();
      setState(302);
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

//----------------- AndExpressionContext ------------------------------------------------------------------

MiniSQLParser::AndExpressionContext::AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::NotExpressionContext *> MiniSQLParser::AndExpressionContext::notExpression() {
  return getRuleContexts<MiniSQLParser::NotExpressionContext>();
}

MiniSQLParser::NotExpressionContext* MiniSQLParser::AndExpressionContext::notExpression(size_t i) {
  return getRuleContext<MiniSQLParser::NotExpressionContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::AndExpressionContext::AND() {
  return getTokens(MiniSQLParser::AND);
}

tree::TerminalNode* MiniSQLParser::AndExpressionContext::AND(size_t i) {
  return getToken(MiniSQLParser::AND, i);
}


size_t MiniSQLParser::AndExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleAndExpression;
}

void MiniSQLParser::AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndExpression(this);
}

void MiniSQLParser::AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndExpression(this);
}

MiniSQLParser::AndExpressionContext* MiniSQLParser::andExpression() {
  AndExpressionContext *_localctx = _tracker.createInstance<AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 52, MiniSQLParser::RuleAndExpression);
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
    setState(303);
    notExpression();
    setState(308);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::AND) {
      setState(304);
      match(MiniSQLParser::AND);
      setState(305);
      notExpression();
      setState(310);
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

//----------------- NotExpressionContext ------------------------------------------------------------------

MiniSQLParser::NotExpressionContext::NotExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::NotExpressionContext::NOT() {
  return getToken(MiniSQLParser::NOT, 0);
}

MiniSQLParser::NotExpressionContext* MiniSQLParser::NotExpressionContext::notExpression() {
  return getRuleContext<MiniSQLParser::NotExpressionContext>(0);
}

MiniSQLParser::ComparisonExpressionContext* MiniSQLParser::NotExpressionContext::comparisonExpression() {
  return getRuleContext<MiniSQLParser::ComparisonExpressionContext>(0);
}


size_t MiniSQLParser::NotExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleNotExpression;
}

void MiniSQLParser::NotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotExpression(this);
}

void MiniSQLParser::NotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotExpression(this);
}

MiniSQLParser::NotExpressionContext* MiniSQLParser::notExpression() {
  NotExpressionContext *_localctx = _tracker.createInstance<NotExpressionContext>(_ctx, getState());
  enterRule(_localctx, 54, MiniSQLParser::RuleNotExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(314);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(311);
        match(MiniSQLParser::NOT);
        setState(312);
        notExpression();
        break;
      }

      case MiniSQLParser::NULL_:
      case MiniSQLParser::TRUE:
      case MiniSQLParser::FALSE:
      case MiniSQLParser::CASE:
      case MiniSQLParser::PLUS:
      case MiniSQLParser::MINUS:
      case MiniSQLParser::LPAREN:
      case MiniSQLParser::NUMBER:
      case MiniSQLParser::STRING:
      case MiniSQLParser::QUOTED_IDENTIFIER:
      case MiniSQLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(313);
        comparisonExpression();
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

//----------------- ComparisonExpressionContext ------------------------------------------------------------------

MiniSQLParser::ComparisonExpressionContext::ComparisonExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::AdditiveExpressionContext *> MiniSQLParser::ComparisonExpressionContext::additiveExpression() {
  return getRuleContexts<MiniSQLParser::AdditiveExpressionContext>();
}

MiniSQLParser::AdditiveExpressionContext* MiniSQLParser::ComparisonExpressionContext::additiveExpression(size_t i) {
  return getRuleContext<MiniSQLParser::AdditiveExpressionContext>(i);
}

MiniSQLParser::ComparisonOperatorContext* MiniSQLParser::ComparisonExpressionContext::comparisonOperator() {
  return getRuleContext<MiniSQLParser::ComparisonOperatorContext>(0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::IS() {
  return getToken(MiniSQLParser::IS, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::NULL_() {
  return getToken(MiniSQLParser::NULL_, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::TRUE() {
  return getToken(MiniSQLParser::TRUE, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::FALSE() {
  return getToken(MiniSQLParser::FALSE, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::IN() {
  return getToken(MiniSQLParser::IN, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

MiniSQLParser::InExpressionContext* MiniSQLParser::ComparisonExpressionContext::inExpression() {
  return getRuleContext<MiniSQLParser::InExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::NOT() {
  return getToken(MiniSQLParser::NOT, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::LIKE() {
  return getToken(MiniSQLParser::LIKE, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::BETWEEN() {
  return getToken(MiniSQLParser::BETWEEN, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::AND() {
  return getToken(MiniSQLParser::AND, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonExpressionContext::EXISTS() {
  return getToken(MiniSQLParser::EXISTS, 0);
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::ComparisonExpressionContext::queryExpression() {
  return getRuleContext<MiniSQLParser::QueryExpressionContext>(0);
}


size_t MiniSQLParser::ComparisonExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleComparisonExpression;
}

void MiniSQLParser::ComparisonExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparisonExpression(this);
}

void MiniSQLParser::ComparisonExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparisonExpression(this);
}

MiniSQLParser::ComparisonExpressionContext* MiniSQLParser::comparisonExpression() {
  ComparisonExpressionContext *_localctx = _tracker.createInstance<ComparisonExpressionContext>(_ctx, getState());
  enterRule(_localctx, 56, MiniSQLParser::RuleComparisonExpression);
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
    setState(316);
    additiveExpression();
    setState(373);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      setState(317);
      comparisonOperator();
      setState(318);
      additiveExpression();
      break;
    }

    case 2: {
      setState(320);
      match(MiniSQLParser::IS);
      setState(322);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MiniSQLParser::NOT) {
        setState(321);
        match(MiniSQLParser::NOT);
      }
      setState(324);
      match(MiniSQLParser::NULL_);
      break;
    }

    case 3: {
      setState(325);
      match(MiniSQLParser::IS);
      setState(327);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MiniSQLParser::NOT) {
        setState(326);
        match(MiniSQLParser::NOT);
      }
      setState(329);
      match(MiniSQLParser::TRUE);
      break;
    }

    case 4: {
      setState(330);
      match(MiniSQLParser::IS);
      setState(332);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MiniSQLParser::NOT) {
        setState(331);
        match(MiniSQLParser::NOT);
      }
      setState(334);
      match(MiniSQLParser::FALSE);
      break;
    }

    case 5: {
      setState(335);
      match(MiniSQLParser::IN);
      setState(336);
      match(MiniSQLParser::LPAREN);
      setState(337);
      inExpression();
      setState(338);
      match(MiniSQLParser::RPAREN);
      break;
    }

    case 6: {
      setState(340);
      match(MiniSQLParser::NOT);
      setState(341);
      match(MiniSQLParser::IN);
      setState(342);
      match(MiniSQLParser::LPAREN);
      setState(343);
      inExpression();
      setState(344);
      match(MiniSQLParser::RPAREN);
      break;
    }

    case 7: {
      setState(346);
      match(MiniSQLParser::LIKE);
      setState(347);
      additiveExpression();
      break;
    }

    case 8: {
      setState(348);
      match(MiniSQLParser::NOT);
      setState(349);
      match(MiniSQLParser::LIKE);
      setState(350);
      additiveExpression();
      break;
    }

    case 9: {
      setState(351);
      match(MiniSQLParser::BETWEEN);
      setState(352);
      additiveExpression();
      setState(353);
      match(MiniSQLParser::AND);
      setState(354);
      additiveExpression();
      break;
    }

    case 10: {
      setState(356);
      match(MiniSQLParser::NOT);
      setState(357);
      match(MiniSQLParser::BETWEEN);
      setState(358);
      additiveExpression();
      setState(359);
      match(MiniSQLParser::AND);
      setState(360);
      additiveExpression();
      break;
    }

    case 11: {
      setState(362);
      match(MiniSQLParser::EXISTS);
      setState(363);
      match(MiniSQLParser::LPAREN);
      setState(364);
      queryExpression();
      setState(365);
      match(MiniSQLParser::RPAREN);
      break;
    }

    case 12: {
      setState(367);
      match(MiniSQLParser::NOT);
      setState(368);
      match(MiniSQLParser::EXISTS);
      setState(369);
      match(MiniSQLParser::LPAREN);
      setState(370);
      queryExpression();
      setState(371);
      match(MiniSQLParser::RPAREN);
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

//----------------- ComparisonOperatorContext ------------------------------------------------------------------

MiniSQLParser::ComparisonOperatorContext::ComparisonOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::ComparisonOperatorContext::EQ() {
  return getToken(MiniSQLParser::EQ, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonOperatorContext::NE() {
  return getToken(MiniSQLParser::NE, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonOperatorContext::LT() {
  return getToken(MiniSQLParser::LT, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonOperatorContext::LE() {
  return getToken(MiniSQLParser::LE, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonOperatorContext::GT() {
  return getToken(MiniSQLParser::GT, 0);
}

tree::TerminalNode* MiniSQLParser::ComparisonOperatorContext::GE() {
  return getToken(MiniSQLParser::GE, 0);
}


size_t MiniSQLParser::ComparisonOperatorContext::getRuleIndex() const {
  return MiniSQLParser::RuleComparisonOperator;
}

void MiniSQLParser::ComparisonOperatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparisonOperator(this);
}

void MiniSQLParser::ComparisonOperatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparisonOperator(this);
}

MiniSQLParser::ComparisonOperatorContext* MiniSQLParser::comparisonOperator() {
  ComparisonOperatorContext *_localctx = _tracker.createInstance<ComparisonOperatorContext>(_ctx, getState());
  enterRule(_localctx, 58, MiniSQLParser::RuleComparisonOperator);
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
    setState(375);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 554153860399104) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

MiniSQLParser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::MultiplicativeExpressionContext *> MiniSQLParser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<MiniSQLParser::MultiplicativeExpressionContext>();
}

MiniSQLParser::MultiplicativeExpressionContext* MiniSQLParser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<MiniSQLParser::MultiplicativeExpressionContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::AdditiveExpressionContext::PLUS() {
  return getTokens(MiniSQLParser::PLUS);
}

tree::TerminalNode* MiniSQLParser::AdditiveExpressionContext::PLUS(size_t i) {
  return getToken(MiniSQLParser::PLUS, i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::AdditiveExpressionContext::MINUS() {
  return getTokens(MiniSQLParser::MINUS);
}

tree::TerminalNode* MiniSQLParser::AdditiveExpressionContext::MINUS(size_t i) {
  return getToken(MiniSQLParser::MINUS, i);
}


size_t MiniSQLParser::AdditiveExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleAdditiveExpression;
}

void MiniSQLParser::AdditiveExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditiveExpression(this);
}

void MiniSQLParser::AdditiveExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditiveExpression(this);
}

MiniSQLParser::AdditiveExpressionContext* MiniSQLParser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 60, MiniSQLParser::RuleAdditiveExpression);
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
    setState(377);
    multiplicativeExpression();
    setState(382);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::PLUS

    || _la == MiniSQLParser::MINUS) {
      setState(378);
      _la = _input->LA(1);
      if (!(_la == MiniSQLParser::PLUS

      || _la == MiniSQLParser::MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(379);
      multiplicativeExpression();
      setState(384);
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

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

MiniSQLParser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::UnaryExpressionContext *> MiniSQLParser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<MiniSQLParser::UnaryExpressionContext>();
}

MiniSQLParser::UnaryExpressionContext* MiniSQLParser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<MiniSQLParser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::MultiplicativeExpressionContext::STAR() {
  return getTokens(MiniSQLParser::STAR);
}

tree::TerminalNode* MiniSQLParser::MultiplicativeExpressionContext::STAR(size_t i) {
  return getToken(MiniSQLParser::STAR, i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::MultiplicativeExpressionContext::DIV() {
  return getTokens(MiniSQLParser::DIV);
}

tree::TerminalNode* MiniSQLParser::MultiplicativeExpressionContext::DIV(size_t i) {
  return getToken(MiniSQLParser::DIV, i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::MultiplicativeExpressionContext::MOD() {
  return getTokens(MiniSQLParser::MOD);
}

tree::TerminalNode* MiniSQLParser::MultiplicativeExpressionContext::MOD(size_t i) {
  return getToken(MiniSQLParser::MOD, i);
}


size_t MiniSQLParser::MultiplicativeExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleMultiplicativeExpression;
}

void MiniSQLParser::MultiplicativeExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicativeExpression(this);
}

void MiniSQLParser::MultiplicativeExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicativeExpression(this);
}

MiniSQLParser::MultiplicativeExpressionContext* MiniSQLParser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 62, MiniSQLParser::RuleMultiplicativeExpression);
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
    setState(385);
    unaryExpression();
    setState(390);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 15762598695796736) != 0)) {
      setState(386);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 15762598695796736) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(387);
      unaryExpression();
      setState(392);
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

//----------------- UnaryExpressionContext ------------------------------------------------------------------

MiniSQLParser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::UnaryExpressionContext::PLUS() {
  return getToken(MiniSQLParser::PLUS, 0);
}

MiniSQLParser::UnaryExpressionContext* MiniSQLParser::UnaryExpressionContext::unaryExpression() {
  return getRuleContext<MiniSQLParser::UnaryExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::UnaryExpressionContext::MINUS() {
  return getToken(MiniSQLParser::MINUS, 0);
}

MiniSQLParser::PrimaryExpressionContext* MiniSQLParser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<MiniSQLParser::PrimaryExpressionContext>(0);
}


size_t MiniSQLParser::UnaryExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleUnaryExpression;
}

void MiniSQLParser::UnaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnaryExpression(this);
}

void MiniSQLParser::UnaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnaryExpression(this);
}

MiniSQLParser::UnaryExpressionContext* MiniSQLParser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 64, MiniSQLParser::RuleUnaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(398);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::PLUS: {
        enterOuterAlt(_localctx, 1);
        setState(393);
        match(MiniSQLParser::PLUS);
        setState(394);
        unaryExpression();
        break;
      }

      case MiniSQLParser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(395);
        match(MiniSQLParser::MINUS);
        setState(396);
        unaryExpression();
        break;
      }

      case MiniSQLParser::NULL_:
      case MiniSQLParser::TRUE:
      case MiniSQLParser::FALSE:
      case MiniSQLParser::CASE:
      case MiniSQLParser::LPAREN:
      case MiniSQLParser::NUMBER:
      case MiniSQLParser::STRING:
      case MiniSQLParser::QUOTED_IDENTIFIER:
      case MiniSQLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(397);
        primaryExpression();
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

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

MiniSQLParser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::LiteralContext* MiniSQLParser::PrimaryExpressionContext::literal() {
  return getRuleContext<MiniSQLParser::LiteralContext>(0);
}

MiniSQLParser::ColumnReferenceContext* MiniSQLParser::PrimaryExpressionContext::columnReference() {
  return getRuleContext<MiniSQLParser::ColumnReferenceContext>(0);
}

MiniSQLParser::FunctionCallContext* MiniSQLParser::PrimaryExpressionContext::functionCall() {
  return getRuleContext<MiniSQLParser::FunctionCallContext>(0);
}

MiniSQLParser::CaseExpressionContext* MiniSQLParser::PrimaryExpressionContext::caseExpression() {
  return getRuleContext<MiniSQLParser::CaseExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::PrimaryExpressionContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

MiniSQLParser::ExpressionContext* MiniSQLParser::PrimaryExpressionContext::expression() {
  return getRuleContext<MiniSQLParser::ExpressionContext>(0);
}

tree::TerminalNode* MiniSQLParser::PrimaryExpressionContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::PrimaryExpressionContext::queryExpression() {
  return getRuleContext<MiniSQLParser::QueryExpressionContext>(0);
}


size_t MiniSQLParser::PrimaryExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RulePrimaryExpression;
}

void MiniSQLParser::PrimaryExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpression(this);
}

void MiniSQLParser::PrimaryExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpression(this);
}

MiniSQLParser::PrimaryExpressionContext* MiniSQLParser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 66, MiniSQLParser::RulePrimaryExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(412);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(400);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(401);
      columnReference();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(402);
      functionCall();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(403);
      caseExpression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(404);
      match(MiniSQLParser::LPAREN);
      setState(405);
      expression();
      setState(406);
      match(MiniSQLParser::RPAREN);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(408);
      match(MiniSQLParser::LPAREN);
      setState(409);
      queryExpression();
      setState(410);
      match(MiniSQLParser::RPAREN);
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

//----------------- ColumnReferenceContext ------------------------------------------------------------------

MiniSQLParser::ColumnReferenceContext::ColumnReferenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::IdentifierContext *> MiniSQLParser::ColumnReferenceContext::identifier() {
  return getRuleContexts<MiniSQLParser::IdentifierContext>();
}

MiniSQLParser::IdentifierContext* MiniSQLParser::ColumnReferenceContext::identifier(size_t i) {
  return getRuleContext<MiniSQLParser::IdentifierContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::ColumnReferenceContext::DOT() {
  return getTokens(MiniSQLParser::DOT);
}

tree::TerminalNode* MiniSQLParser::ColumnReferenceContext::DOT(size_t i) {
  return getToken(MiniSQLParser::DOT, i);
}


size_t MiniSQLParser::ColumnReferenceContext::getRuleIndex() const {
  return MiniSQLParser::RuleColumnReference;
}

void MiniSQLParser::ColumnReferenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnReference(this);
}

void MiniSQLParser::ColumnReferenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnReference(this);
}

MiniSQLParser::ColumnReferenceContext* MiniSQLParser::columnReference() {
  ColumnReferenceContext *_localctx = _tracker.createInstance<ColumnReferenceContext>(_ctx, getState());
  enterRule(_localctx, 68, MiniSQLParser::RuleColumnReference);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(425);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(414);
      identifier();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(415);
      identifier();
      setState(416);
      match(MiniSQLParser::DOT);
      setState(417);
      identifier();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(419);
      identifier();
      setState(420);
      match(MiniSQLParser::DOT);
      setState(421);
      identifier();
      setState(422);
      match(MiniSQLParser::DOT);
      setState(423);
      identifier();
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

//----------------- FunctionCallContext ------------------------------------------------------------------

MiniSQLParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::IdentifierContext* MiniSQLParser::FunctionCallContext::identifier() {
  return getRuleContext<MiniSQLParser::IdentifierContext>(0);
}

tree::TerminalNode* MiniSQLParser::FunctionCallContext::LPAREN() {
  return getToken(MiniSQLParser::LPAREN, 0);
}

tree::TerminalNode* MiniSQLParser::FunctionCallContext::RPAREN() {
  return getToken(MiniSQLParser::RPAREN, 0);
}

MiniSQLParser::FunctionArgumentsContext* MiniSQLParser::FunctionCallContext::functionArguments() {
  return getRuleContext<MiniSQLParser::FunctionArgumentsContext>(0);
}


size_t MiniSQLParser::FunctionCallContext::getRuleIndex() const {
  return MiniSQLParser::RuleFunctionCall;
}

void MiniSQLParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void MiniSQLParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

MiniSQLParser::FunctionCallContext* MiniSQLParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 70, MiniSQLParser::RuleFunctionCall);
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
    setState(427);
    identifier();
    setState(428);
    match(MiniSQLParser::LPAREN);
    setState(430);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4345411025600774144) != 0)) {
      setState(429);
      functionArguments();
    }
    setState(432);
    match(MiniSQLParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionArgumentsContext ------------------------------------------------------------------

MiniSQLParser::FunctionArgumentsContext::FunctionArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::FunctionArgumentsContext::STAR() {
  return getToken(MiniSQLParser::STAR, 0);
}

MiniSQLParser::ExpressionListContext* MiniSQLParser::FunctionArgumentsContext::expressionList() {
  return getRuleContext<MiniSQLParser::ExpressionListContext>(0);
}


size_t MiniSQLParser::FunctionArgumentsContext::getRuleIndex() const {
  return MiniSQLParser::RuleFunctionArguments;
}

void MiniSQLParser::FunctionArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionArguments(this);
}

void MiniSQLParser::FunctionArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionArguments(this);
}

MiniSQLParser::FunctionArgumentsContext* MiniSQLParser::functionArguments() {
  FunctionArgumentsContext *_localctx = _tracker.createInstance<FunctionArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 72, MiniSQLParser::RuleFunctionArguments);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(436);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniSQLParser::STAR: {
        enterOuterAlt(_localctx, 1);
        setState(434);
        match(MiniSQLParser::STAR);
        break;
      }

      case MiniSQLParser::NOT:
      case MiniSQLParser::NULL_:
      case MiniSQLParser::TRUE:
      case MiniSQLParser::FALSE:
      case MiniSQLParser::CASE:
      case MiniSQLParser::PLUS:
      case MiniSQLParser::MINUS:
      case MiniSQLParser::LPAREN:
      case MiniSQLParser::NUMBER:
      case MiniSQLParser::STRING:
      case MiniSQLParser::QUOTED_IDENTIFIER:
      case MiniSQLParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(435);
        expressionList();
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

//----------------- CaseExpressionContext ------------------------------------------------------------------

MiniSQLParser::CaseExpressionContext::CaseExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::CaseExpressionContext::CASE() {
  return getToken(MiniSQLParser::CASE, 0);
}

tree::TerminalNode* MiniSQLParser::CaseExpressionContext::END() {
  return getToken(MiniSQLParser::END, 0);
}

std::vector<MiniSQLParser::ExpressionContext *> MiniSQLParser::CaseExpressionContext::expression() {
  return getRuleContexts<MiniSQLParser::ExpressionContext>();
}

MiniSQLParser::ExpressionContext* MiniSQLParser::CaseExpressionContext::expression(size_t i) {
  return getRuleContext<MiniSQLParser::ExpressionContext>(i);
}

std::vector<MiniSQLParser::WhenClauseContext *> MiniSQLParser::CaseExpressionContext::whenClause() {
  return getRuleContexts<MiniSQLParser::WhenClauseContext>();
}

MiniSQLParser::WhenClauseContext* MiniSQLParser::CaseExpressionContext::whenClause(size_t i) {
  return getRuleContext<MiniSQLParser::WhenClauseContext>(i);
}

tree::TerminalNode* MiniSQLParser::CaseExpressionContext::ELSE() {
  return getToken(MiniSQLParser::ELSE, 0);
}


size_t MiniSQLParser::CaseExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleCaseExpression;
}

void MiniSQLParser::CaseExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaseExpression(this);
}

void MiniSQLParser::CaseExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaseExpression(this);
}

MiniSQLParser::CaseExpressionContext* MiniSQLParser::caseExpression() {
  CaseExpressionContext *_localctx = _tracker.createInstance<CaseExpressionContext>(_ctx, getState());
  enterRule(_localctx, 74, MiniSQLParser::RuleCaseExpression);
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
    setState(438);
    match(MiniSQLParser::CASE);
    setState(440);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4343159225787088896) != 0)) {
      setState(439);
      expression();
    }
    setState(443); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(442);
      whenClause();
      setState(445); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == MiniSQLParser::WHEN);
    setState(449);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniSQLParser::ELSE) {
      setState(447);
      match(MiniSQLParser::ELSE);
      setState(448);
      expression();
    }
    setState(451);
    match(MiniSQLParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhenClauseContext ------------------------------------------------------------------

MiniSQLParser::WhenClauseContext::WhenClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::WhenClauseContext::WHEN() {
  return getToken(MiniSQLParser::WHEN, 0);
}

std::vector<MiniSQLParser::ExpressionContext *> MiniSQLParser::WhenClauseContext::expression() {
  return getRuleContexts<MiniSQLParser::ExpressionContext>();
}

MiniSQLParser::ExpressionContext* MiniSQLParser::WhenClauseContext::expression(size_t i) {
  return getRuleContext<MiniSQLParser::ExpressionContext>(i);
}

tree::TerminalNode* MiniSQLParser::WhenClauseContext::THEN() {
  return getToken(MiniSQLParser::THEN, 0);
}


size_t MiniSQLParser::WhenClauseContext::getRuleIndex() const {
  return MiniSQLParser::RuleWhenClause;
}

void MiniSQLParser::WhenClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhenClause(this);
}

void MiniSQLParser::WhenClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhenClause(this);
}

MiniSQLParser::WhenClauseContext* MiniSQLParser::whenClause() {
  WhenClauseContext *_localctx = _tracker.createInstance<WhenClauseContext>(_ctx, getState());
  enterRule(_localctx, 76, MiniSQLParser::RuleWhenClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(453);
    match(MiniSQLParser::WHEN);
    setState(454);
    expression();
    setState(455);
    match(MiniSQLParser::THEN);
    setState(456);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InExpressionContext ------------------------------------------------------------------

MiniSQLParser::InExpressionContext::InExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniSQLParser::ExpressionListContext* MiniSQLParser::InExpressionContext::expressionList() {
  return getRuleContext<MiniSQLParser::ExpressionListContext>(0);
}

MiniSQLParser::QueryExpressionContext* MiniSQLParser::InExpressionContext::queryExpression() {
  return getRuleContext<MiniSQLParser::QueryExpressionContext>(0);
}


size_t MiniSQLParser::InExpressionContext::getRuleIndex() const {
  return MiniSQLParser::RuleInExpression;
}

void MiniSQLParser::InExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInExpression(this);
}

void MiniSQLParser::InExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInExpression(this);
}

MiniSQLParser::InExpressionContext* MiniSQLParser::inExpression() {
  InExpressionContext *_localctx = _tracker.createInstance<InExpressionContext>(_ctx, getState());
  enterRule(_localctx, 78, MiniSQLParser::RuleInExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(460);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(458);
      expressionList();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(459);
      queryExpression();
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

//----------------- ExpressionListContext ------------------------------------------------------------------

MiniSQLParser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniSQLParser::ExpressionContext *> MiniSQLParser::ExpressionListContext::expression() {
  return getRuleContexts<MiniSQLParser::ExpressionContext>();
}

MiniSQLParser::ExpressionContext* MiniSQLParser::ExpressionListContext::expression(size_t i) {
  return getRuleContext<MiniSQLParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> MiniSQLParser::ExpressionListContext::COMMA() {
  return getTokens(MiniSQLParser::COMMA);
}

tree::TerminalNode* MiniSQLParser::ExpressionListContext::COMMA(size_t i) {
  return getToken(MiniSQLParser::COMMA, i);
}


size_t MiniSQLParser::ExpressionListContext::getRuleIndex() const {
  return MiniSQLParser::RuleExpressionList;
}

void MiniSQLParser::ExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionList(this);
}

void MiniSQLParser::ExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionList(this);
}

MiniSQLParser::ExpressionListContext* MiniSQLParser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 80, MiniSQLParser::RuleExpressionList);
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
    setState(462);
    expression();
    setState(467);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniSQLParser::COMMA) {
      setState(463);
      match(MiniSQLParser::COMMA);
      setState(464);
      expression();
      setState(469);
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

//----------------- LiteralContext ------------------------------------------------------------------

MiniSQLParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::LiteralContext::NUMBER() {
  return getToken(MiniSQLParser::NUMBER, 0);
}

tree::TerminalNode* MiniSQLParser::LiteralContext::STRING() {
  return getToken(MiniSQLParser::STRING, 0);
}

tree::TerminalNode* MiniSQLParser::LiteralContext::NULL_() {
  return getToken(MiniSQLParser::NULL_, 0);
}

tree::TerminalNode* MiniSQLParser::LiteralContext::TRUE() {
  return getToken(MiniSQLParser::TRUE, 0);
}

tree::TerminalNode* MiniSQLParser::LiteralContext::FALSE() {
  return getToken(MiniSQLParser::FALSE, 0);
}


size_t MiniSQLParser::LiteralContext::getRuleIndex() const {
  return MiniSQLParser::RuleLiteral;
}

void MiniSQLParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void MiniSQLParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}

MiniSQLParser::LiteralContext* MiniSQLParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 82, MiniSQLParser::RuleLiteral);
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
    setState(470);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 864691188584677376) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

MiniSQLParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniSQLParser::IdentifierContext::IDENTIFIER() {
  return getToken(MiniSQLParser::IDENTIFIER, 0);
}

tree::TerminalNode* MiniSQLParser::IdentifierContext::QUOTED_IDENTIFIER() {
  return getToken(MiniSQLParser::QUOTED_IDENTIFIER, 0);
}


size_t MiniSQLParser::IdentifierContext::getRuleIndex() const {
  return MiniSQLParser::RuleIdentifier;
}

void MiniSQLParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void MiniSQLParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MiniSQLListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

MiniSQLParser::IdentifierContext* MiniSQLParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 84, MiniSQLParser::RuleIdentifier);
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
    setState(472);
    _la = _input->LA(1);
    if (!(_la == MiniSQLParser::QUOTED_IDENTIFIER

    || _la == MiniSQLParser::IDENTIFIER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void MiniSQLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  minisqlParserInitialize();
#else
  ::antlr4::internal::call_once(minisqlParserOnceFlag, minisqlParserInitialize);
#endif
}
