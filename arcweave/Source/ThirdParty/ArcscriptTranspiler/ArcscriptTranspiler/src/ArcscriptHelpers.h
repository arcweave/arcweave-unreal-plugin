#pragma once

#include <iostream>
#include <any>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <set>
#include "ArcscriptExpression.h"
#include "ArcscriptErrorExceptions.h"
#include "ArcscriptOutputs.h"

namespace Arcweave {

enum VariableType {
    AW_STRING,
    AW_INTEGER,
    AW_DOUBLE,
    AW_BOOLEAN,
    AW_ANY
};

struct Variable {
  std::string id;
  std::string name;
  VariableType type;
  std::any value;
};

class ArcscriptState {
public:
  std::map<std::string, std::any> variableChanges;
  std::map<std::string, Variable> variableValues;
  std::map<std::string, std::string> varNameToID;
  ArcscriptOutputs outputs;
  std::string currentElement;
  std::map<std::string, int> visits;

  ArcscriptState(std::string elementId, std::map<std::string, Variable> varValues, std::map<std::string, int> _visits) {
    currentElement = elementId;
    variableValues = varValues;
    for(const auto var : variableValues) {
      varNameToID[var.second.name] = var.first;
    }
    visits = _visits;
  };

  inline Variable getVar(std::string name) {
    std::string varId = varNameToID[name];
    return variableValues[varId];
  }

  inline std::any getVarValue(std::string name) {
    std::string varId = varNameToID[name];
    if(variableChanges.count(varId)) {
      return variableChanges[varId];
    }
    return variableValues[varId].value;
  }
  inline VariableType getVarType(std::string name) {
    return variableValues[varNameToID[name]].type;
  }
  inline void setVarValue(std::string name, std::any value) {
    std::string varId = varNameToID[name];
    variableChanges[varId] = value;
  }
  inline void setVarValues(std::vector<std::string> names, std::vector<std::any> values) {
    for (int i = 0; i < names.size(); i++) {
      variableChanges[names[i]] = values[i];
    }
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
