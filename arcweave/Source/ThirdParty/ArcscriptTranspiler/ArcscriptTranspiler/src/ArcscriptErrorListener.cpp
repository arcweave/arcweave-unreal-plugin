#include "ArcscriptErrorListener.h"
#include "ArcscriptErrorExceptions.h"

using namespace antlr4;
using namespace Arcweave;

ErrorListener ErrorListener::INSTANCE;

void ErrorListener::syntaxError(Recognizer * /*recognizer*/, Token * /*offendingSymbol*/,
  size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr /*e*/)  {
  throw ParseErrorException(msg, line, charPositionInLine);
}