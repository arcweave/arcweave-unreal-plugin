#include "ArcscriptParser.h"
#include "ArcscriptLexer.h"
#include "ArcscriptParserBase.h"

using namespace antlr4;

bool ArcscriptParserBase::assertVariable(antlr4::Token *variable) {
  std::string variableName = variable->getText();
  if (_state->varNameToID.count(variableName) > 0) {
    return true;
  }
  throw Arcweave::ParseErrorException("Unknown variable \"" + variableName + "\"");
  return false;
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

bool ArcscriptParserBase::assertMention(std::any attrCtxList) {
  std::map<std::string, std::string> attrs;
  ParserRuleContext *ctx = this->getContext();
  std::vector<Arcweave::ArcscriptParser::Mention_attributesContext *> ctxList = ctx->getRuleContexts<Arcweave::ArcscriptParser::Mention_attributesContext>();
  for (auto attrCtx : ctxList) {
    tree::TerminalNode *nameNode = attrCtx->getToken(Arcweave::ArcscriptParser::ATTR_NAME, 0);
    std::string attrName = "";
    if (nameNode) {
      attrName = nameNode->getText();
    }
    tree::TerminalNode *valueNode = attrCtx->getToken(Arcweave::ArcscriptParser::ATTR_VALUE, 0);
    std::string attrValue = "";
    if (nameNode) {
      attrValue = valueNode->getText();
    }

    if ((attrValue.rfind("\"", 0) == 0 && ends_with(attrValue, "\"")) ||
         attrValue.rfind("'", 0) == 0 && ends_with(attrValue, "'")) {
      
      attrValue = attrValue.substr(1, attrValue.size() - 2);
      
    }
    attrs[attrName] = attrValue;
  }
  std::stringstream classList(attrs["class"]);
  std::string className;
  bool classFound = false;
  while(classList >> className){
    if (className == "mention") {
      classFound = true;
      break;
    }
  }
  if (!classFound) {
    throw Arcweave::ParseErrorException("Invalid mention type");
    return false;
  }
  if (attrs["data-type"] != "element") {
    throw Arcweave::ParseErrorException("Invalid mention type");
    return false;
  }
  if (_state->visits.count(attrs["data-id"]) == 0) {
    throw Arcweave::ParseErrorException("Invalid element mention");
  }

  return true;
}

bool ArcscriptParserBase::assertFunctionArguments(Token *fname, std::any argumentList) {
  int argListLength = 0;
  std::string functionName = fname->getText();
  int min = Arcweave::ArcscriptFunctions::functions[functionName].minArgs;
  int max = Arcweave::ArcscriptFunctions::functions[functionName].maxArgs;
  if (argumentList.type() == typeid(Arcweave::ArcscriptParser::Argument_listContext*)) {
    Arcweave::ArcscriptParser::Argument_listContext *argumentListCtx = std::any_cast<Arcweave::ArcscriptParser::Argument_listContext*>(argumentList);
    if (argumentListCtx != NULL) {
      argListLength = argumentListCtx->argument().size();
    }
  }
  if (argumentList.type() == typeid(Arcweave::ArcscriptParser::Variable_listContext*)) {
    Arcweave::ArcscriptParser::Variable_listContext *variableListCtx = std::any_cast<Arcweave::ArcscriptParser::Variable_listContext*>(argumentList);
    if (variableListCtx != NULL) {
      argListLength = variableListCtx->VARIABLE().size();
    }
  }

  if ((min != -1 && argListLength < min) || (max != -1 && argListLength > max)) {
    throw Arcweave::ParseErrorException("Wrong number of arguments in \""+ functionName + "\".");
    return false;
  }
  
  return true;
}

void ArcscriptParserBase::setLineStart(antlr4::Token* token)
{
  openTagEndPos = token->getStartIndex() + token->getText().length();
}
