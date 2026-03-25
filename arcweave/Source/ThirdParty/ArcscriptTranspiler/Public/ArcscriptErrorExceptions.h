#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <exception>

#ifdef _WIN64
#define strdup _strdup
#endif

namespace Arcweave {
  class RuntimeErrorException : public std::exception {
    public:
    std::string message;
    size_t line = 0;
    size_t charPositionInLine = 0;
    RuntimeErrorException(std::string msg) {
      message = msg;
    };
    RuntimeErrorException(std::string msg, size_t _line, size_t _charPositionInLine) {
      message = msg;
      line = _line;
      charPositionInLine = _charPositionInLine;
    };
    char const* what() const noexcept override {
      if (line > 0) {
        std::ostringstream oss;
        oss << "line " << line << ":" << charPositionInLine << " " << message << std::endl;
        return strdup(oss.str().c_str());
      }
      return message.c_str();
    }
  };

  class ParseErrorException : public std::exception {
    public:
    std::string message;
    size_t line = 0;
    size_t charPositionInLine = 0;
    ParseErrorException(std::string msg) {
      message = msg;
    };
    ParseErrorException(std::string msg, size_t _line, size_t _charPositionInLine) {
      message = msg;
      line = _line;
      charPositionInLine = _charPositionInLine;
    };
    char const* what() const noexcept override {
      if (line > 0) {
        std::ostringstream oss;
        oss << "line " << line << ":" << charPositionInLine << " " << message << std::endl;
        return strdup(oss.str().c_str());
      }
      return message.c_str();
    }
  };
}

