#include "ArcscriptFunctions.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

namespace Arcweave {
    std::map<std::string, ArcscriptFunctions::FunctionInfo> ArcscriptFunctions::functions = {
      { "abs", { 1, 1 } },
      { "max", { 2, -1 }},
      { "min", { 2, -1 }},
      { "random", { 0, 0 }},
      { "reset", { 1, -1 }},
      { "resetAll", { 0, -1} },
      { "roll", { 1, 2 } },
      { "round", { 1, 1} },
      { "show", { 1, -1 } },
      { "sqr", { 1, 1 } },
      { "sqrt", { 1, 1 } },
      { "visits", { 0, 1 } },
    };

    std::any ArcscriptFunctions::Call(std::string functionName, std::vector<std::any> _args) {
        std::vector<std::any> args;
        for (std::any arg : _args) {
            if (arg.type() == typeid(Expression)) {
                args.push_back(std::any_cast<Expression>(arg).value);
            }
            else {
                args.push_back(arg);
            }
        }
        std::any result;
        if (functionName == "sqrt") {
            result = this->Sqrt(args);
        }
        else if (functionName == "sqr") {
            result = this->Sqr(args);
        }
        else if (functionName == "abs") {
            result = this->Abs(args);
        }
        else if (functionName == "random") {
            result = this->Random(args);
        }
        else if (functionName == "roll") {
            result = this->Roll(args);
        }
        else if (functionName == "show") {
            result = this->Show(args);
        }
        else if (functionName == "reset") {
            result = this->Reset(args);
        }
        else if (functionName == "resetAll") {
            result = this->ResetAll(args);
        }
        else if (functionName == "round") {
            result = this->Round(args);
        }
        else if (functionName == "min") {
            result = this->Min(args);
        }
        else if (functionName == "max") {
            result = this->Max(args);
        }
        else if (functionName == "visits") {
            result = this->Visits(args);
        }
        return result;
    }

    std::any ArcscriptFunctions::Sqrt(std::vector<std::any> args) {

        if (args[0].type() == typeid(int)) {
            return sqrt(std::any_cast<int>(args[0]));
        }
        return sqrt(std::any_cast<double>(args[0]));
    }

    std::any ArcscriptFunctions::Sqr(std::vector<std::any> args) {
        if (args[0].type() == typeid(int)) {
            int n = std::any_cast<int>(args[0]);
            return n * n;
        }
        double n = std::any_cast<double>(args[0]);
        return n * n;
    }

    std::any ArcscriptFunctions::Abs(std::vector<std::any> args) {
        if (args[0].type() == typeid(int)) {
            return abs(std::any_cast<int>(args[0]));
        }
        double n = std::any_cast<double>(args[0]);
        return abs(n);
    }

    std::any ArcscriptFunctions::Random(std::vector<std::any> args) {
        srand(time(NULL));
        return ((double)rand() / (RAND_MAX));
    }

    std::any ArcscriptFunctions::Roll(std::vector<std::any> args) {
        int maxRoll = std::any_cast<int>(args[0]);
        int numRolls = 1;
        if (args.size() == 2) {
            numRolls = std::any_cast<int>(args[1]);
        }
        int sum = 0;
        for (int i = 0; i < numRolls; i++) {
            int oneRoll = rand() % maxRoll + 1;
            sum += oneRoll;
        }
        return sum;
    }

    std::any ArcscriptFunctions::Show(std::vector<std::any> args) {
        std::string result;
        for (int i = 0; i < args.size(); i++) {
            std::any arg = args[i];
            if (arg.type() == typeid(int)) {
                result += std::to_string(std::any_cast<int>(arg));
            }
            else if (arg.type() == typeid(double)) {
                result += std::to_string(std::any_cast<double>(arg));
            }
            else if (arg.type() == typeid(bool)) {
                result += std::to_string(std::any_cast<bool>(arg));
            }
            else if (arg.type() == typeid(std::string)) {
                result += std::any_cast<std::string>(arg);
            }
        }
        _state->outputs.push_back("<p>" + result + "</p>");
        return std::any();
    }

    std::any ArcscriptFunctions::Round(std::vector<std::any> args) {
        if (args[0].type() == typeid(int)) {
            return round(std::any_cast<int>(args[0]));
        }
        double n = std::any_cast<double>(args[0]);
        return round(n);
    }

    std::any ArcscriptFunctions::Min(std::vector<std::any> args) {
        std::vector<double> casted;
        for (std::any arg : args) {
            double val;
            if (arg.type() == typeid(int)) {
                val = std::any_cast<int>(arg);
            }
            else {
                val = std::any_cast<double>(arg);
            }
            casted.push_back(val);
        }
        return *min_element(casted.begin(), casted.end());
    }

    std::any ArcscriptFunctions::Max(std::vector<std::any> args) {
        std::vector<double> casted;
        for (std::any arg : args) {
            double val;
            if (arg.type() == typeid(int)) {
                val = std::any_cast<int>(arg);
            }
            else {
                val = std::any_cast<double>(arg);
            }
            casted.push_back(val);
        }
        return *max_element(casted.begin(), casted.end());
    }

    std::any ArcscriptFunctions::Reset(std::vector<std::any> args) {
        std::vector<Variable> variables;
        for (std::any arg : args) {
            variables.push_back(std::any_cast<Variable>(arg));
        }
        _state->resetVars(variables);
        return std::any();
    }

    std::any ArcscriptFunctions::ResetAll(std::vector<std::any> args) {
        std::vector<Variable> except;
        for (std::any arg : args) {
            except.push_back(std::any_cast<Variable>(arg));
        }
        _state->resetAllVars(except);
        return std::any();
    }

    std::any ArcscriptFunctions::Visits(std::vector<std::any> args) {
        std::string nodeId = _state->currentElement;
        if (args.size() > 0) {
            Mention mention = std::any_cast<Mention>(args[0]);

            if (mention.attrs.count("data-id")) {
                nodeId = mention.attrs["data-id"];
            }
        }

        return _state->visits[nodeId];
    }
}