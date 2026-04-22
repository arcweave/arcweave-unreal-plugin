#pragma once
#include "ArcscriptHelpers.h"
#include "ArcscriptErrorExceptions.h"

#if defined _WIN64
	#ifdef WIN_EXPORT
		#ifdef __GNUC__
			#define EXPORTED __attribute__ ((dllexport))
		#else
			#define EXPORTED __declspec(dllexport)
		#endif
	#else
		#ifdef __GNUC__
			#define EXPORTED __attribute__ ((dllimport))
		#else
			#define EXPORTED __declspec(dllimport)
		#endif
	#endif
	#define NOT_EXPORTED
#else
	#if __GNUC__ >= 4
		#define EXPORTED __attribute__ ((visibility("default")))
		#define NOT_EXPORTED __attribute__ ((visibility("hidden")))
	#else
		#define EXPORTED
		#define NOT_EXPORTED
	#endif
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

	ArcscriptTranspiler(std::string elId, std::map<std::string, Variable> initVars, std::map<std::string, int> _visits, std::function<void(const char*)> onEvent) : state(elId, initVars, _visits, onEvent) { };

	/**
	 * Runs the arcscript code and returns it's results.
	 * @param code The code block that we need to parse
	 * @return The result of the ran script
	*/
	TranspilerOutput runScript(std::string code);

	//ARCSCRIPTTRANSPILER_API UTranspilerOutput URunScript(char* code);
  };
};
EXPORTED Arcweave::UTranspilerOutput* runScriptExport(const char* code, const char* elId, Arcweave::UVariable* variables, size_t varLength, Arcweave::UVisit* visits, size_t visitsLength, std::function<void(const char*)> onEvent);
EXPORTED void deallocateOutput(Arcweave::UTranspilerOutput* output);
