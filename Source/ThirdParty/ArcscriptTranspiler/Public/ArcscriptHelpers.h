#pragma once

#include <any>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <functional>

#include "ArcscriptOutputs.h"

namespace Arcweave {

enum VariableType {
    AW_STRING,
    AW_INTEGER,
    AW_DOUBLE,
    AW_BOOLEAN,
    AW_ANY
};

  struct IdentifierDef {
    std::string name;
    std::string scope;
  };

struct Variable {
  std::string id;
  std::string name;
  VariableType type;
  std::any value;
  std::string scope;
};

class ArcscriptState {
public:
  std::map<std::string, std::any> variableChanges;
  std::map<std::string, Variable> variableValues;
  std::map<std::string, std::string> varNameToID;
  ArcscriptOutputs outputs;
  std::string currentElement;
  std::map<std::string, int> visits;

  std::function<void(const char*)> emit;

  ArcscriptState(std::string elementId, std::map<std::string, Variable> varValues, std::map<std::string, int> _visits, std::function<void(const char*)> _emit) {
    currentElement = std::move(elementId);
    variableValues = std::move(varValues);
    for(const auto&[varId, variable] : variableValues) {
      std::string name = variable.name;
      if (variable.scope != "") {
        name = variable.scope + "." + variable.name;
      }
      varNameToID[name] = varId;
    }
    visits = std::move(_visits);
    emit = _emit;
  }

  inline static std::string getVarFullName(IdentifierDef identifier) {
    if (identifier.scope != "") {
      return identifier.scope + "." + identifier.name;
    }
    return identifier.name;
  }

  inline std::any getVarValue(IdentifierDef identifier) {
    std::string varId = varNameToID[getVarFullName(identifier)];
    if (variableChanges.count(varId)) {
      return variableChanges[varId];
    }
    return variableValues[varId].value;
  }

  inline Variable getVar(IdentifierDef identifier) {
    return variableValues[varNameToID[getVarFullName(identifier)]];
  }

  inline void setVarValue(IdentifierDef identifier, std::any value) {
    std::string varId = varNameToID[getVarFullName(identifier)];
    variableChanges[varId] = value;
  }

  inline void resetVars(std::vector<Variable> vars) {
    for (Variable var : vars) {
      variableChanges[var.id] = var.value;
    }
  }

  inline void resetAllVars(std::vector<Variable> except) {
    std::set<std::string> exceptVariableIds;
    for (Variable var : except) {
      exceptVariableIds.insert(var.id);
    }
    std::map<std::string, Variable>::iterator it = variableValues.begin();
    while (it != variableValues.end())
    {
      if (exceptVariableIds.find(it->first) == exceptVariableIds.end()) { // not in except vars
        variableChanges[it->first] = it->second.value;
      }
      it++;
    }
  }

  inline void resetVisits() {
    for (auto visit: visits) {
      visits[visit.first] = 0;
    }
    emit("resetVisits");
  }
};

class Mention {
public:
  std::string label;
  std::map<std::string, std::string> attrs;
  Mention(std::string _label, std::map<std::string, std::string> _attrs) {
    label = _label;
    attrs = _attrs;
  }
  Mention(const Mention &m) {
    label = m.label;
    attrs = m.attrs;
  }
};
}
