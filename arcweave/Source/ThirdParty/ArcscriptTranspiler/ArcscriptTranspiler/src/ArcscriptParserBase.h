#pragma once

#include "antlr4-runtime.h"
#include "ArcscriptHelpers.h"
#include "ArcscriptFunctions.h"

class ArcscriptParserBase : public antlr4::Parser {
private:
  Arcweave::ArcscriptState* _state;
public:
  ArcscriptParserBase(antlr4::TokenStream *input) : Parser(input) { }
  inline void setArcscriptState(Arcweave::ArcscriptState *state) { _state = state; };
  bool assertVariable(antlr4::Token *variable);
  bool assertMention(std::any attrCtxList);
  bool assertFunctionArguments(antlr4::Token *fname, std::any argumentList);
};