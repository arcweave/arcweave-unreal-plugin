#if defined _WIN64
#pragma once
#include "ArcscriptTranspiler.h"
#include "ArcscriptErrorListener.h"
#include <sstream>
#include <iterator>
#include <windows.h>
#endif

#define _CRT_SECURE_NO_WARNINGS

using namespace Arcweave;
using namespace antlr4;

TranspilerOutput ArcscriptTranspiler::runScript(std::string code) {
  ANTLRInputStream input(code);
  ArcscriptLexer lexer(&input);

  TranspilerOutput result;

  ErrorListener lexerErrorListener;
  lexer.removeErrorListeners();
  lexer.addErrorListener(&lexerErrorListener);
  
  CommonTokenStream tokens(&lexer);

  // Run the lexer
  tokens.fill();

  ArcscriptParser parser(&tokens);
  parser.setArcscriptState(&state);
  ErrorListener parserErrorListener;
  parser.removeErrorListeners();
  parser.addErrorListener(&parserErrorListener);

  ArcscriptParser::InputContext *tree;

  // Run the parser
  tree = parser.input();
  
  ArcscriptVisitor visitor(&state);
  
  // Run the visitor
  std::any res(visitor.visitInput(tree));

  result.changes = visitor.state->variableChanges;
  std::vector<std::string> outputs = visitor.state->outputs;

  // concatenate the outputs
  const char* const delim = "";
  std::ostringstream imploded;
  std::copy(outputs.begin(), outputs.end(), std::ostream_iterator<std::string>(imploded, delim));
  result.output = imploded.str();
  result.result = res;
  
  if (tree->script() != NULL) {
    result.type = SCRIPT;
  } else {
    result.type = CONDITION;
  }

  return result;
}

ARCSCRIPTTRANSPILER_API UTranspilerOutput* runScriptExport(const char* code, const char* elId, UVariable* variables, size_t varLength, UVisit* visits, size_t visitsLength)
{
    Arcweave::TranspilerOutput transpilerOutput;

    transpilerOutput.type = InputType::CONDITION;

    std::string sCode(code);
    std::string sElId(elId);

    std::map<std::string, Variable> initVars;
    for (size_t i = 0; i < varLength; i++) {
        Variable var;
        var.id = std::string(variables[i].id);
        var.name = std::string(variables[i].name);
        var.type = variables[i].type;
        
        if (var.type == VariableType::AW_STRING) {
            var.value = std::string(variables[i].string_val);
        }
        else if (var.type == VariableType::AW_INTEGER) {
            var.value = variables[i].int_val;
        }
        else if (var.type == VariableType::AW_DOUBLE) {
            var.value = variables[i].double_val;
        }
        else if (var.type == VariableType::AW_BOOLEAN) {
            var.value = variables[i].bool_val;
        }
        initVars[variables[i].id] = var;
    }

    std::map<std::string, int> initVisits;
    for (size_t i = 0; i < visitsLength; i++) {
        initVisits[std::string(visits[i].elId)] = visits[i].visits;
    }

    Arcweave::ArcscriptTranspiler transpiler(sElId, initVars, initVisits);
    transpilerOutput = transpiler.runScript(sCode);

    UTranspilerOutput* uTranspilerOutput = new UTranspilerOutput();
    uTranspilerOutput->output = _strdup(transpilerOutput.output.c_str());
    uTranspilerOutput->type = transpilerOutput.type;
    
    if (transpilerOutput.type == InputType::CONDITION) {
        uTranspilerOutput->conditionResult = std::any_cast<bool>(transpilerOutput.result);
    }

    size_t changesLen = transpilerOutput.changes.size();

    UVariableChange* variableChanges = new UVariableChange[changesLen];
    size_t i = 0;
    for (auto change : transpilerOutput.changes) {
        UVariableChange uChange;
        uChange.varId = _strdup(change.first.c_str());

        if (change.second.type() == typeid(std::string)) {
            uChange.type = VariableType::AW_STRING;
            std::string string_result = std::any_cast<std::string>(change.second);
            uChange.string_result = _strdup(string_result.c_str());
        }
        else if (change.second.type() == typeid(int)) {
            uChange.type = VariableType::AW_INTEGER;
            uChange.int_result = std::any_cast<int>(change.second);
        }
        else if (change.second.type() == typeid(double)) {
            uChange.type = VariableType::AW_DOUBLE;
            uChange.double_result = std::any_cast<double>(change.second);
        }
        else if (change.second.type() == typeid(bool)) {
            uChange.type = VariableType::AW_BOOLEAN;
            uChange.bool_result = std::any_cast<bool>(change.second);
        }
        variableChanges[i] = uChange;
        i++;
    }
    uTranspilerOutput->changes = variableChanges;
    uTranspilerOutput->changesLen = changesLen;

    return uTranspilerOutput;
    //std::cout << code << std::endl;
    //std::cout << elId << std::endl;
    //std::cout << _visits["test"] << std::endl;
    /*try {
        Arcweave::ArcscriptTranspiler transpiler(elId, initVars, _visits);
        
        try {
            transpilerOutput = transpiler.runScript(code);
        }
        catch (std::exception& e) {
            std::cerr << "Arcscript Transpiler failed during runScript: " << std::endl;
            std::cerr << e.what() << std::endl;
            return false;
        }
    }
    catch (std::exception &e) {
        std::cerr << "Arcscript Transpiler failed during init: " << std::endl;
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;*/
}

ARCSCRIPTTRANSPILER_API void deallocateOutput(UTranspilerOutput* output) {
    for (size_t i = 0; i < output->changesLen; i++) {
        free(output->changes[i].varId);
        if (output->changes[i].type == VariableType::AW_STRING) {
            free(output->changes[i].string_result);
        }
    }
    delete[] output->changes;
    free(output->output);
    delete output;
}