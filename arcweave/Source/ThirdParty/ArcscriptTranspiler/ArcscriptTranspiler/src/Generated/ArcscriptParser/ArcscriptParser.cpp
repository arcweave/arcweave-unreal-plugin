
// Generated from ArcscriptParser.g4 by ANTLR 4.13.0


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
      "input", "script", "script_section", "assignment_segment", "function_call_segment", 
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
      "", "", "", "'</code></pre>'", "'<span'", "", "", "", "'('", "')'", 
      "'*='", "'/='", "'+='", "'-='", "'*'", "'/'", "'+'", "'-'", "", "", 
      "", "", "'=='", "'!='", "", "'||'", "", "'!'", "','", "'{'", "'}'", 
      "", "", "'show'", "", "'if'", "'else'", "'elseif'", "'endif'", "'and'", 
      "'or'", "'is'", "'not'", "", "", "", "'>'", "", "", "'/span>'", "", 
      "'<'"
    },
    std::vector<std::string>{
      "", "CODESTART", "NORMALTEXT", "CODEEND", "MENTION_TAG_OPEN", "FLOAT", 
      "INTEGER", "DIGIT", "LPAREN", "RPAREN", "ASSIGNMUL", "ASSIGNDIV", 
      "ASSIGNADD", "ASSIGNSUB", "MUL", "DIV", "ADD", "SUB", "GE", "GT", 
      "LE", "LT", "EQ", "NE", "AND", "OR", "ASSIGN", "NEG", "COMMA", "LBRACE", 
      "RBRACE", "BOOLEAN", "FNAME", "VFNAME", "VFNAMEVARS", "IFKEYWORD", 
      "ELSEKEYWORD", "ELSEIFKEYWORD", "ENDIFKEYWORD", "ANDKEYWORD", "ORKEYWORD", 
      "ISKEYWORD", "NOTKEYWORD", "STRING", "VARIABLE", "WHITESPACE", "TAG_CLOSE", 
      "ATTR_NAME", "TAG_EQUALS", "MENTION_TAG_CLOSE", "TAG_WHITESPACE", 
      "TAG_OPEN", "MENTION_LABEL", "ATTR_VALUE", "ATTRIBUTE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,54,279,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,1,0,1,0,1,0,1,0,1,0,1,0,1,
  	0,1,0,3,0,75,8,0,1,1,4,1,78,8,1,11,1,12,1,79,1,2,4,2,83,8,2,11,2,12,2,
  	84,1,2,1,2,1,2,3,2,90,8,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,5,5,
  	102,8,5,10,5,12,5,105,9,5,1,5,3,5,108,8,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,
  	1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,
  	11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,14,1,14,1,14,5,
  	14,147,8,14,10,14,12,14,150,9,14,1,15,1,15,1,15,3,15,155,8,15,1,16,1,
  	16,5,16,159,8,16,10,16,12,16,162,9,16,1,16,1,16,3,16,166,8,16,1,16,1,
  	16,1,16,1,16,1,17,1,17,1,17,3,17,175,8,17,1,18,1,18,1,18,3,18,180,8,18,
  	1,19,1,19,1,19,3,19,185,8,19,1,20,1,20,1,20,1,20,3,20,191,8,20,1,21,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,202,8,21,1,22,1,22,1,22,3,
  	22,207,8,22,1,22,1,22,1,22,1,23,1,23,1,23,3,23,215,8,23,1,23,1,23,1,23,
  	1,23,1,23,3,23,222,8,23,1,23,1,23,3,23,226,8,23,1,24,1,24,1,25,1,25,1,
  	25,5,25,233,8,25,10,25,12,25,236,9,25,1,25,1,25,1,26,1,26,1,26,3,26,243,
  	8,26,1,27,1,27,1,27,3,27,248,8,27,1,28,3,28,251,8,28,1,28,1,28,1,29,1,
  	29,1,30,1,30,1,30,1,30,3,30,261,8,30,1,31,1,31,1,31,1,31,1,31,1,31,1,
  	31,1,31,1,31,3,31,272,8,31,1,32,1,32,1,32,3,32,277,8,32,1,32,0,0,33,0,
  	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,0,6,2,0,10,13,26,26,1,0,16,17,1,0,14,15,2,0,25,25,
  	40,40,2,0,24,24,39,39,2,0,27,27,42,42,284,0,74,1,0,0,0,2,77,1,0,0,0,4,
  	89,1,0,0,0,6,91,1,0,0,0,8,95,1,0,0,0,10,99,1,0,0,0,12,111,1,0,0,0,14,
  	116,1,0,0,0,16,121,1,0,0,0,18,126,1,0,0,0,20,129,1,0,0,0,22,132,1,0,0,
  	0,24,136,1,0,0,0,26,141,1,0,0,0,28,143,1,0,0,0,30,154,1,0,0,0,32,156,
  	1,0,0,0,34,171,1,0,0,0,36,176,1,0,0,0,38,181,1,0,0,0,40,190,1,0,0,0,42,
  	201,1,0,0,0,44,203,1,0,0,0,46,225,1,0,0,0,48,227,1,0,0,0,50,229,1,0,0,
  	0,52,239,1,0,0,0,54,244,1,0,0,0,56,250,1,0,0,0,58,254,1,0,0,0,60,256,
  	1,0,0,0,62,271,1,0,0,0,64,276,1,0,0,0,66,67,3,2,1,0,67,68,5,0,0,1,68,
  	75,1,0,0,0,69,70,5,1,0,0,70,71,3,52,26,0,71,72,5,3,0,0,72,73,5,0,0,1,
  	73,75,1,0,0,0,74,66,1,0,0,0,74,69,1,0,0,0,75,1,1,0,0,0,76,78,3,4,2,0,
  	77,76,1,0,0,0,78,79,1,0,0,0,79,77,1,0,0,0,79,80,1,0,0,0,80,3,1,0,0,0,
  	81,83,5,2,0,0,82,81,1,0,0,0,83,84,1,0,0,0,84,82,1,0,0,0,84,85,1,0,0,0,
  	85,90,1,0,0,0,86,90,3,6,3,0,87,90,3,8,4,0,88,90,3,10,5,0,89,82,1,0,0,
  	0,89,86,1,0,0,0,89,87,1,0,0,0,89,88,1,0,0,0,90,5,1,0,0,0,91,92,5,1,0,
  	0,92,93,3,24,12,0,93,94,5,3,0,0,94,7,1,0,0,0,95,96,5,1,0,0,96,97,3,26,
  	13,0,97,98,5,3,0,0,98,9,1,0,0,0,99,103,3,12,6,0,100,102,3,14,7,0,101,
  	100,1,0,0,0,102,105,1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,107,1,
  	0,0,0,105,103,1,0,0,0,106,108,3,16,8,0,107,106,1,0,0,0,107,108,1,0,0,
  	0,108,109,1,0,0,0,109,110,3,22,11,0,110,11,1,0,0,0,111,112,5,1,0,0,112,
  	113,3,18,9,0,113,114,5,3,0,0,114,115,3,2,1,0,115,13,1,0,0,0,116,117,5,
  	1,0,0,117,118,3,20,10,0,118,119,5,3,0,0,119,120,3,2,1,0,120,15,1,0,0,
  	0,121,122,5,1,0,0,122,123,5,36,0,0,123,124,5,3,0,0,124,125,3,2,1,0,125,
  	17,1,0,0,0,126,127,5,35,0,0,127,128,3,52,26,0,128,19,1,0,0,0,129,130,
  	5,37,0,0,130,131,3,52,26,0,131,21,1,0,0,0,132,133,5,1,0,0,133,134,5,38,
  	0,0,134,135,5,3,0,0,135,23,1,0,0,0,136,137,5,44,0,0,137,138,7,0,0,0,138,
  	139,3,52,26,0,139,140,6,12,-1,0,140,25,1,0,0,0,141,142,3,46,23,0,142,
  	27,1,0,0,0,143,148,3,30,15,0,144,145,5,28,0,0,145,147,3,30,15,0,146,144,
  	1,0,0,0,147,150,1,0,0,0,148,146,1,0,0,0,148,149,1,0,0,0,149,29,1,0,0,
  	0,150,148,1,0,0,0,151,155,3,36,18,0,152,155,5,43,0,0,153,155,3,32,16,
  	0,154,151,1,0,0,0,154,152,1,0,0,0,154,153,1,0,0,0,155,31,1,0,0,0,156,
  	160,5,4,0,0,157,159,3,34,17,0,158,157,1,0,0,0,159,162,1,0,0,0,160,158,
  	1,0,0,0,160,161,1,0,0,0,161,163,1,0,0,0,162,160,1,0,0,0,163,165,5,46,
  	0,0,164,166,5,52,0,0,165,164,1,0,0,0,165,166,1,0,0,0,166,167,1,0,0,0,
  	167,168,5,51,0,0,168,169,5,49,0,0,169,170,6,16,-1,0,170,33,1,0,0,0,171,
  	174,5,47,0,0,172,173,5,48,0,0,173,175,5,53,0,0,174,172,1,0,0,0,174,175,
  	1,0,0,0,175,35,1,0,0,0,176,179,3,38,19,0,177,178,7,1,0,0,178,180,3,36,
  	18,0,179,177,1,0,0,0,179,180,1,0,0,0,180,37,1,0,0,0,181,184,3,40,20,0,
  	182,183,7,2,0,0,183,185,3,38,19,0,184,182,1,0,0,0,184,185,1,0,0,0,185,
  	39,1,0,0,0,186,187,3,48,24,0,187,188,3,42,21,0,188,191,1,0,0,0,189,191,
  	3,42,21,0,190,186,1,0,0,0,190,189,1,0,0,0,191,41,1,0,0,0,192,202,5,5,
  	0,0,193,194,5,44,0,0,194,202,6,21,-1,0,195,202,5,6,0,0,196,202,3,44,22,
  	0,197,198,5,8,0,0,198,199,3,52,26,0,199,200,5,9,0,0,200,202,1,0,0,0,201,
  	192,1,0,0,0,201,193,1,0,0,0,201,195,1,0,0,0,201,196,1,0,0,0,201,197,1,
  	0,0,0,202,43,1,0,0,0,203,204,5,32,0,0,204,206,5,8,0,0,205,207,3,28,14,
  	0,206,205,1,0,0,0,206,207,1,0,0,0,207,208,1,0,0,0,208,209,5,9,0,0,209,
  	210,6,22,-1,0,210,45,1,0,0,0,211,212,5,33,0,0,212,214,5,8,0,0,213,215,
  	3,28,14,0,214,213,1,0,0,0,214,215,1,0,0,0,215,216,1,0,0,0,216,217,5,9,
  	0,0,217,226,6,23,-1,0,218,219,5,34,0,0,219,221,5,8,0,0,220,222,3,50,25,
  	0,221,220,1,0,0,0,221,222,1,0,0,0,222,223,1,0,0,0,223,224,5,9,0,0,224,
  	226,6,23,-1,0,225,211,1,0,0,0,225,218,1,0,0,0,226,47,1,0,0,0,227,228,
  	7,1,0,0,228,49,1,0,0,0,229,234,5,44,0,0,230,231,5,28,0,0,231,233,5,44,
  	0,0,232,230,1,0,0,0,233,236,1,0,0,0,234,232,1,0,0,0,234,235,1,0,0,0,235,
  	237,1,0,0,0,236,234,1,0,0,0,237,238,6,25,-1,0,238,51,1,0,0,0,239,242,
  	3,54,27,0,240,241,7,3,0,0,241,243,3,52,26,0,242,240,1,0,0,0,242,243,1,
  	0,0,0,243,53,1,0,0,0,244,247,3,56,28,0,245,246,7,4,0,0,246,248,3,54,27,
  	0,247,245,1,0,0,0,247,248,1,0,0,0,248,55,1,0,0,0,249,251,7,5,0,0,250,
  	249,1,0,0,0,250,251,1,0,0,0,251,252,1,0,0,0,252,253,3,58,29,0,253,57,
  	1,0,0,0,254,255,3,60,30,0,255,59,1,0,0,0,256,260,3,64,32,0,257,258,3,
  	62,31,0,258,259,3,64,32,0,259,261,1,0,0,0,260,257,1,0,0,0,260,261,1,0,
  	0,0,261,61,1,0,0,0,262,272,5,19,0,0,263,272,5,18,0,0,264,272,5,21,0,0,
  	265,272,5,20,0,0,266,272,5,22,0,0,267,272,5,23,0,0,268,272,5,41,0,0,269,
  	270,5,41,0,0,270,272,5,42,0,0,271,262,1,0,0,0,271,263,1,0,0,0,271,264,
  	1,0,0,0,271,265,1,0,0,0,271,266,1,0,0,0,271,267,1,0,0,0,271,268,1,0,0,
  	0,271,269,1,0,0,0,272,63,1,0,0,0,273,277,5,43,0,0,274,277,5,31,0,0,275,
  	277,3,36,18,0,276,273,1,0,0,0,276,274,1,0,0,0,276,275,1,0,0,0,277,65,
  	1,0,0,0,26,74,79,84,89,103,107,148,154,160,165,174,179,184,190,201,206,
  	214,221,225,234,242,247,250,260,271,276
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

tree::TerminalNode* ArcscriptParser::InputContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

ArcscriptParser::Compound_condition_orContext* ArcscriptParser::InputContext::compound_condition_or() {
  return getRuleContext<ArcscriptParser::Compound_condition_orContext>(0);
}

tree::TerminalNode* ArcscriptParser::InputContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
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
    setState(74);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(66);
      script();
      setState(67);
      match(ArcscriptParser::EOF);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(69);
      match(ArcscriptParser::CODESTART);
      setState(70);
      compound_condition_or();
      setState(71);
      match(ArcscriptParser::CODEEND);
      setState(72);
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
    setState(77); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(76);
              script_section();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(79); 
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

std::vector<tree::TerminalNode *> ArcscriptParser::Script_sectionContext::NORMALTEXT() {
  return getTokens(ArcscriptParser::NORMALTEXT);
}

tree::TerminalNode* ArcscriptParser::Script_sectionContext::NORMALTEXT(size_t i) {
  return getToken(ArcscriptParser::NORMALTEXT, i);
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
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(82); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(81);
                match(ArcscriptParser::NORMALTEXT);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(84); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(86);
      assignment_segment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(87);
      function_call_segment();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(88);
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

//----------------- Assignment_segmentContext ------------------------------------------------------------------

ArcscriptParser::Assignment_segmentContext::Assignment_segmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ArcscriptParser::Assignment_segmentContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

ArcscriptParser::Statement_assignmentContext* ArcscriptParser::Assignment_segmentContext::statement_assignment() {
  return getRuleContext<ArcscriptParser::Statement_assignmentContext>(0);
}

tree::TerminalNode* ArcscriptParser::Assignment_segmentContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
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
  enterRule(_localctx, 6, ArcscriptParser::RuleAssignment_segment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(ArcscriptParser::CODESTART);
    setState(92);
    statement_assignment();
    setState(93);
    match(ArcscriptParser::CODEEND);
   
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

tree::TerminalNode* ArcscriptParser::Function_call_segmentContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

ArcscriptParser::Statement_function_callContext* ArcscriptParser::Function_call_segmentContext::statement_function_call() {
  return getRuleContext<ArcscriptParser::Statement_function_callContext>(0);
}

tree::TerminalNode* ArcscriptParser::Function_call_segmentContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
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
  enterRule(_localctx, 8, ArcscriptParser::RuleFunction_call_segment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(95);
    match(ArcscriptParser::CODESTART);
    setState(96);
    statement_function_call();
    setState(97);
    match(ArcscriptParser::CODEEND);
   
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
  enterRule(_localctx, 10, ArcscriptParser::RuleConditional_section);

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
    setState(99);
    if_section();
    setState(103);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(100);
        else_if_section(); 
      }
      setState(105);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
    setState(107);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(106);
      else_section();
      break;
    }

    default:
      break;
    }
    setState(109);
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

tree::TerminalNode* ArcscriptParser::If_sectionContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

ArcscriptParser::If_clauseContext* ArcscriptParser::If_sectionContext::if_clause() {
  return getRuleContext<ArcscriptParser::If_clauseContext>(0);
}

tree::TerminalNode* ArcscriptParser::If_sectionContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
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
  enterRule(_localctx, 12, ArcscriptParser::RuleIf_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    match(ArcscriptParser::CODESTART);
    setState(112);
    if_clause();
    setState(113);
    match(ArcscriptParser::CODEEND);
    setState(114);
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

tree::TerminalNode* ArcscriptParser::Else_if_sectionContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

ArcscriptParser::Else_if_clauseContext* ArcscriptParser::Else_if_sectionContext::else_if_clause() {
  return getRuleContext<ArcscriptParser::Else_if_clauseContext>(0);
}

tree::TerminalNode* ArcscriptParser::Else_if_sectionContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
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
  enterRule(_localctx, 14, ArcscriptParser::RuleElse_if_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(ArcscriptParser::CODESTART);
    setState(117);
    else_if_clause();
    setState(118);
    match(ArcscriptParser::CODEEND);
    setState(119);
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

tree::TerminalNode* ArcscriptParser::Else_sectionContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

tree::TerminalNode* ArcscriptParser::Else_sectionContext::ELSEKEYWORD() {
  return getToken(ArcscriptParser::ELSEKEYWORD, 0);
}

tree::TerminalNode* ArcscriptParser::Else_sectionContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
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
  enterRule(_localctx, 16, ArcscriptParser::RuleElse_section);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(ArcscriptParser::CODESTART);
    setState(122);
    match(ArcscriptParser::ELSEKEYWORD);
    setState(123);
    match(ArcscriptParser::CODEEND);
    setState(124);
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
  enterRule(_localctx, 18, ArcscriptParser::RuleIf_clause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    match(ArcscriptParser::IFKEYWORD);
    setState(127);
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
  enterRule(_localctx, 20, ArcscriptParser::RuleElse_if_clause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    match(ArcscriptParser::ELSEIFKEYWORD);
    setState(130);
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

tree::TerminalNode* ArcscriptParser::Endif_segmentContext::CODESTART() {
  return getToken(ArcscriptParser::CODESTART, 0);
}

tree::TerminalNode* ArcscriptParser::Endif_segmentContext::ENDIFKEYWORD() {
  return getToken(ArcscriptParser::ENDIFKEYWORD, 0);
}

tree::TerminalNode* ArcscriptParser::Endif_segmentContext::CODEEND() {
  return getToken(ArcscriptParser::CODEEND, 0);
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
  enterRule(_localctx, 22, ArcscriptParser::RuleEndif_segment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    match(ArcscriptParser::CODESTART);
    setState(133);
    match(ArcscriptParser::ENDIFKEYWORD);
    setState(134);
    match(ArcscriptParser::CODEEND);
   
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
  enterRule(_localctx, 24, ArcscriptParser::RuleStatement_assignment);
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
    setState(136);
    antlrcpp::downCast<Statement_assignmentContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
    setState(137);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 67124224) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(138);
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
  enterRule(_localctx, 26, ArcscriptParser::RuleStatement_function_call);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
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
  enterRule(_localctx, 28, ArcscriptParser::RuleArgument_list);
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
    setState(143);
    argument();
    setState(148);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ArcscriptParser::COMMA) {
      setState(144);
      match(ArcscriptParser::COMMA);
      setState(145);
      argument();
      setState(150);
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
  enterRule(_localctx, 30, ArcscriptParser::RuleArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(154);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::FLOAT:
      case ArcscriptParser::INTEGER:
      case ArcscriptParser::LPAREN:
      case ArcscriptParser::ADD:
      case ArcscriptParser::SUB:
      case ArcscriptParser::FNAME:
      case ArcscriptParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(151);
        additive_numeric_expression();
        break;
      }

      case ArcscriptParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(152);
        match(ArcscriptParser::STRING);
        break;
      }

      case ArcscriptParser::MENTION_TAG_OPEN: {
        enterOuterAlt(_localctx, 3);
        setState(153);
        mention();
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
  enterRule(_localctx, 32, ArcscriptParser::RuleMention);
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
    setState(156);
    match(ArcscriptParser::MENTION_TAG_OPEN);
    setState(160);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ArcscriptParser::ATTR_NAME) {
      setState(157);
      antlrcpp::downCast<MentionContext *>(_localctx)->mention_attributesContext = mention_attributes();
      antlrcpp::downCast<MentionContext *>(_localctx)->attr.push_back(antlrcpp::downCast<MentionContext *>(_localctx)->mention_attributesContext);
      setState(162);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(163);
    match(ArcscriptParser::TAG_CLOSE);
    setState(165);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::MENTION_LABEL) {
      setState(164);
      match(ArcscriptParser::MENTION_LABEL);
    }
    setState(167);
    match(ArcscriptParser::TAG_OPEN);
    setState(168);
    match(ArcscriptParser::MENTION_TAG_CLOSE);
    this->assertMention(antlrcpp::downCast<MentionContext *>(_localctx)->attr);
   
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
  enterRule(_localctx, 34, ArcscriptParser::RuleMention_attributes);
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
    setState(171);
    match(ArcscriptParser::ATTR_NAME);
    setState(174);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::TAG_EQUALS) {
      setState(172);
      match(ArcscriptParser::TAG_EQUALS);
      setState(173);
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
  Additive_numeric_expressionContext *_localctx = _tracker.createInstance<Additive_numeric_expressionContext>(_ctx, getState());
  enterRule(_localctx, 36, ArcscriptParser::RuleAdditive_numeric_expression);
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
    setState(176);
    multiplicative_numeric_expression();
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::ADD

    || _la == ArcscriptParser::SUB) {
      setState(177);
      _la = _input->LA(1);
      if (!(_la == ArcscriptParser::ADD

      || _la == ArcscriptParser::SUB)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(178);
      additive_numeric_expression();
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
  Multiplicative_numeric_expressionContext *_localctx = _tracker.createInstance<Multiplicative_numeric_expressionContext>(_ctx, getState());
  enterRule(_localctx, 38, ArcscriptParser::RuleMultiplicative_numeric_expression);
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
    setState(181);
    signed_unary_numeric_expression();
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::MUL

    || _la == ArcscriptParser::DIV) {
      setState(182);
      _la = _input->LA(1);
      if (!(_la == ArcscriptParser::MUL

      || _la == ArcscriptParser::DIV)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(183);
      multiplicative_numeric_expression();
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
  enterRule(_localctx, 40, ArcscriptParser::RuleSigned_unary_numeric_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(190);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::ADD:
      case ArcscriptParser::SUB: {
        enterOuterAlt(_localctx, 1);
        setState(186);
        sign();
        setState(187);
        unary_numeric_expression();
        break;
      }

      case ArcscriptParser::FLOAT:
      case ArcscriptParser::INTEGER:
      case ArcscriptParser::LPAREN:
      case ArcscriptParser::FNAME:
      case ArcscriptParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(189);
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
  enterRule(_localctx, 42, ArcscriptParser::RuleUnary_numeric_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(201);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(192);
        match(ArcscriptParser::FLOAT);
        break;
      }

      case ArcscriptParser::VARIABLE: {
        enterOuterAlt(_localctx, 2);
        setState(193);
        antlrcpp::downCast<Unary_numeric_expressionContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
        this->assertVariable(antlrcpp::downCast<Unary_numeric_expressionContext *>(_localctx)->variableToken);
        break;
      }

      case ArcscriptParser::INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(195);
        match(ArcscriptParser::INTEGER);
        break;
      }

      case ArcscriptParser::FNAME: {
        enterOuterAlt(_localctx, 4);
        setState(196);
        function_call();
        break;
      }

      case ArcscriptParser::LPAREN: {
        enterOuterAlt(_localctx, 5);
        setState(197);
        match(ArcscriptParser::LPAREN);
        setState(198);
        compound_condition_or();
        setState(199);
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
  enterRule(_localctx, 44, ArcscriptParser::RuleFunction_call);
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
    setState(203);
    antlrcpp::downCast<Function_callContext *>(_localctx)->fnameToken = match(ArcscriptParser::FNAME);
    setState(204);
    match(ArcscriptParser::LPAREN);
    setState(206);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26392574230896) != 0)) {
      setState(205);
      antlrcpp::downCast<Function_callContext *>(_localctx)->argument_listContext = argument_list();
    }
    setState(208);
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
  enterRule(_localctx, 46, ArcscriptParser::RuleVoid_function_call);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(225);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::VFNAME: {
        enterOuterAlt(_localctx, 1);
        setState(211);
        antlrcpp::downCast<Void_function_callContext *>(_localctx)->vfnameToken = match(ArcscriptParser::VFNAME);
        setState(212);
        match(ArcscriptParser::LPAREN);
        setState(214);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 26392574230896) != 0)) {
          setState(213);
          antlrcpp::downCast<Void_function_callContext *>(_localctx)->argument_listContext = argument_list();
        }
        setState(216);
        match(ArcscriptParser::RPAREN);
        this->assertFunctionArguments(antlrcpp::downCast<Void_function_callContext *>(_localctx)->vfnameToken, antlrcpp::downCast<Void_function_callContext *>(_localctx)->argument_listContext);
        break;
      }

      case ArcscriptParser::VFNAMEVARS: {
        enterOuterAlt(_localctx, 2);
        setState(218);
        antlrcpp::downCast<Void_function_callContext *>(_localctx)->vfnamevarsToken = match(ArcscriptParser::VFNAMEVARS);
        setState(219);
        match(ArcscriptParser::LPAREN);
        setState(221);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ArcscriptParser::VARIABLE) {
          setState(220);
          antlrcpp::downCast<Void_function_callContext *>(_localctx)->variable_listContext = variable_list();
        }
        setState(223);
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
  enterRule(_localctx, 48, ArcscriptParser::RuleSign);
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
    setState(227);
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
  enterRule(_localctx, 50, ArcscriptParser::RuleVariable_list);
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
    setState(229);
    antlrcpp::downCast<Variable_listContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
    setState(234);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ArcscriptParser::COMMA) {
      setState(230);
      match(ArcscriptParser::COMMA);
      setState(231);
      antlrcpp::downCast<Variable_listContext *>(_localctx)->variableToken = match(ArcscriptParser::VARIABLE);
      setState(236);
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
  enterRule(_localctx, 52, ArcscriptParser::RuleCompound_condition_or);
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
    setState(239);
    compound_condition_and();
    setState(242);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::OR

    || _la == ArcscriptParser::ORKEYWORD) {
      setState(240);
      _la = _input->LA(1);
      if (!(_la == ArcscriptParser::OR

      || _la == ArcscriptParser::ORKEYWORD)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(241);
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
  enterRule(_localctx, 54, ArcscriptParser::RuleCompound_condition_and);
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
    setState(244);
    negated_unary_condition();
    setState(247);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::AND

    || _la == ArcscriptParser::ANDKEYWORD) {
      setState(245);
      _la = _input->LA(1);
      if (!(_la == ArcscriptParser::AND

      || _la == ArcscriptParser::ANDKEYWORD)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(246);
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
  enterRule(_localctx, 56, ArcscriptParser::RuleNegated_unary_condition);
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
    setState(250);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ArcscriptParser::NEG

    || _la == ArcscriptParser::NOTKEYWORD) {
      setState(249);
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
    setState(252);
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
  enterRule(_localctx, 58, ArcscriptParser::RuleUnary_condition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
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
  enterRule(_localctx, 60, ArcscriptParser::RuleCondition);
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
    setState(256);
    expression();
    setState(260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2199039770624) != 0)) {
      setState(257);
      conditional_operator();
      setState(258);
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
  enterRule(_localctx, 62, ArcscriptParser::RuleConditional_operator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(262);
      match(ArcscriptParser::GT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(263);
      match(ArcscriptParser::GE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(264);
      match(ArcscriptParser::LT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(265);
      match(ArcscriptParser::LE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(266);
      match(ArcscriptParser::EQ);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(267);
      match(ArcscriptParser::NE);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(268);
      match(ArcscriptParser::ISKEYWORD);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(269);
      match(ArcscriptParser::ISKEYWORD);
      setState(270);
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
  enterRule(_localctx, 64, ArcscriptParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(276);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ArcscriptParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(273);
        match(ArcscriptParser::STRING);
        break;
      }

      case ArcscriptParser::BOOLEAN: {
        enterOuterAlt(_localctx, 2);
        setState(274);
        match(ArcscriptParser::BOOLEAN);
        break;
      }

      case ArcscriptParser::FLOAT:
      case ArcscriptParser::INTEGER:
      case ArcscriptParser::LPAREN:
      case ArcscriptParser::ADD:
      case ArcscriptParser::SUB:
      case ArcscriptParser::FNAME:
      case ArcscriptParser::VARIABLE: {
        enterOuterAlt(_localctx, 3);
        setState(275);
        additive_numeric_expression();
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

void ArcscriptParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  arcscriptparserParserInitialize();
#else
  ::antlr4::internal::call_once(arcscriptparserParserOnceFlag, arcscriptparserParserInitialize);
#endif
}
