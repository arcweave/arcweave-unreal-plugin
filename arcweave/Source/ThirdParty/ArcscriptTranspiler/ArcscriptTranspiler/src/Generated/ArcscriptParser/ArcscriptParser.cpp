
// Generated from ArcscriptParser.g4 by ANTLR 4.13.1


#include "ArcscriptParserVisitor.h"

#include "ArcscriptParser.h"

#include "ArcscriptParserBase.h"

using namespace antlrcpp;
using namespace Arcweave;

using namespace antlr4;

namespace {

struct ArcscriptParserStaticData final {
  ArcscriptParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ArcscriptParserStaticData(const ArcscriptParserStaticData&) = delete;
  ArcscriptParserStaticData(ArcscriptParserStaticData&&) = delete;
  ArcscriptParserStaticData& operator=(const ArcscriptParserStaticData&) = delete;
  ArcscriptParserStaticData& operator=(ArcscriptParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag arcscriptparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ArcscriptParserStaticData *arcscriptparserParserStaticData = nullptr;

void arcscriptparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (arcscriptparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(arcscriptparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ArcscriptParserStaticData>(
    std::vector<std::string>{
      "input", "script", "script_section", "blockquote", "paragraph", "paragraph_start", 
      "codestart", "codeend", "assignment_segment", "function_call_segment", 
      "conditional_section", "if_section", "else_if_section", "else_section", 
      "if_clause", "else_if_clause", "endif_segment", "statement_assignment", 
      "statement_function_call", "argument_list", "argument", "mention", 
      "mention_attributes", "additive_numeric_expression", "multiplicative_numeric_expression", 
      "signed_unary_numeric_expression", "unary_numeric_expression", "function_call", 
      "void_function_call", "sign", "variable_list", "compound_condition_or", 
      "compound_condition_and", "negated_unary_condition", "unary_condition", 
      "condition", "conditional_operator", "expression"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "'</blockquote>'", "", "'</code></pre>'", 
      "'<span'", "", "", "", "'('", "')'", "'*='", "'/='", "'+='", "'-='", 
      "'*'", "'/'", "'+'", "'-'", "", "", "", "", "'=='", "'!='", "", "'||'", 
      "", "'!'", "','", "'{'", "'}'", "", "", "'show'", "", "'if'", "'else'", 
      "'elseif'", "'endif'", "'and'", "'or'", "'is'", "'not'", "", "", "", 
      "'>'", "", "", "'/span>'", "", "'<'"
    },
    std::vector<std::string>{
      "", "CODESTART", "PARAGRAPHSTART", "BLOCKQUOTESTART", "NORMAL_WHITESPACE", 
      "PARAGRAPHEND", "BQ_CODESTART", "BQ_PARAGRAPHSTART", "BLOCKQUOTEEND", 
      "BQ_WHITESPACE", "CODEEND", "MENTION_TAG_OPEN", "FLOAT", "INTEGER", 
      "DIGIT", "LPAREN", "RPAREN", "ASSIGNMUL", "ASSIGNDIV", "ASSIGNADD", 
      "ASSIGNSUB", "MUL", "DIV", "ADD", "SUB", "GE", "GT", "LE", "LT", "EQ", 
      "NE", "AND", "OR", "ASSIGN", "NEG", "COMMA", "LBRACE", "RBRACE", "BOOLEAN", 
      "FNAME", "VFNAME", "VFNAMEVARS", "IFKEYWORD", "ELSEKEYWORD", "ELSEIFKEYWORD", 
      "ENDIFKEYWORD", "ANDKEYWORD", "ORKEYWORD", "ISKEYWORD", "NOTKEYWORD", 
      "STRING", "VARIABLE", "WHITESPACE", "TAG_CLOSE", "ATTR_NAME", "TAG_EQUALS", 
      "MENTION_TAG_CLOSE", "TAG_WHITESPACE", "TAG_OPEN", "MENTION_LABEL", 
      "ATTR_VALUE", "ATTRIBUTE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,61,337,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,3,0,85,8,0,1,1,
  	4,1,88,8,1,11,1,12,1,89,1,2,4,2,93,8,2,11,2,12,2,94,1,2,4,2,98,8,2,11,
  	2,12,2,99,1,2,1,2,1,2,3,2,105,8,2,1,3,1,3,1,3,1,3,5,3,111,8,3,10,3,12,
  	3,114,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,3,5,126,8,5,1,6,1,6,
  	1,6,1,6,3,6,132,8,6,1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,1,10,1,10,
  	5,10,146,8,10,10,10,12,10,149,9,10,1,10,3,10,152,8,10,1,10,1,10,1,11,
  	1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,
  	1,14,1,14,1,14,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,
  	1,17,1,18,1,18,1,19,1,19,1,19,5,19,191,8,19,10,19,12,19,194,9,19,1,20,
  	1,20,1,20,3,20,199,8,20,1,21,1,21,5,21,203,8,21,10,21,12,21,206,9,21,
  	1,21,1,21,3,21,210,8,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,3,22,219,8,
  	22,1,23,1,23,1,23,1,23,1,23,1,23,5,23,227,8,23,10,23,12,23,230,9,23,1,
  	24,1,24,1,24,1,24,1,24,1,24,5,24,238,8,24,10,24,12,24,241,9,24,1,25,1,
  	25,1,25,1,25,3,25,247,8,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,
  	26,1,26,1,26,3,26,260,8,26,1,27,1,27,1,27,3,27,265,8,27,1,27,1,27,1,27,
  	1,28,1,28,1,28,3,28,273,8,28,1,28,1,28,1,28,1,28,1,28,3,28,280,8,28,1,
  	28,1,28,3,28,284,8,28,1,29,1,29,1,30,1,30,1,30,5,30,291,8,30,10,30,12,
  	30,294,9,30,1,30,1,30,1,31,1,31,1,31,3,31,301,8,31,1,32,1,32,1,32,3,32,
  	306,8,32,1,33,3,33,309,8,33,1,33,1,33,1,34,1,34,1,35,1,35,1,35,1,35,3,
  	35,319,8,35,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,330,8,36,
  	1,37,1,37,1,37,3,37,335,8,37,1,37,2,94,99,2,46,48,38,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,64,66,68,70,72,74,0,6,2,0,17,20,33,33,1,0,23,24,1,0,21,22,2,0,32,
  	32,47,47,2,0,31,31,46,46,2,0,34,34,49,49,346,0,84,1,0,0,0,2,87,1,0,0,
  	0,4,104,1,0,0,0,6,106,1,0,0,0,8,117,1,0,0,0,10,125,1,0,0,0,12,131,1,0,
  	0,0,14,133,1,0,0,0,16,135,1,0,0,0,18,139,1,0,0,0,20,143,1,0,0,0,22,155,
  	1,0,0,0,24,160,1,0,0,0,26,165,1,0,0,0,28,170,1,0,0,0,30,173,1,0,0,0,32,
  	176,1,0,0,0,34,180,1,0,0,0,36,185,1,0,0,0,38,187,1,0,0,0,40,198,1,0,0,
  	0,42,200,1,0,0,0,44,215,1,0,0,0,46,220,1,0,0,0,48,231,1,0,0,0,50,246,
  	1,0,0,0,52,259,1,0,0,0,54,261,1,0,0,0,56,283,1,0,0,0,58,285,1,0,0,0,60,
  	287,1,0,0,0,62,297,1,0,0,0,64,302,1,0,0,0,66,308,1,0,0,0,68,312,1,0,0,
  	0,70,314,1,0,0,0,72,329,1,0,0,0,74,334,1,0,0,0,76,77,3,2,1,0,77,78,5,
  	0,0,1,78,85,1,0,0,0,79,80,3,12,6,0,80,81,3,62,31,0,81,82,3,14,7,0,82,
  	83,5,0,0,1,83,85,1,0,0,0,84,76,1,0,0,0,84,79,1,0,0,0,85,1,1,0,0,0,86,
  	88,3,4,2,0,87,86,1,0,0,0,88,89,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,
  	3,1,0,0,0,91,93,3,6,3,0,92,91,1,0,0,0,93,94,1,0,0,0,94,95,1,0,0,0,94,
  	92,1,0,0,0,95,105,1,0,0,0,96,98,3,8,4,0,97,96,1,0,0,0,98,99,1,0,0,0,99,
  	100,1,0,0,0,99,97,1,0,0,0,100,105,1,0,0,0,101,105,3,16,8,0,102,105,3,
  	18,9,0,103,105,3,20,10,0,104,92,1,0,0,0,104,97,1,0,0,0,104,101,1,0,0,
  	0,104,102,1,0,0,0,104,103,1,0,0,0,105,5,1,0,0,0,106,112,5,3,0,0,107,111,
  	3,8,4,0,108,111,3,16,8,0,109,111,3,18,9,0,110,107,1,0,0,0,110,108,1,0,
  	0,0,110,109,1,0,0,0,111,114,1,0,0,0,112,110,1,0,0,0,112,113,1,0,0,0,113,
  	115,1,0,0,0,114,112,1,0,0,0,115,116,5,8,0,0,116,7,1,0,0,0,117,118,3,10,
  	5,0,118,119,5,5,0,0,119,120,6,4,-1,0,120,9,1,0,0,0,121,122,5,2,0,0,122,
  	126,6,5,-1,0,123,124,5,7,0,0,124,126,6,5,-1,0,125,121,1,0,0,0,125,123,
  	1,0,0,0,126,11,1,0,0,0,127,128,5,1,0,0,128,132,6,6,-1,0,129,130,5,6,0,
  	0,130,132,6,6,-1,0,131,127,1,0,0,0,131,129,1,0,0,0,132,13,1,0,0,0,133,
  	134,5,10,0,0,134,15,1,0,0,0,135,136,3,12,6,0,136,137,3,34,17,0,137,138,
  	3,14,7,0,138,17,1,0,0,0,139,140,3,12,6,0,140,141,3,36,18,0,141,142,3,
  	14,7,0,142,19,1,0,0,0,143,147,3,22,11,0,144,146,3,24,12,0,145,144,1,0,
  	0,0,146,149,1,0,0,0,147,145,1,0,0,0,147,148,1,0,0,0,148,151,1,0,0,0,149,
  	147,1,0,0,0,150,152,3,26,13,0,151,150,1,0,0,0,151,152,1,0,0,0,152,153,
  	1,0,0,0,153,154,3,32,16,0,154,21,1,0,0,0,155,156,3,12,6,0,156,157,3,28,
  	14,0,157,158,3,14,7,0,158,159,3,2,1,0,159,23,1,0,0,0,160,161,3,12,6,0,
  	161,162,3,30,15,0,162,163,3,14,7,0,163,164,3,2,1,0,164,25,1,0,0,0,165,
  	166,3,12,6,0,166,167,5,43,0,0,167,168,3,14,7,0,168,169,3,2,1,0,169,27,
  	1,0,0,0,170,171,5,42,0,0,171,172,3,62,31,0,172,29,1,0,0,0,173,174,5,44,
  	0,0,174,175,3,62,31,0,175,31,1,0,0,0,176,177,3,12,6,0,177,178,5,45,0,
  	0,178,179,3,14,7,0,179,33,1,0,0,0,180,181,5,51,0,0,181,182,7,0,0,0,182,
  	183,3,62,31,0,183,184,6,17,-1,0,184,35,1,0,0,0,185,186,3,56,28,0,186,
  	37,1,0,0,0,187,192,3,40,20,0,188,189,5,35,0,0,189,191,3,40,20,0,190,188,
  	1,0,0,0,191,194,1,0,0,0,192,190,1,0,0,0,192,193,1,0,0,0,193,39,1,0,0,
  	0,194,192,1,0,0,0,195,199,3,46,23,0,196,199,5,50,0,0,197,199,3,42,21,
  	0,198,195,1,0,0,0,198,196,1,0,0,0,198,197,1,0,0,0,199,41,1,0,0,0,200,
  	204,5,11,0,0,201,203,3,44,22,0,202,201,1,0,0,0,203,206,1,0,0,0,204,202,
  	1,0,0,0,204,205,1,0,0,0,205,207,1,0,0,0,206,204,1,0,0,0,207,209,5,53,
  	0,0,208,210,5,59,0,0,209,208,1,0,0,0,209,210,1,0,0,0,210,211,1,0,0,0,
  	211,212,5,58,0,0,212,213,5,56,0,0,213,214,4,21,0,1,214,43,1,0,0,0,215,
  	218,5,54,0,0,216,217,5,55,0,0,217,219,5,60,0,0,218,216,1,0,0,0,218,219,
  	1,0,0,0,219,45,1,0,0,0,220,221,6,23,-1,0,221,222,3,48,24,0,222,228,1,
  	0,0,0,223,224,10,1,0,0,224,225,7,1,0,0,225,227,3,48,24,0,226,223,1,0,
  	0,0,227,230,1,0,0,0,228,226,1,0,0,0,228,229,1,0,0,0,229,47,1,0,0,0,230,
  	228,1,0,0,0,231,232,6,24,-1,0,232,233,3,50,25,0,233,239,1,0,0,0,234,235,
  	10,1,0,0,235,236,7,2,0,0,236,238,3,50,25,0,237,234,1,0,0,0,238,241,1,
  	0,0,0,239,237,1,0,0,0,239,240,1,0,0,0,240,49,1,0,0,0,241,239,1,0,0,0,
  	242,243,3,58,29,0,243,244,3,52,26,0,244,247,1,0,0,0,245,247,3,52,26,0,
  	246,242,1,0,0,0,246,245,1,0,0,0,247,51,1,0,0,0,248,260,5,12,0,0,249,250,
  	5,51,0,0,250,260,6,26,-1,0,251,260,5,13,0,0,252,260,5,50,0,0,253,260,
  	5,38,0,0,254,260,3,54,27,0,255,256,5,15,0,0,256,257,3,62,31,0,257,258,
  	5,16,0,0,258,260,1,0,0,0,259,248,1,0,0,0,259,249,1,0,0,0,259,251,1,0,
  	0,0,259,252,1,0,0,0,259,253,1,0,0,0,259,254,1,0,0,0,259,255,1,0,0,0,260,
  	53,1,0,0,0,261,262,5,39,0,0,262,264,5,15,0,0,263,265,3,38,19,0,264,263,
  	1,0,0,0,264,265,1,0,0,0,265,266,1,0,0,0,266,267,5,16,0,0,267,268,6,27,
  	-1,0,268,55,1,0,0,0,269,270,5,40,0,0,270,272,5,15,0,0,271,273,3,38,19,
  	0,272,271,1,0,0,0,272,273,1,0,0,0,273,274,1,0,0,0,274,275,5,16,0,0,275,
  	284,6,28,-1,0,276,277,5,41,0,0,277,279,5,15,0,0,278,280,3,60,30,0,279,
  	278,1,0,0,0,279,280,1,0,0,0,280,281,1,0,0,0,281,282,5,16,0,0,282,284,
  	6,28,-1,0,283,269,1,0,0,0,283,276,1,0,0,0,284,57,1,0,0,0,285,286,7,1,
  	0,0,286,59,1,0,0,0,287,292,5,51,0,0,288,289,5,35,0,0,289,291,5,51,0,0,
  	290,288,1,0,0,0,291,294,1,0,0,0,292,290,1,0,0,0,292,293,1,0,0,0,293,295,
  	1,0,0,0,294,292,1,0,0,0,295,296,6,30,-1,0,296,61,1,0,0,0,297,300,3,64,
  	32,0,298,299,7,3,0,0,299,301,3,62,31,0,300,298,1,0,0,0,300,301,1,0,0,
  	0,301,63,1,0,0,0,302,305,3,66,33,0,303,304,7,4,0,0,304,306,3,64,32,0,
  	305,303,1,0,0,0,305,306,1,0,0,0,306,65,1,0,0,0,307,309,7,5,0,0,308,307,
  	1,0,0,0,308,309,1,0,0,0,309,310,1,0,0,0,310,311,3,68,34,0,311,67,1,0,
  	0,0,312,313,3,70,35,0,313,69,1,0,0,0,314,318,3,74,37,0,315,316,3,72,36,
  	0,316,317,3,74,37,0,317,319,1,0,0,0,318,315,1,0,0,0,318,319,1,0,0,0,319,
  	71,1,0,0,0,320,330,5,26,0,0,321,330,5,25,0,0,322,330,5,28,0,0,323,330,
  	5,27,0,0,324,330,5,29,0,0,325,330,5,30,0,0,326,330,5,48,0,0,327,328,5,
  	48,0,0,328,330,5,49,0,0,329,320,1,0,0,0,329,321,1,0,0,0,329,322,1,0,0,
  	0,329,323,1,0,0,0,329,324,1,0,0,0,329,325,1,0,0,0,329,326,1,0,0,0,329,
  	327,1,0,0,0,330,73,1,0,0,0,331,335,5,50,0,0,332,335,5,38,0,0,333,335,
  	3,46,23,0,334,331,1,0,0,0,334,332,1,0,0,0,334,333,1,0,0,0,335,75,1,0,
  	0,0,31,84,89,94,99,104,110,112,125,131,147,151,192,198,204,209,218,228,
  	239,246,259,264,272,279,283,292,300,305,308,318,329,334
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  arcscriptparserParserStaticData = staticData.release();
}

}

ArcscriptParser::ArcscriptParser(TokenStream *input) : ArcscriptParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ArcscriptParser::ArcscriptParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : ArcscriptParserBase(input) {
  ArcscriptParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *arcscriptparserParserStaticData->atn, arcscriptparserParserStaticData->decisionToDFA, arcscriptparserParserStaticData->sharedContextCache, options);
}

ArcscriptParser::~ArcscriptParser() {
  delete _interpreter;
}

const atn::ATN& ArcscriptParser::getATN() const {
  return *arcscriptparserParserStaticData->atn;
}

std::string ArcscriptParser::getGrammarFileName() const {
  return "ArcscriptParser.g4";
}

const std::vector<std::string>& ArcscriptParser::getRuleNames() const {
  return arcscriptparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& ArcscriptParser::getVocabulary() const {
  return arcscriptparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ArcscriptParser::getSerializedATN() const {
  return arcscriptparserParserStaticData->serializedATN;
}


//----------------- InputContext ------------------------------------------------------------------

ArcscriptParser::InputContext::InputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::ScriptContext* ArcscriptParser::InputContext::script() {
  return getRuleContext<ArcscriptParser::ScriptContext>(0);
}

tree::TerminalNode* ArcscriptParser::InputContext::EOF() {
  return getToken(ArcscriptParser::EOF, 0);
}

ArcscriptParser::CodestartContext* ArcscriptParser::InputContext::codestart() {
  return getRuleContext<ArcscriptParser::CodestartContext>(0);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::InputContext::compound_condition_or() {
  return getRuleContext<ArcscriptParser::Compound_condition_orContext>(0);
}

ArcscriptParser::CodeendContext* ArcscriptParser::InputContext::codeend() {
  return getRuleContext<ArcscriptParser::CodeendContext>(0);
}


size_t ArcscriptParser::InputContext::getRuleIndex() const {
  return ArcscriptParser::RuleInput;
}


std::any ArcscriptParser::InputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitInput(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::InputContext* ArcscriptParser::input() {
  InputContext *_localctx = _tracker.createInstance<InputContext>(_ctx, getState());
  enterRule(_localctx, 0, ArcscriptParser::RuleInput);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(76);
      script();
      setState(77);
      match(ArcscriptParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(79);
      codestart();
      setState(80);
      compound_condition_or();
      setState(81);
      codeend();
      setState(82);
      match(ArcscriptParser::EOF);
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

//----------------- ScriptContext ------------------------------------------------------------------

ArcscriptParser::ScriptContext::ScriptContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ArcscriptParser::Script_sectionContext *> ArcscriptParser::ScriptContext::script_section() {
  return getRuleContexts<ArcscriptParser::Script_sectionContext>();
}

ArcscriptParser::Script_sectionContext* ArcscriptParser::ScriptContext::script_section(size_t i) {
  return getRuleContext<ArcscriptParser::Script_sectionContext>(i);
}


size_t ArcscriptParser::ScriptContext::getRuleIndex() const {
  return ArcscriptParser::RuleScript;
}


std::any ArcscriptParser::ScriptContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitScript(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::ScriptContext* ArcscriptParser::script() {
  ScriptContext *_localctx = _tracker.createInstance<ScriptContext>(_ctx, getState());
  enterRule(_localctx, 2, ArcscriptParser::RuleScript);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(87); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(86);
              script_section();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(89); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Script_sectionContext ------------------------------------------------------------------

ArcscriptParser::Script_sectionContext::Script_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ArcscriptParser::BlockquoteContext *> ArcscriptParser::Script_sectionContext::blockquote() {
  return getRuleContexts<ArcscriptParser::BlockquoteContext>();
}

ArcscriptParser::BlockquoteContext* ArcscriptParser::Script_sectionContext::blockquote(size_t i) {
  return getRuleContext<ArcscriptParser::BlockquoteContext>(i);
}

std::vector<ArcscriptParser::ParagraphContext *> ArcscriptParser::Script_sectionContext::paragraph() {
  return getRuleContexts<ArcscriptParser::ParagraphContext>();
}

ArcscriptParser::ParagraphContext* ArcscriptParser::Script_sectionContext::paragraph(size_t i) {
  return getRuleContext<ArcscriptParser::ParagraphContext>(i);
}

ArcscriptParser::Assignment_segmentContext* ArcscriptParser::Script_sectionContext::assignment_segment() {
  return getRuleContext<ArcscriptParser::Assignment_segmentContext>(0);
}

ArcscriptParser::Function_call_segmentContext* ArcscriptParser::Script_sectionContext::function_call_segment() {
  return getRuleContext<ArcscriptParser::Function_call_segmentContext>(0);
}

ArcscriptParser::Conditional_sectionContext* ArcscriptParser::Script_sectionContext::conditional_section() {
  return getRuleContext<ArcscriptParser::Conditional_sectionContext>(0);
}


size_t ArcscriptParser::Script_sectionContext::getRuleIndex() const {
  return ArcscriptParser::RuleScript_section;
}


std::any ArcscriptParser::Script_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitScript_section(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Script_sectionContext* ArcscriptParser::script_section() {
  Script_sectionContext *_localctx = _tracker.createInstance<Script_sectionContext>(_ctx, getState());
  enterRule(_localctx, 4, ArcscriptParser::RuleScript_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(104);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(92); 
      _errHandler->sync(this);
      alt = 1 + 1;
      do {
        switch (alt) {
          case 1 + 1: {
                setState(91);
                blockquote();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(94); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      } while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(97); 
      _errHandler->sync(this);
      alt = 1 + 1;
      do {
        switch (alt) {
          case 1 + 1: {
                setState(96);
                paragraph();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(99); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
      } while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(101);
      assignment_segment();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(102);
      function_call_segment();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(103);
      conditional_section();
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

//----------------- BlockquoteContext ------------------------------------------------------------------

ArcscriptParser::BlockquoteContext::BlockquoteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::BlockquoteContext::BLOCKQUOTESTART() {
  return getToken(ArcscriptParser::BLOCKQUOTESTART, 0);
}

tree::TerminalNode* ArcscriptParser::BlockquoteContext::BLOCKQUOTEEND() {
  return getToken(ArcscriptParser::BLOCKQUOTEEND, 0);
}

std::vector<ArcscriptParser::ParagraphContext *> ArcscriptParser::BlockquoteContext::paragraph() {
  return getRuleContexts<ArcscriptParser::ParagraphContext>();
}

ArcscriptParser::ParagraphContext* ArcscriptParser::BlockquoteContext::paragraph(size_t i) {
  return getRuleContext<ArcscriptParser::ParagraphContext>(i);
}

std::vector<ArcscriptParser::Assignment_segmentContext *> ArcscriptParser::BlockquoteContext::assignment_segment() {
  return getRuleContexts<ArcscriptParser::Assignment_segmentContext>();
}

ArcscriptParser::Assignment_segmentContext* ArcscriptParser::BlockquoteContext::assignment_segment(size_t i) {
  return getRuleContext<ArcscriptParser::Assignment_segmentContext>(i);
}

std::vector<ArcscriptParser::Function_call_segmentContext *> ArcscriptParser::BlockquoteContext::function_call_segment() {
  return getRuleContexts<ArcscriptParser::Function_call_segmentContext>();
}

ArcscriptParser::Function_call_segmentContext* ArcscriptParser::BlockquoteContext::function_call_segment(size_t i) {
  return getRuleContext<ArcscriptParser::Function_call_segmentContext>(i);
}


size_t ArcscriptParser::BlockquoteContext::getRuleIndex() const {
  return ArcscriptParser::RuleBlockquote;
}


std::any ArcscriptParser::BlockquoteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitBlockquote(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::BlockquoteContext* ArcscriptParser::blockquote() {
  BlockquoteContext *_localctx = _tracker.createInstance<BlockquoteContext>(_ctx, getState());
  enterRule(_localctx, 6, ArcscriptParser::RuleBlockquote);
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
    setState(106);
    match(ArcscriptParser::BLOCKQUOTESTART);
    setState(112);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 198) != 0)) {
      setState(110);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(107);
        paragraph();
        break;
      }

      case 2: {
        setState(108);
        assignment_segment();
        break;
      }

      case 3: {
        setState(109);
        function_call_segment();
        break;
      }

      default:
        break;
      }
      setState(114);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(115);
    match(ArcscriptParser::BLOCKQUOTEEND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParagraphContext ------------------------------------------------------------------

ArcscriptParser::ParagraphContext::ParagraphContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Paragraph_startContext* ArcscriptParser::ParagraphContext::paragraph_start() {
  return getRuleContext<ArcscriptParser::Paragraph_startContext>(0);
}

tree::TerminalNode* ArcscriptParser::ParagraphContext::PARAGRAPHEND() {
  return getToken(ArcscriptParser::PARAGRAPHEND, 0);
}


size_t ArcscriptParser::ParagraphContext::getRuleIndex() const {
  return ArcscriptParser::RuleParagraph;
}


std::any ArcscriptParser::ParagraphContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitParagraph(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::ParagraphContext* ArcscriptParser::paragraph() {
  ParagraphContext *_localctx = _tracker.createInstance<ParagraphContext>(_ctx, getState());
  enterRule(_localctx, 8, ArcscriptParser::RuleParagraph);

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
    paragraph_start();
    setState(118);
    match(ArcscriptParser::PARAGRAPHEND);
     this->currentLine++;
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Paragraph_startContext ------------------------------------------------------------------

ArcscriptParser::Paragraph_startContext::Paragraph_startContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Paragraph_startContext::PARAGRAPHSTART() {
  return getToken(ArcscriptParser::PARAGRAPHSTART, 0);
}

tree::TerminalNode* ArcscriptParser::Paragraph_startContext::BQ_PARAGRAPHSTART() {
  return getToken(ArcscriptParser::BQ_PARAGRAPHSTART, 0);
}


size_t ArcscriptParser::Paragraph_startContext::getRuleIndex() const {
  return ArcscriptParser::RuleParagraph_start;
}


std::any ArcscriptParser::Paragraph_startContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitParagraph_start(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Paragraph_startContext* ArcscriptParser::paragraph_start() {
  Paragraph_startContext *_localctx = _tracker.createInstance<Paragraph_startContext>(_ctx, getState());
  enterRule(_localctx, 10, ArcscriptParser::RuleParagraph_start);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(125);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::PARAGRAPHSTART: {
        enterOuterAlt(_localctx, 1);
        setState(121);
        antlrcpp::downCast<Paragraph_startContext *>(_localctx)->paragraphstartToken = match(ArcscriptParser::PARAGRAPHSTART);
         this->setLineStart(antlrcpp::downCast<Paragraph_startContext *>(_localctx)->paragraphstartToken); 
        break;
      }

      case ArcscriptParser::BQ_PARAGRAPHSTART: {
        enterOuterAlt(_localctx, 2);
        setState(123);
        antlrcpp::downCast<Paragraph_startContext *>(_localctx)->bq_paragraphstartToken = match(ArcscriptParser::BQ_PARAGRAPHSTART);
         this->setLineStart(antlrcpp::downCast<Paragraph_startContext *>(_localctx)->bq_paragraphstartToken); 
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

//----------------- CodestartContext ------------------------------------------------------------------

ArcscriptParser::CodestartContext::CodestartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::CodestartContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

tree::TerminalNode* ArcscriptParser::CodestartContext::BQ_CODESTART() {
  return getToken(ArcscriptParser::BQ_CODESTART, 0);
}


size_t ArcscriptParser::CodestartContext::getRuleIndex() const {
  return ArcscriptParser::RuleCodestart;
}


std::any ArcscriptParser::CodestartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitCodestart(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::CodestartContext* ArcscriptParser::codestart() {
  CodestartContext *_localctx = _tracker.createInstance<CodestartContext>(_ctx, getState());
  enterRule(_localctx, 12, ArcscriptParser::RuleCodestart);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(131);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::CODESTART: {
        enterOuterAlt(_localctx, 1);
        setState(127);
        antlrcpp::downCast<CodestartContext *>(_localctx)->codestartToken = match(ArcscriptParser::CODESTART);
         this->currentLine++; this->setLineStart(antlrcpp::downCast<CodestartContext *>(_localctx)->codestartToken);
        break;
      }

      case ArcscriptParser::BQ_CODESTART: {
        enterOuterAlt(_localctx, 2);
        setState(129);
        antlrcpp::downCast<CodestartContext *>(_localctx)->bq_codestartToken = match(ArcscriptParser::BQ_CODESTART);
         this->currentLine++; this->setLineStart(antlrcpp::downCast<CodestartContext *>(_localctx)->bq_codestartToken);
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

//----------------- CodeendContext ------------------------------------------------------------------

ArcscriptParser::CodeendContext::CodeendContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::CodeendContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
}


size_t ArcscriptParser::CodeendContext::getRuleIndex() const {
  return ArcscriptParser::RuleCodeend;
}


std::any ArcscriptParser::CodeendContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitCodeend(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::CodeendContext* ArcscriptParser::codeend() {
  CodeendContext *_localctx = _tracker.createInstance<CodeendContext>(_ctx, getState());
  enterRule(_localctx, 14, ArcscriptParser::RuleCodeend);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    match(ArcscriptParser::CODEEND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assignment_segmentContext ------------------------------------------------------------------

ArcscriptParser::Assignment_segmentContext::Assignment_segmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::CodestartContext* ArcscriptParser::Assignment_segmentContext::codestart() {
  return getRuleContext<ArcscriptParser::CodestartContext>(0);
}

ArcscriptParser::Statement_assignmentContext* ArcscriptParser::Assignment_segmentContext::statement_assignment() {
  return getRuleContext<ArcscriptParser::Statement_assignmentContext>(0);
}

ArcscriptParser::CodeendContext* ArcscriptParser::Assignment_segmentContext::codeend() {
  return getRuleContext<ArcscriptParser::CodeendContext>(0);
}


size_t ArcscriptParser::Assignment_segmentContext::getRuleIndex() const {
  return ArcscriptParser::RuleAssignment_segment;
}


std::any ArcscriptParser::Assignment_segmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitAssignment_segment(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Assignment_segmentContext* ArcscriptParser::assignment_segment() {
  Assignment_segmentContext *_localctx = _tracker.createInstance<Assignment_segmentContext>(_ctx, getState());
  enterRule(_localctx, 16, ArcscriptParser::RuleAssignment_segment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
    codestart();
    setState(136);
    statement_assignment();
    setState(137);
    codeend();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_call_segmentContext ------------------------------------------------------------------

ArcscriptParser::Function_call_segmentContext::Function_call_segmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::CodestartContext* ArcscriptParser::Function_call_segmentContext::codestart() {
  return getRuleContext<ArcscriptParser::CodestartContext>(0);
}

ArcscriptParser::Statement_function_callContext* ArcscriptParser::Function_call_segmentContext::statement_function_call() {
  return getRuleContext<ArcscriptParser::Statement_function_callContext>(0);
}

ArcscriptParser::CodeendContext* ArcscriptParser::Function_call_segmentContext::codeend() {
  return getRuleContext<ArcscriptParser::CodeendContext>(0);
}


size_t ArcscriptParser::Function_call_segmentContext::getRuleIndex() const {
  return ArcscriptParser::RuleFunction_call_segment;
}


std::any ArcscriptParser::Function_call_segmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitFunction_call_segment(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Function_call_segmentContext* ArcscriptParser::function_call_segment() {
  Function_call_segmentContext *_localctx = _tracker.createInstance<Function_call_segmentContext>(_ctx, getState());
  enterRule(_localctx, 18, ArcscriptParser::RuleFunction_call_segment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    codestart();
    setState(140);
    statement_function_call();
    setState(141);
    codeend();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Conditional_sectionContext ------------------------------------------------------------------

ArcscriptParser::Conditional_sectionContext::Conditional_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::If_sectionContext* ArcscriptParser::Conditional_sectionContext::if_section() {
  return getRuleContext<ArcscriptParser::If_sectionContext>(0);
}

ArcscriptParser::Endif_segmentContext* ArcscriptParser::Conditional_sectionContext::endif_segment() {
  return getRuleContext<ArcscriptParser::Endif_segmentContext>(0);
}

std::vector<ArcscriptParser::Else_if_sectionContext *> ArcscriptParser::Conditional_sectionContext::else_if_section() {
  return getRuleContexts<ArcscriptParser::Else_if_sectionContext>();
}

ArcscriptParser::Else_if_sectionContext* ArcscriptParser::Conditional_sectionContext::else_if_section(size_t i) {
  return getRuleContext<ArcscriptParser::Else_if_sectionContext>(i);
}

ArcscriptParser::Else_sectionContext* ArcscriptParser::Conditional_sectionContext::else_section() {
  return getRuleContext<ArcscriptParser::Else_sectionContext>(0);
}


size_t ArcscriptParser::Conditional_sectionContext::getRuleIndex() const {
  return ArcscriptParser::RuleConditional_section;
}


std::any ArcscriptParser::Conditional_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitConditional_section(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Conditional_sectionContext* ArcscriptParser::conditional_section() {
  Conditional_sectionContext *_localctx = _tracker.createInstance<Conditional_sectionContext>(_ctx, getState());
  enterRule(_localctx, 20, ArcscriptParser::RuleConditional_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(143);
    if_section();
    setState(147);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(144);
        else_if_section(); 
      }
      setState(149);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(151);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(150);
      else_section();
      break;
    }

    default:
      break;
    }
    setState(153);
    endif_segment();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_sectionContext ------------------------------------------------------------------

ArcscriptParser::If_sectionContext::If_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::CodestartContext* ArcscriptParser::If_sectionContext::codestart() {
  return getRuleContext<ArcscriptParser::CodestartContext>(0);
}

ArcscriptParser::If_clauseContext* ArcscriptParser::If_sectionContext::if_clause() {
  return getRuleContext<ArcscriptParser::If_clauseContext>(0);
}

ArcscriptParser::CodeendContext* ArcscriptParser::If_sectionContext::codeend() {
  return getRuleContext<ArcscriptParser::CodeendContext>(0);
}

ArcscriptParser::ScriptContext* ArcscriptParser::If_sectionContext::script() {
  return getRuleContext<ArcscriptParser::ScriptContext>(0);
}


size_t ArcscriptParser::If_sectionContext::getRuleIndex() const {
  return ArcscriptParser::RuleIf_section;
}


std::any ArcscriptParser::If_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitIf_section(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::If_sectionContext* ArcscriptParser::if_section() {
  If_sectionContext *_localctx = _tracker.createInstance<If_sectionContext>(_ctx, getState());
  enterRule(_localctx, 22, ArcscriptParser::RuleIf_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    codestart();
    setState(156);
    if_clause();
    setState(157);
    codeend();
    setState(158);
    script();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Else_if_sectionContext ------------------------------------------------------------------

ArcscriptParser::Else_if_sectionContext::Else_if_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::CodestartContext* ArcscriptParser::Else_if_sectionContext::codestart() {
  return getRuleContext<ArcscriptParser::CodestartContext>(0);
}

ArcscriptParser::Else_if_clauseContext* ArcscriptParser::Else_if_sectionContext::else_if_clause() {
  return getRuleContext<ArcscriptParser::Else_if_clauseContext>(0);
}

ArcscriptParser::CodeendContext* ArcscriptParser::Else_if_sectionContext::codeend() {
  return getRuleContext<ArcscriptParser::CodeendContext>(0);
}

ArcscriptParser::ScriptContext* ArcscriptParser::Else_if_sectionContext::script() {
  return getRuleContext<ArcscriptParser::ScriptContext>(0);
}


size_t ArcscriptParser::Else_if_sectionContext::getRuleIndex() const {
  return ArcscriptParser::RuleElse_if_section;
}


std::any ArcscriptParser::Else_if_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitElse_if_section(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Else_if_sectionContext* ArcscriptParser::else_if_section() {
  Else_if_sectionContext *_localctx = _tracker.createInstance<Else_if_sectionContext>(_ctx, getState());
  enterRule(_localctx, 24, ArcscriptParser::RuleElse_if_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    codestart();
    setState(161);
    else_if_clause();
    setState(162);
    codeend();
    setState(163);
    script();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Else_sectionContext ------------------------------------------------------------------

ArcscriptParser::Else_sectionContext::Else_sectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::CodestartContext* ArcscriptParser::Else_sectionContext::codestart() {
  return getRuleContext<ArcscriptParser::CodestartContext>(0);
}

tree::TerminalNode* ArcscriptParser::Else_sectionContext::ELSEKEYWORD() {
  return getToken(ArcscriptParser::ELSEKEYWORD, 0);
}

ArcscriptParser::CodeendContext* ArcscriptParser::Else_sectionContext::codeend() {
  return getRuleContext<ArcscriptParser::CodeendContext>(0);
}

ArcscriptParser::ScriptContext* ArcscriptParser::Else_sectionContext::script() {
  return getRuleContext<ArcscriptParser::ScriptContext>(0);
}


size_t ArcscriptParser::Else_sectionContext::getRuleIndex() const {
  return ArcscriptParser::RuleElse_section;
}


std::any ArcscriptParser::Else_sectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitElse_section(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Else_sectionContext* ArcscriptParser::else_section() {
  Else_sectionContext *_localctx = _tracker.createInstance<Else_sectionContext>(_ctx, getState());
  enterRule(_localctx, 26, ArcscriptParser::RuleElse_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    codestart();
    setState(166);
    match(ArcscriptParser::ELSEKEYWORD);
    setState(167);
    codeend();
    setState(168);
    script();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_clauseContext ------------------------------------------------------------------

ArcscriptParser::If_clauseContext::If_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::If_clauseContext::IFKEYWORD() {
  return getToken(ArcscriptParser::IFKEYWORD, 0);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::If_clauseContext::compound_condition_or() {
  return getRuleContext<ArcscriptParser::Compound_condition_orContext>(0);
}


size_t ArcscriptParser::If_clauseContext::getRuleIndex() const {
  return ArcscriptParser::RuleIf_clause;
}


std::any ArcscriptParser::If_clauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitIf_clause(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::If_clauseContext* ArcscriptParser::if_clause() {
  If_clauseContext *_localctx = _tracker.createInstance<If_clauseContext>(_ctx, getState());
  enterRule(_localctx, 28, ArcscriptParser::RuleIf_clause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    match(ArcscriptParser::IFKEYWORD);
    setState(171);
    compound_condition_or();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Else_if_clauseContext ------------------------------------------------------------------

ArcscriptParser::Else_if_clauseContext::Else_if_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Else_if_clauseContext::ELSEIFKEYWORD() {
  return getToken(ArcscriptParser::ELSEIFKEYWORD, 0);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::Else_if_clauseContext::compound_condition_or() {
  return getRuleContext<ArcscriptParser::Compound_condition_orContext>(0);
}


size_t ArcscriptParser::Else_if_clauseContext::getRuleIndex() const {
  return ArcscriptParser::RuleElse_if_clause;
}


std::any ArcscriptParser::Else_if_clauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitElse_if_clause(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Else_if_clauseContext* ArcscriptParser::else_if_clause() {
  Else_if_clauseContext *_localctx = _tracker.createInstance<Else_if_clauseContext>(_ctx, getState());
  enterRule(_localctx, 30, ArcscriptParser::RuleElse_if_clause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    match(ArcscriptParser::ELSEIFKEYWORD);
    setState(174);
    compound_condition_or();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Endif_segmentContext ------------------------------------------------------------------

ArcscriptParser::Endif_segmentContext::Endif_segmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::CodestartContext* ArcscriptParser::Endif_segmentContext::codestart() {
  return getRuleContext<ArcscriptParser::CodestartContext>(0);
}

tree::TerminalNode* ArcscriptParser::Endif_segmentContext::ENDIFKEYWORD() {
  return getToken(ArcscriptParser::ENDIFKEYWORD, 0);
}

ArcscriptParser::CodeendContext* ArcscriptParser::Endif_segmentContext::codeend() {
  return getRuleContext<ArcscriptParser::CodeendContext>(0);
}


size_t ArcscriptParser::Endif_segmentContext::getRuleIndex() const {
  return ArcscriptParser::RuleEndif_segment;
}


std::any ArcscriptParser::Endif_segmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitEndif_segment(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Endif_segmentContext* ArcscriptParser::endif_segment() {
  Endif_segmentContext *_localctx = _tracker.createInstance<Endif_segmentContext>(_ctx, getState());
  enterRule(_localctx, 32, ArcscriptParser::RuleEndif_segment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(176);
    codestart();
    setState(177);
    match(ArcscriptParser::ENDIFKEYWORD);
    setState(178);
    codeend();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Statement_assignmentContext ------------------------------------------------------------------

ArcscriptParser::Statement_assignmentContext::Statement_assignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Statement_assignmentContext::VARIABLE() {
  return getToken(ArcscriptParser::VARIABLE, 0);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::Statement_assignmentContext::compound_condition_or() {
  return getRuleContext<ArcscriptParser::Compound_condition_orContext>(0);
}

tree::TerminalNode* ArcscriptParser::Statement_assignmentContext::ASSIGNADD() {
  return getToken(ArcscriptParser::ASSIGNADD, 0);
}

tree::TerminalNode* ArcscriptParser::Statement_assignmentContext::ASSIGNSUB() {
  return getToken(ArcscriptParser::ASSIGNSUB, 0);
}

tree::TerminalNode* ArcscriptParser::Statement_assignmentContext::ASSIGNMUL() {
  return getToken(ArcscriptParser::ASSIGNMUL, 0);
}

tree::TerminalNode* ArcscriptParser::Statement_assignmentContext::ASSIGNDIV() {
  return getToken(ArcscriptParser::ASSIGNDIV, 0);
}

tree::TerminalNode* ArcscriptParser::Statement_assignmentContext::ASSIGN() {
  return getToken(ArcscriptParser::ASSIGN, 0);
}


size_t ArcscriptParser::Statement_assignmentContext::getRuleIndex() const {
  return ArcscriptParser::RuleStatement_assignment;
}


std::any ArcscriptParser::Statement_assignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitStatement_assignment(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Statement_assignmentContext* ArcscriptParser::statement_assignment() {
  Statement_assignmentContext *_localctx = _tracker.createInstance<Statement_assignmentContext>(_ctx, getState());
  enterRule(_localctx, 34, ArcscriptParser::RuleStatement_assignment);
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
    setState(180);
    antlrcpp::downCast<Statement_assignmentContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
    setState(181);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8591900672) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(182);
    compound_condition_or();
    this->assertVariable(antlrcpp::downCast<Statement_assignmentContext *>(_localctx)->variableToken);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Statement_function_callContext ------------------------------------------------------------------

ArcscriptParser::Statement_function_callContext::Statement_function_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Void_function_callContext* ArcscriptParser::Statement_function_callContext::void_function_call() {
  return getRuleContext<ArcscriptParser::Void_function_callContext>(0);
}


size_t ArcscriptParser::Statement_function_callContext::getRuleIndex() const {
  return ArcscriptParser::RuleStatement_function_call;
}


std::any ArcscriptParser::Statement_function_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitStatement_function_call(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Statement_function_callContext* ArcscriptParser::statement_function_call() {
  Statement_function_callContext *_localctx = _tracker.createInstance<Statement_function_callContext>(_ctx, getState());
  enterRule(_localctx, 36, ArcscriptParser::RuleStatement_function_call);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(185);
    void_function_call();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Argument_listContext ------------------------------------------------------------------

ArcscriptParser::Argument_listContext::Argument_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ArcscriptParser::ArgumentContext *> ArcscriptParser::Argument_listContext::argument() {
  return getRuleContexts<ArcscriptParser::ArgumentContext>();
}

ArcscriptParser::ArgumentContext* ArcscriptParser::Argument_listContext::argument(size_t i) {
  return getRuleContext<ArcscriptParser::ArgumentContext>(i);
}

std::vector<tree::TerminalNode *> ArcscriptParser::Argument_listContext::COMMA() {
  return getTokens(ArcscriptParser::COMMA);
}

tree::TerminalNode* ArcscriptParser::Argument_listContext::COMMA(size_t i) {
  return getToken(ArcscriptParser::COMMA, i);
}


size_t ArcscriptParser::Argument_listContext::getRuleIndex() const {
  return ArcscriptParser::RuleArgument_list;
}


std::any ArcscriptParser::Argument_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitArgument_list(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Argument_listContext* ArcscriptParser::argument_list() {
  Argument_listContext *_localctx = _tracker.createInstance<Argument_listContext>(_ctx, getState());
  enterRule(_localctx, 38, ArcscriptParser::RuleArgument_list);
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
    setState(187);
    argument();
    setState(192);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ArcscriptParser::COMMA) {
      setState(188);
      match(ArcscriptParser::COMMA);
      setState(189);
      argument();
      setState(194);
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

//----------------- ArgumentContext ------------------------------------------------------------------

ArcscriptParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Additive_numeric_expressionContext* ArcscriptParser::ArgumentContext::additive_numeric_expression() {
  return getRuleContext<ArcscriptParser::Additive_numeric_expressionContext>(0);
}

tree::TerminalNode* ArcscriptParser::ArgumentContext::STRING() {
  return getToken(ArcscriptParser::STRING, 0);
}

ArcscriptParser::MentionContext* ArcscriptParser::ArgumentContext::mention() {
  return getRuleContext<ArcscriptParser::MentionContext>(0);
}


size_t ArcscriptParser::ArgumentContext::getRuleIndex() const {
  return ArcscriptParser::RuleArgument;
}


std::any ArcscriptParser::ArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitArgument(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::ArgumentContext* ArcscriptParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 40, ArcscriptParser::RuleArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(198);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(195);
      additive_numeric_expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(196);
      match(ArcscriptParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(197);
      mention();
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

//----------------- MentionContext ------------------------------------------------------------------

ArcscriptParser::MentionContext::MentionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::MentionContext::MENTION_TAG_OPEN() {
  return getToken(ArcscriptParser::MENTION_TAG_OPEN, 0);
}

tree::TerminalNode* ArcscriptParser::MentionContext::TAG_CLOSE() {
  return getToken(ArcscriptParser::TAG_CLOSE, 0);
}

tree::TerminalNode* ArcscriptParser::MentionContext::TAG_OPEN() {
  return getToken(ArcscriptParser::TAG_OPEN, 0);
}

tree::TerminalNode* ArcscriptParser::MentionContext::MENTION_TAG_CLOSE() {
  return getToken(ArcscriptParser::MENTION_TAG_CLOSE, 0);
}

tree::TerminalNode* ArcscriptParser::MentionContext::MENTION_LABEL() {
  return getToken(ArcscriptParser::MENTION_LABEL, 0);
}

std::vector<ArcscriptParser::Mention_attributesContext *> ArcscriptParser::MentionContext::mention_attributes() {
  return getRuleContexts<ArcscriptParser::Mention_attributesContext>();
}

ArcscriptParser::Mention_attributesContext* ArcscriptParser::MentionContext::mention_attributes(size_t i) {
  return getRuleContext<ArcscriptParser::Mention_attributesContext>(i);
}


size_t ArcscriptParser::MentionContext::getRuleIndex() const {
  return ArcscriptParser::RuleMention;
}


std::any ArcscriptParser::MentionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitMention(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::MentionContext* ArcscriptParser::mention() {
  MentionContext *_localctx = _tracker.createInstance<MentionContext>(_ctx, getState());
  enterRule(_localctx, 42, ArcscriptParser::RuleMention);
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
    setState(200);
    match(ArcscriptParser::MENTION_TAG_OPEN);
    setState(204);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ArcscriptParser::ATTR_NAME) {
      setState(201);
      antlrcpp::downCast<MentionContext *>(_localctx)->mention_attributesContext = mention_attributes();
      antlrcpp::downCast<MentionContext *>(_localctx)->attr.push_back(antlrcpp::downCast<MentionContext *>(_localctx)->mention_attributesContext);
      setState(206);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(207);
    match(ArcscriptParser::TAG_CLOSE);
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::MENTION_LABEL) {
      setState(208);
      match(ArcscriptParser::MENTION_LABEL);
    }
    setState(211);
    match(ArcscriptParser::TAG_OPEN);
    setState(212);
    match(ArcscriptParser::MENTION_TAG_CLOSE);
    setState(213);

    if (!(this->assertMention(antlrcpp::downCast<MentionContext *>(_localctx)->attr)
    		)) throw FailedPredicateException(this, "this->assertMention($attr)\n\t\t");
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mention_attributesContext ------------------------------------------------------------------

ArcscriptParser::Mention_attributesContext::Mention_attributesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Mention_attributesContext::ATTR_NAME() {
  return getToken(ArcscriptParser::ATTR_NAME, 0);
}

tree::TerminalNode* ArcscriptParser::Mention_attributesContext::TAG_EQUALS() {
  return getToken(ArcscriptParser::TAG_EQUALS, 0);
}

tree::TerminalNode* ArcscriptParser::Mention_attributesContext::ATTR_VALUE() {
  return getToken(ArcscriptParser::ATTR_VALUE, 0);
}


size_t ArcscriptParser::Mention_attributesContext::getRuleIndex() const {
  return ArcscriptParser::RuleMention_attributes;
}


std::any ArcscriptParser::Mention_attributesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitMention_attributes(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Mention_attributesContext* ArcscriptParser::mention_attributes() {
  Mention_attributesContext *_localctx = _tracker.createInstance<Mention_attributesContext>(_ctx, getState());
  enterRule(_localctx, 44, ArcscriptParser::RuleMention_attributes);
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
    setState(215);
    match(ArcscriptParser::ATTR_NAME);
    setState(218);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::TAG_EQUALS) {
      setState(216);
      match(ArcscriptParser::TAG_EQUALS);
      setState(217);
      match(ArcscriptParser::ATTR_VALUE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Additive_numeric_expressionContext ------------------------------------------------------------------

ArcscriptParser::Additive_numeric_expressionContext::Additive_numeric_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Multiplicative_numeric_expressionContext* ArcscriptParser::Additive_numeric_expressionContext::multiplicative_numeric_expression() {
  return getRuleContext<ArcscriptParser::Multiplicative_numeric_expressionContext>(0);
}

ArcscriptParser::Additive_numeric_expressionContext* ArcscriptParser::Additive_numeric_expressionContext::additive_numeric_expression() {
  return getRuleContext<ArcscriptParser::Additive_numeric_expressionContext>(0);
}

tree::TerminalNode* ArcscriptParser::Additive_numeric_expressionContext::ADD() {
  return getToken(ArcscriptParser::ADD, 0);
}

tree::TerminalNode* ArcscriptParser::Additive_numeric_expressionContext::SUB() {
  return getToken(ArcscriptParser::SUB, 0);
}


size_t ArcscriptParser::Additive_numeric_expressionContext::getRuleIndex() const {
  return ArcscriptParser::RuleAdditive_numeric_expression;
}


std::any ArcscriptParser::Additive_numeric_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitAdditive_numeric_expression(this);
  else
    return visitor->visitChildren(this);
}


ArcscriptParser::Additive_numeric_expressionContext* ArcscriptParser::additive_numeric_expression() {
   return additive_numeric_expression(0);
}

ArcscriptParser::Additive_numeric_expressionContext* ArcscriptParser::additive_numeric_expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ArcscriptParser::Additive_numeric_expressionContext *_localctx = _tracker.createInstance<Additive_numeric_expressionContext>(_ctx, parentState);
  ArcscriptParser::Additive_numeric_expressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, ArcscriptParser::RuleAdditive_numeric_expression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(221);
    multiplicative_numeric_expression(0);
    _ctx->stop = _input->LT(-1);
    setState(228);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Additive_numeric_expressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAdditive_numeric_expression);
        setState(223);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(224);
        _la = _input->LA(1);
        if (!(_la == ArcscriptParser::ADD

        || _la == ArcscriptParser::SUB)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(225);
        multiplicative_numeric_expression(0); 
      }
      setState(230);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Multiplicative_numeric_expressionContext ------------------------------------------------------------------

ArcscriptParser::Multiplicative_numeric_expressionContext::Multiplicative_numeric_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Signed_unary_numeric_expressionContext* ArcscriptParser::Multiplicative_numeric_expressionContext::signed_unary_numeric_expression() {
  return getRuleContext<ArcscriptParser::Signed_unary_numeric_expressionContext>(0);
}

ArcscriptParser::Multiplicative_numeric_expressionContext* ArcscriptParser::Multiplicative_numeric_expressionContext::multiplicative_numeric_expression() {
  return getRuleContext<ArcscriptParser::Multiplicative_numeric_expressionContext>(0);
}

tree::TerminalNode* ArcscriptParser::Multiplicative_numeric_expressionContext::MUL() {
  return getToken(ArcscriptParser::MUL, 0);
}

tree::TerminalNode* ArcscriptParser::Multiplicative_numeric_expressionContext::DIV() {
  return getToken(ArcscriptParser::DIV, 0);
}


size_t ArcscriptParser::Multiplicative_numeric_expressionContext::getRuleIndex() const {
  return ArcscriptParser::RuleMultiplicative_numeric_expression;
}


std::any ArcscriptParser::Multiplicative_numeric_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitMultiplicative_numeric_expression(this);
  else
    return visitor->visitChildren(this);
}


ArcscriptParser::Multiplicative_numeric_expressionContext* ArcscriptParser::multiplicative_numeric_expression() {
   return multiplicative_numeric_expression(0);
}

ArcscriptParser::Multiplicative_numeric_expressionContext* ArcscriptParser::multiplicative_numeric_expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ArcscriptParser::Multiplicative_numeric_expressionContext *_localctx = _tracker.createInstance<Multiplicative_numeric_expressionContext>(_ctx, parentState);
  ArcscriptParser::Multiplicative_numeric_expressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, ArcscriptParser::RuleMultiplicative_numeric_expression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(232);
    signed_unary_numeric_expression();
    _ctx->stop = _input->LT(-1);
    setState(239);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Multiplicative_numeric_expressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleMultiplicative_numeric_expression);
        setState(234);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(235);
        _la = _input->LA(1);
        if (!(_la == ArcscriptParser::MUL

        || _la == ArcscriptParser::DIV)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(236);
        signed_unary_numeric_expression(); 
      }
      setState(241);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Signed_unary_numeric_expressionContext ------------------------------------------------------------------

ArcscriptParser::Signed_unary_numeric_expressionContext::Signed_unary_numeric_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::SignContext* ArcscriptParser::Signed_unary_numeric_expressionContext::sign() {
  return getRuleContext<ArcscriptParser::SignContext>(0);
}

ArcscriptParser::Unary_numeric_expressionContext* ArcscriptParser::Signed_unary_numeric_expressionContext::unary_numeric_expression() {
  return getRuleContext<ArcscriptParser::Unary_numeric_expressionContext>(0);
}


size_t ArcscriptParser::Signed_unary_numeric_expressionContext::getRuleIndex() const {
  return ArcscriptParser::RuleSigned_unary_numeric_expression;
}


std::any ArcscriptParser::Signed_unary_numeric_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitSigned_unary_numeric_expression(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Signed_unary_numeric_expressionContext* ArcscriptParser::signed_unary_numeric_expression() {
  Signed_unary_numeric_expressionContext *_localctx = _tracker.createInstance<Signed_unary_numeric_expressionContext>(_ctx, getState());
  enterRule(_localctx, 50, ArcscriptParser::RuleSigned_unary_numeric_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(246);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::ADD:
      case ArcscriptParser::SUB: {
        enterOuterAlt(_localctx, 1);
        setState(242);
        sign();
        setState(243);
        unary_numeric_expression();
        break;
      }

      case ArcscriptParser::FLOAT:
      case ArcscriptParser::INTEGER:
      case ArcscriptParser::LPAREN:
      case ArcscriptParser::BOOLEAN:
      case ArcscriptParser::FNAME:
      case ArcscriptParser::STRING:
      case ArcscriptParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(245);
        unary_numeric_expression();
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

//----------------- Unary_numeric_expressionContext ------------------------------------------------------------------

ArcscriptParser::Unary_numeric_expressionContext::Unary_numeric_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Unary_numeric_expressionContext::FLOAT() {
  return getToken(ArcscriptParser::FLOAT, 0);
}

tree::TerminalNode* ArcscriptParser::Unary_numeric_expressionContext::VARIABLE() {
  return getToken(ArcscriptParser::VARIABLE, 0);
}

tree::TerminalNode* ArcscriptParser::Unary_numeric_expressionContext::INTEGER() {
  return getToken(ArcscriptParser::INTEGER, 0);
}

tree::TerminalNode* ArcscriptParser::Unary_numeric_expressionContext::STRING() {
  return getToken(ArcscriptParser::STRING, 0);
}

tree::TerminalNode* ArcscriptParser::Unary_numeric_expressionContext::BOOLEAN() {
  return getToken(ArcscriptParser::BOOLEAN, 0);
}

ArcscriptParser::Function_callContext* ArcscriptParser::Unary_numeric_expressionContext::function_call() {
  return getRuleContext<ArcscriptParser::Function_callContext>(0);
}

tree::TerminalNode* ArcscriptParser::Unary_numeric_expressionContext::LPAREN() {
  return getToken(ArcscriptParser::LPAREN, 0);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::Unary_numeric_expressionContext::compound_condition_or() {
  return getRuleContext<ArcscriptParser::Compound_condition_orContext>(0);
}

tree::TerminalNode* ArcscriptParser::Unary_numeric_expressionContext::RPAREN() {
  return getToken(ArcscriptParser::RPAREN, 0);
}


size_t ArcscriptParser::Unary_numeric_expressionContext::getRuleIndex() const {
  return ArcscriptParser::RuleUnary_numeric_expression;
}


std::any ArcscriptParser::Unary_numeric_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitUnary_numeric_expression(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Unary_numeric_expressionContext* ArcscriptParser::unary_numeric_expression() {
  Unary_numeric_expressionContext *_localctx = _tracker.createInstance<Unary_numeric_expressionContext>(_ctx, getState());
  enterRule(_localctx, 52, ArcscriptParser::RuleUnary_numeric_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(259);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(248);
        match(ArcscriptParser::FLOAT);
        break;
      }

      case ArcscriptParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(249);
        antlrcpp::downCast<Unary_numeric_expressionContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
        this->assertVariable(antlrcpp::downCast<Unary_numeric_expressionContext *>(_localctx)->variableToken);
        break;
      }

      case ArcscriptParser::INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(251);
        match(ArcscriptParser::INTEGER);
        break;
      }

      case ArcscriptParser::STRING: {
        enterOuterAlt(_localctx, 4);
        setState(252);
        match(ArcscriptParser::STRING);
        break;
      }

      case ArcscriptParser::BOOLEAN: {
        enterOuterAlt(_localctx, 5);
        setState(253);
        match(ArcscriptParser::BOOLEAN);
        break;
      }

      case ArcscriptParser::FNAME: {
        enterOuterAlt(_localctx, 6);
        setState(254);
        function_call();
        break;
      }

      case ArcscriptParser::LPAREN: {
        enterOuterAlt(_localctx, 7);
        setState(255);
        match(ArcscriptParser::LPAREN);
        setState(256);
        compound_condition_or();
        setState(257);
        match(ArcscriptParser::RPAREN);
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

//----------------- Function_callContext ------------------------------------------------------------------

ArcscriptParser::Function_callContext::Function_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Function_callContext::FNAME() {
  return getToken(ArcscriptParser::FNAME, 0);
}

tree::TerminalNode* ArcscriptParser::Function_callContext::LPAREN() {
  return getToken(ArcscriptParser::LPAREN, 0);
}

tree::TerminalNode* ArcscriptParser::Function_callContext::RPAREN() {
  return getToken(ArcscriptParser::RPAREN, 0);
}

ArcscriptParser::Argument_listContext* ArcscriptParser::Function_callContext::argument_list() {
  return getRuleContext<ArcscriptParser::Argument_listContext>(0);
}


size_t ArcscriptParser::Function_callContext::getRuleIndex() const {
  return ArcscriptParser::RuleFunction_call;
}


std::any ArcscriptParser::Function_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitFunction_call(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Function_callContext* ArcscriptParser::function_call() {
  Function_callContext *_localctx = _tracker.createInstance<Function_callContext>(_ctx, getState());
  enterRule(_localctx, 54, ArcscriptParser::RuleFunction_call);
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
    setState(261);
    antlrcpp::downCast<Function_callContext *>(_localctx)->fnameToken = match(ArcscriptParser::FNAME);
    setState(262);
    match(ArcscriptParser::LPAREN);
    setState(264);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3378524379461632) != 0)) {
      setState(263);
      antlrcpp::downCast<Function_callContext *>(_localctx)->argument_listContext = argument_list();
    }
    setState(266);
    match(ArcscriptParser::RPAREN);
    this->assertFunctionArguments(antlrcpp::downCast<Function_callContext *>(_localctx)->fnameToken, antlrcpp::downCast<Function_callContext *>(_localctx)->argument_listContext);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Void_function_callContext ------------------------------------------------------------------

ArcscriptParser::Void_function_callContext::Void_function_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Void_function_callContext::VFNAME() {
  return getToken(ArcscriptParser::VFNAME, 0);
}

tree::TerminalNode* ArcscriptParser::Void_function_callContext::LPAREN() {
  return getToken(ArcscriptParser::LPAREN, 0);
}

tree::TerminalNode* ArcscriptParser::Void_function_callContext::RPAREN() {
  return getToken(ArcscriptParser::RPAREN, 0);
}

ArcscriptParser::Argument_listContext* ArcscriptParser::Void_function_callContext::argument_list() {
  return getRuleContext<ArcscriptParser::Argument_listContext>(0);
}

tree::TerminalNode* ArcscriptParser::Void_function_callContext::VFNAMEVARS() {
  return getToken(ArcscriptParser::VFNAMEVARS, 0);
}

ArcscriptParser::Variable_listContext* ArcscriptParser::Void_function_callContext::variable_list() {
  return getRuleContext<ArcscriptParser::Variable_listContext>(0);
}


size_t ArcscriptParser::Void_function_callContext::getRuleIndex() const {
  return ArcscriptParser::RuleVoid_function_call;
}


std::any ArcscriptParser::Void_function_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitVoid_function_call(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Void_function_callContext* ArcscriptParser::void_function_call() {
  Void_function_callContext *_localctx = _tracker.createInstance<Void_function_callContext>(_ctx, getState());
  enterRule(_localctx, 56, ArcscriptParser::RuleVoid_function_call);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(283);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::VFNAME: {
        enterOuterAlt(_localctx, 1);
        setState(269);
        antlrcpp::downCast<Void_function_callContext *>(_localctx)->vfnameToken = match(ArcscriptParser::VFNAME);
        setState(270);
        match(ArcscriptParser::LPAREN);
        setState(272);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 3378524379461632) != 0)) {
          setState(271);
          antlrcpp::downCast<Void_function_callContext *>(_localctx)->argument_listContext = argument_list();
        }
        setState(274);
        match(ArcscriptParser::RPAREN);
        this->assertFunctionArguments(antlrcpp::downCast<Void_function_callContext *>(_localctx)->vfnameToken, antlrcpp::downCast<Void_function_callContext *>(_localctx)->argument_listContext);
        break;
      }

      case ArcscriptParser::VFNAMEVARS: {
        enterOuterAlt(_localctx, 2);
        setState(276);
        antlrcpp::downCast<Void_function_callContext *>(_localctx)->vfnamevarsToken = match(ArcscriptParser::VFNAMEVARS);
        setState(277);
        match(ArcscriptParser::LPAREN);
        setState(279);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ArcscriptParser::VARIABLE) {
          setState(278);
          antlrcpp::downCast<Void_function_callContext *>(_localctx)->variable_listContext = variable_list();
        }
        setState(281);
        match(ArcscriptParser::RPAREN);
        this->assertFunctionArguments(antlrcpp::downCast<Void_function_callContext *>(_localctx)->vfnamevarsToken, antlrcpp::downCast<Void_function_callContext *>(_localctx)->variable_listContext);
        		
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

//----------------- SignContext ------------------------------------------------------------------

ArcscriptParser::SignContext::SignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::SignContext::ADD() {
  return getToken(ArcscriptParser::ADD, 0);
}

tree::TerminalNode* ArcscriptParser::SignContext::SUB() {
  return getToken(ArcscriptParser::SUB, 0);
}


size_t ArcscriptParser::SignContext::getRuleIndex() const {
  return ArcscriptParser::RuleSign;
}


std::any ArcscriptParser::SignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitSign(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::SignContext* ArcscriptParser::sign() {
  SignContext *_localctx = _tracker.createInstance<SignContext>(_ctx, getState());
  enterRule(_localctx, 58, ArcscriptParser::RuleSign);
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
    setState(285);
    _la = _input->LA(1);
    if (!(_la == ArcscriptParser::ADD

    || _la == ArcscriptParser::SUB)) {
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

//----------------- Variable_listContext ------------------------------------------------------------------

ArcscriptParser::Variable_listContext::Variable_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ArcscriptParser::Variable_listContext::VARIABLE() {
  return getTokens(ArcscriptParser::VARIABLE);
}

tree::TerminalNode* ArcscriptParser::Variable_listContext::VARIABLE(size_t i) {
  return getToken(ArcscriptParser::VARIABLE, i);
}

std::vector<tree::TerminalNode *> ArcscriptParser::Variable_listContext::COMMA() {
  return getTokens(ArcscriptParser::COMMA);
}

tree::TerminalNode* ArcscriptParser::Variable_listContext::COMMA(size_t i) {
  return getToken(ArcscriptParser::COMMA, i);
}


size_t ArcscriptParser::Variable_listContext::getRuleIndex() const {
  return ArcscriptParser::RuleVariable_list;
}


std::any ArcscriptParser::Variable_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitVariable_list(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Variable_listContext* ArcscriptParser::variable_list() {
  Variable_listContext *_localctx = _tracker.createInstance<Variable_listContext>(_ctx, getState());
  enterRule(_localctx, 60, ArcscriptParser::RuleVariable_list);
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
    antlrcpp::downCast<Variable_listContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
    setState(292);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ArcscriptParser::COMMA) {
      setState(288);
      match(ArcscriptParser::COMMA);
      setState(289);
      antlrcpp::downCast<Variable_listContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
      setState(294);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    this->assertVariable(antlrcpp::downCast<Variable_listContext *>(_localctx)->variableToken);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Compound_condition_orContext ------------------------------------------------------------------

ArcscriptParser::Compound_condition_orContext::Compound_condition_orContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Compound_condition_andContext* ArcscriptParser::Compound_condition_orContext::compound_condition_and() {
  return getRuleContext<ArcscriptParser::Compound_condition_andContext>(0);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::Compound_condition_orContext::compound_condition_or() {
  return getRuleContext<ArcscriptParser::Compound_condition_orContext>(0);
}

tree::TerminalNode* ArcscriptParser::Compound_condition_orContext::OR() {
  return getToken(ArcscriptParser::OR, 0);
}

tree::TerminalNode* ArcscriptParser::Compound_condition_orContext::ORKEYWORD() {
  return getToken(ArcscriptParser::ORKEYWORD, 0);
}


size_t ArcscriptParser::Compound_condition_orContext::getRuleIndex() const {
  return ArcscriptParser::RuleCompound_condition_or;
}


std::any ArcscriptParser::Compound_condition_orContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitCompound_condition_or(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::compound_condition_or() {
  Compound_condition_orContext *_localctx = _tracker.createInstance<Compound_condition_orContext>(_ctx, getState());
  enterRule(_localctx, 62, ArcscriptParser::RuleCompound_condition_or);
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
    setState(297);
    compound_condition_and();
    setState(300);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::OR

    || _la == ArcscriptParser::ORKEYWORD) {
      setState(298);
      _la = _input->LA(1);
      if (!(_la == ArcscriptParser::OR

      || _la == ArcscriptParser::ORKEYWORD)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(299);
      compound_condition_or();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Compound_condition_andContext ------------------------------------------------------------------

ArcscriptParser::Compound_condition_andContext::Compound_condition_andContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Negated_unary_conditionContext* ArcscriptParser::Compound_condition_andContext::negated_unary_condition() {
  return getRuleContext<ArcscriptParser::Negated_unary_conditionContext>(0);
}

ArcscriptParser::Compound_condition_andContext* ArcscriptParser::Compound_condition_andContext::compound_condition_and() {
  return getRuleContext<ArcscriptParser::Compound_condition_andContext>(0);
}

tree::TerminalNode* ArcscriptParser::Compound_condition_andContext::AND() {
  return getToken(ArcscriptParser::AND, 0);
}

tree::TerminalNode* ArcscriptParser::Compound_condition_andContext::ANDKEYWORD() {
  return getToken(ArcscriptParser::ANDKEYWORD, 0);
}


size_t ArcscriptParser::Compound_condition_andContext::getRuleIndex() const {
  return ArcscriptParser::RuleCompound_condition_and;
}


std::any ArcscriptParser::Compound_condition_andContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitCompound_condition_and(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Compound_condition_andContext* ArcscriptParser::compound_condition_and() {
  Compound_condition_andContext *_localctx = _tracker.createInstance<Compound_condition_andContext>(_ctx, getState());
  enterRule(_localctx, 64, ArcscriptParser::RuleCompound_condition_and);
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
    setState(302);
    negated_unary_condition();
    setState(305);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::AND

    || _la == ArcscriptParser::ANDKEYWORD) {
      setState(303);
      _la = _input->LA(1);
      if (!(_la == ArcscriptParser::AND

      || _la == ArcscriptParser::ANDKEYWORD)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(304);
      compound_condition_and();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Negated_unary_conditionContext ------------------------------------------------------------------

ArcscriptParser::Negated_unary_conditionContext::Negated_unary_conditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::Unary_conditionContext* ArcscriptParser::Negated_unary_conditionContext::unary_condition() {
  return getRuleContext<ArcscriptParser::Unary_conditionContext>(0);
}

tree::TerminalNode* ArcscriptParser::Negated_unary_conditionContext::NEG() {
  return getToken(ArcscriptParser::NEG, 0);
}

tree::TerminalNode* ArcscriptParser::Negated_unary_conditionContext::NOTKEYWORD() {
  return getToken(ArcscriptParser::NOTKEYWORD, 0);
}


size_t ArcscriptParser::Negated_unary_conditionContext::getRuleIndex() const {
  return ArcscriptParser::RuleNegated_unary_condition;
}


std::any ArcscriptParser::Negated_unary_conditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitNegated_unary_condition(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Negated_unary_conditionContext* ArcscriptParser::negated_unary_condition() {
  Negated_unary_conditionContext *_localctx = _tracker.createInstance<Negated_unary_conditionContext>(_ctx, getState());
  enterRule(_localctx, 66, ArcscriptParser::RuleNegated_unary_condition);
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
    setState(308);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::NEG

    || _la == ArcscriptParser::NOTKEYWORD) {
      setState(307);
      _la = _input->LA(1);
      if (!(_la == ArcscriptParser::NEG

      || _la == ArcscriptParser::NOTKEYWORD)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(310);
    unary_condition();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Unary_conditionContext ------------------------------------------------------------------

ArcscriptParser::Unary_conditionContext::Unary_conditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ArcscriptParser::ConditionContext* ArcscriptParser::Unary_conditionContext::condition() {
  return getRuleContext<ArcscriptParser::ConditionContext>(0);
}


size_t ArcscriptParser::Unary_conditionContext::getRuleIndex() const {
  return ArcscriptParser::RuleUnary_condition;
}


std::any ArcscriptParser::Unary_conditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitUnary_condition(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Unary_conditionContext* ArcscriptParser::unary_condition() {
  Unary_conditionContext *_localctx = _tracker.createInstance<Unary_conditionContext>(_ctx, getState());
  enterRule(_localctx, 68, ArcscriptParser::RuleUnary_condition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    condition();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

ArcscriptParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ArcscriptParser::ExpressionContext *> ArcscriptParser::ConditionContext::expression() {
  return getRuleContexts<ArcscriptParser::ExpressionContext>();
}

ArcscriptParser::ExpressionContext* ArcscriptParser::ConditionContext::expression(size_t i) {
  return getRuleContext<ArcscriptParser::ExpressionContext>(i);
}

ArcscriptParser::Conditional_operatorContext* ArcscriptParser::ConditionContext::conditional_operator() {
  return getRuleContext<ArcscriptParser::Conditional_operatorContext>(0);
}


size_t ArcscriptParser::ConditionContext::getRuleIndex() const {
  return ArcscriptParser::RuleCondition;
}


std::any ArcscriptParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::ConditionContext* ArcscriptParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 70, ArcscriptParser::RuleCondition);
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
    setState(314);
    expression();
    setState(318);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 281477090639872) != 0)) {
      setState(315);
      conditional_operator();
      setState(316);
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

//----------------- Conditional_operatorContext ------------------------------------------------------------------

ArcscriptParser::Conditional_operatorContext::Conditional_operatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::GT() {
  return getToken(ArcscriptParser::GT, 0);
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::GE() {
  return getToken(ArcscriptParser::GE, 0);
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::LT() {
  return getToken(ArcscriptParser::LT, 0);
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::LE() {
  return getToken(ArcscriptParser::LE, 0);
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::EQ() {
  return getToken(ArcscriptParser::EQ, 0);
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::NE() {
  return getToken(ArcscriptParser::NE, 0);
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::ISKEYWORD() {
  return getToken(ArcscriptParser::ISKEYWORD, 0);
}

tree::TerminalNode* ArcscriptParser::Conditional_operatorContext::NOTKEYWORD() {
  return getToken(ArcscriptParser::NOTKEYWORD, 0);
}


size_t ArcscriptParser::Conditional_operatorContext::getRuleIndex() const {
  return ArcscriptParser::RuleConditional_operator;
}


std::any ArcscriptParser::Conditional_operatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitConditional_operator(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::Conditional_operatorContext* ArcscriptParser::conditional_operator() {
  Conditional_operatorContext *_localctx = _tracker.createInstance<Conditional_operatorContext>(_ctx, getState());
  enterRule(_localctx, 72, ArcscriptParser::RuleConditional_operator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(329);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(320);
      match(ArcscriptParser::GT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(321);
      match(ArcscriptParser::GE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(322);
      match(ArcscriptParser::LT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(323);
      match(ArcscriptParser::LE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(324);
      match(ArcscriptParser::EQ);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(325);
      match(ArcscriptParser::NE);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(326);
      match(ArcscriptParser::ISKEYWORD);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(327);
      match(ArcscriptParser::ISKEYWORD);
      setState(328);
      match(ArcscriptParser::NOTKEYWORD);
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

//----------------- ExpressionContext ------------------------------------------------------------------

ArcscriptParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::ExpressionContext::STRING() {
  return getToken(ArcscriptParser::STRING, 0);
}

tree::TerminalNode* ArcscriptParser::ExpressionContext::BOOLEAN() {
  return getToken(ArcscriptParser::BOOLEAN, 0);
}

ArcscriptParser::Additive_numeric_expressionContext* ArcscriptParser::ExpressionContext::additive_numeric_expression() {
  return getRuleContext<ArcscriptParser::Additive_numeric_expressionContext>(0);
}


size_t ArcscriptParser::ExpressionContext::getRuleIndex() const {
  return ArcscriptParser::RuleExpression;
}


std::any ArcscriptParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ArcscriptParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

ArcscriptParser::ExpressionContext* ArcscriptParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 74, ArcscriptParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(334);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(331);
      match(ArcscriptParser::STRING);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(332);
      match(ArcscriptParser::BOOLEAN);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(333);
      additive_numeric_expression(0);
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

bool ArcscriptParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 21: return mentionSempred(antlrcpp::downCast<MentionContext *>(context), predicateIndex);
    case 23: return additive_numeric_expressionSempred(antlrcpp::downCast<Additive_numeric_expressionContext *>(context), predicateIndex);
    case 24: return multiplicative_numeric_expressionSempred(antlrcpp::downCast<Multiplicative_numeric_expressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ArcscriptParser::mentionSempred(MentionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return this->assertMention(antlrcpp::downCast<MentionContext *>(_localctx)->attr)
    		;

  default:
    break;
  }
  return true;
}

bool ArcscriptParser::additive_numeric_expressionSempred(Additive_numeric_expressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool ArcscriptParser::multiplicative_numeric_expressionSempred(Multiplicative_numeric_expressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void ArcscriptParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  arcscriptparserParserInitialize();
#else
  ::antlr4::internal::call_once(arcscriptparserParserOnceFlag, arcscriptparserParserInitialize);
#endif
}
