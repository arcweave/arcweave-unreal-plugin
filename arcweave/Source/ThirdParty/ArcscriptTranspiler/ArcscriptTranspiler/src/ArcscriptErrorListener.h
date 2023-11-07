#pragma once

#include "BaseErrorListener.h"

using namespace antlr4;

namespace Arcweave {
  class ErrorListener : public BaseErrorListener {
  public:
    static ErrorListener INSTANCE;
    void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line,
                    size_t charPositionInLine, const std::string &msg, std::exception_ptr e);
  };
}