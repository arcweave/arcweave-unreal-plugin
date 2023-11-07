#if defined _WIN64
	#pragma once

	#include "antlr4-runtime.h"
	#include "ArcscriptLexer.h"
	#include "ArcscriptParser.h"
	#include "ArcscriptVisitor.h"
	#include <windows.h>
	#ifdef ARCSCRIPTTRANSPILER_EXPORTS
		#define ARCSCRIPTTRANSPILER_API __declspec(dllexport)
	#else
		#define ARCSCRIPTTRANSPILER_API __declspec(dllimport)
	#endif
#else
	#define HELLOWORLD_IMPORT
#endif

namespace Arcweave
{
  /**
   * @enum InputType
   * The arscript code types
  */
  enum InputType { 
	/// @brief A condition (results to bool) code type
	CONDITION,
	/// @brief A script code type
	SCRIPT
  };

  /**
   * @struct TranspilerOutput
   * @brief The structure contains info that the ArcscriptTranspiler returns
   * @var TranspilerOutput::output
   * Member 'output' contains the text output when a codeblock is run
   * @var TranspilerOutput::changes
   * Member 'changes' contains the variables that are going to be changed from the codeblock
   * @var TranspilerOutput::result
   * Member 'result' contains the result of the ArcscriptTranspiler code. Useful in condition blocks
   * @var TranspilerOutput::type
   * Member 'type' contains the type of the code block i.e. CONDITION or SCRIPT
  */
  struct TranspilerOutput {
	std::string output;
	std::map<std::string, std::any> changes;
	std::any result;
	InputType type;
  };
  

  // The following types starting with a U* are the types that the exported DLL function accepts and returns
  extern "C" struct UVariableChange {
	  char* varId;
	  VariableType type;
	  int int_result;
	  double double_result;
	  char* string_result;
	  bool bool_result;
	  UVariableChange() {
		  varId = nullptr;
		  type = VariableType::AW_ANY;
		  int_result = 0;
		  double_result = 0.0;
		  string_result = nullptr;
		  bool_result = false;
	  }
  };
  
  extern "C" struct UTranspilerOutput {
	  char* output;
	  InputType type;
	  UVariableChange* changes;
	  size_t changesLen = 0;
	  bool conditionResult = false;

      UTranspilerOutput() {
          output = nullptr;
          type = InputType::SCRIPT;
          changes = nullptr;
          changesLen = 0;
          conditionResult = false;
      }
  };
  

	struct UVariable {
		const char* id;
		const char* name;
		VariableType type;
		int int_val;
		double double_val;
		const char* string_val;
		bool bool_val;

        UVariable() {
            id = nullptr;
            name = nullptr;
            type = VariableType::AW_ANY;
            int_val = 0;
            double_val = 0;
            string_val = nullptr;
            bool_val = false;
        }
	};
  
	struct UVisit {
		const char* elId;
		int visits;

		UVisit() {
			elId = nullptr;
			visits = 0;
		}
	};
  
  /**
   * Implementation of the Arcscript Transpiler in C++. Uses the ANTLR4 runtime library
   * to run the code and it needs the initial variables and the current element ID it is
   * transpiling.
   * 
   * 
  */
  class ArcscriptTranspiler {
  public:

	ArcscriptState state;

	ArcscriptTranspiler(std::string elId, std::map<std::string, Variable> initVars, std::map<std::string, int> _visits) : state(elId, initVars, _visits) { };

	/**
	 * Runs the arcscript code and returns it's results.
	 * @param code The code block that we need to parse
	 * @return The result of the ran script
	*/
	TranspilerOutput runScript(std::string code);

	//ARCSCRIPTTRANSPILER_API UTranspilerOutput URunScript(char* code);
  };
};
extern "C" ARCSCRIPTTRANSPILER_API UTranspilerOutput* runScriptExport(const char* code, const char* elId, UVariable* variables, size_t varLength, UVisit* visits, size_t visitsLength);
extern "C" ARCSCRIPTTRANSPILER_API void deallocateOutput(UTranspilerOutput* output);