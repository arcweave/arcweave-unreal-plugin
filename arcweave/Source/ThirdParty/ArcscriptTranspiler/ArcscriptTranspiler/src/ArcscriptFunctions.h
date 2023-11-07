#pragma once

#include "ArcscriptHelpers.h"
#include <typeindex>
#include <iostream>
#include <functional>

namespace Arcweave {
class ArcscriptFunctions {
private:
  ArcscriptState *_state;

public:
  struct FunctionInfo {
    int minArgs;
    int maxArgs;
  };

  static std::map<std::string, FunctionInfo> functions;

  ArcscriptFunctions(ArcscriptState* state) : _state(state) {
    
  }

  std::any Call(std::string functionName, std::vector<std::any> args);

  std::any Abs(std::vector<std::any> args);
  std::any Max(std::vector<std::any> args);
  std::any Min(std::vector<std::any> args);
  std::any Random(std::vector<std::any> args);
  std::any Reset(std::vector<std::any> args);
  std::any ResetAll(std::vector<std::any> args);
  std::any Roll(std::vector<std::any> args);
  std::any Round(std::vector<std::any> args);
  std::any Show(std::vector<std::any> args);
  std::any Sqr(std::vector<std::any> args);
  std::any Sqrt(std::vector<std::any> args);
  std::any Visits(std::vector<std::any> args);
};
}