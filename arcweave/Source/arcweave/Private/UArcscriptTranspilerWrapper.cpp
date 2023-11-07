// Fill out your copyright notice in the Description page of Project Settings.


#include "UArcscriptTranspilerWrapper.h"

#include "Core.h"
#include <string>

THIRD_PARTY_INCLUDES_START
#include "ArcscriptTranspiler.h"
THIRD_PARTY_INCLUDES_END

DEFINE_LOG_CATEGORY(LogArcweavePlugin);

FArcscriptTranspilerOutput UArcscriptTranspilerWrapper::RunScript(FString code, FString elementId, TMap<FString, FArcweaveVariable>& initialVars, TMap<FString, int> visits) {
	size_t varLength = initialVars.Num();
	size_t visitsLength = visits.Num();
	const char* dllCode = _strdup(TCHAR_TO_UTF8(*code));
	const char* dllElId = _strdup(TCHAR_TO_UTF8(*elementId));

    // Transform Unreal variable objects to DLL accepted objects
	UVariable* dllVars = new UVariable[varLength];
	UVisit* dllVisits = new UVisit[visitsLength];

	size_t i = 0;
	for (auto& var : initialVars) {
		dllVars[i].id = _strdup(TCHAR_TO_UTF8(*var.Value.Id));
		dllVars[i].name = _strdup(TCHAR_TO_UTF8(*var.Value.Name));
        dllVars[i].type = VariableType::AW_ANY;

	    UE_LOG(LogArcweavePlugin, Log, TEXT("var_name: %s, var_value %s"), *var.Value.Name, *var.Value.Value);
		if (var.Value.Type.Equals(TEXT("string"))) {
			dllVars[i].type = VariableType::AW_STRING;
			dllVars[i].string_val = _strdup(TCHAR_TO_UTF8(*(var.Value.Value)));
		}
		else if (var.Value.Type.Equals(TEXT("integer"))) {
			dllVars[i].type = VariableType::AW_INTEGER;
		    TCHAR* EndPtr = nullptr;
			dllVars[i].int_val = FCString::Strtoi(*var.Value.Value, &EndPtr, 10);
		}
		else if (var.Value.Type.Equals(TEXT("float"))) {
		    dllVars[i].type = VariableType::AW_DOUBLE;
		    dllVars[i].double_val = FCString::Atod(*var.Value.Value);
		}
		else if (var.Value.Type.Equals(TEXT("double"))) {
			dllVars[i].type = VariableType::AW_DOUBLE;
			dllVars[i].double_val =  FCString::Atod(*var.Value.Value);
		}
        else if (var.Value.Type.Equals(TEXT("boolean"))) {
            dllVars[i].type = VariableType::AW_BOOLEAN;
            dllVars[i].bool_val = (var.Value.Value == FString("true")) ? true : false;
        }
        i++;
    }

    i = 0;
    for (auto& visit : visits) {
        dllVisits[i].elId = _strdup(TCHAR_TO_UTF8(*visit.Key));
        dllVisits[i].visits = visit.Value;
        i++;
    }

    UTranspilerOutput* dllResult = nullptr;
    try {
        dllResult = runScriptExport(dllCode, dllElId, dllVars, varLength, dllVisits, visitsLength);
    }
    catch (Arcweave::ParseErrorException& e) {
        UE_LOG(LogArcweavePlugin, Error, TEXT("ParseErrorException %s"), *FString(e.what()));
        return FArcscriptTranspilerOutput();
    }
    catch (Arcweave::RuntimeErrorException& e) {
        UE_LOG(LogArcweavePlugin, Error, TEXT("RuntimeErrorException %s"), *FString(e.what()));
        return FArcscriptTranspilerOutput();
    }
    catch (std::exception& e) {
        UE_LOG(LogArcweavePlugin, Error, TEXT("%s"), *FString(e.what()));
        return FArcscriptTranspilerOutput();
    }

    FArcscriptTranspilerOutput result;
    result.Output = FString(dllResult->output);
    result.ConditionResult = dllResult->conditionResult;
    if (dllResult->type == Arcweave::InputType::CONDITION) {
        result.Type = FArcscriptInputType::CONDITION;
    }
    else {
        result.Type = FArcscriptInputType::SCRIPT;
    }

    for (i = 0; i < dllResult->changesLen; i++) {
        FArcscriptVariableChange change;
        change.Id = FString(dllResult->changes[i].varId);

        switch (dllResult->changes[i].type)
        {
        case VariableType::AW_STRING:
            change.Type = "string";
            break;
        case VariableType::AW_INTEGER:
            change.Type = "integer";
            break;
        case VariableType::AW_DOUBLE:
            change.Type = "double";
            break;
        case VariableType::AW_BOOLEAN:
            change.Type = "bool";
            break;
        default:
            change.Type = "";
            break;
        }

        if (change.Type == "string") {
            change.Value = MakeShareable(new FJsonValueString(FString(dllResult->changes[i].string_result)));
        }
        else if (change.Type == "integer") {
            change.Value = MakeShareable(new FJsonValueNumber(dllResult->changes[i].int_result));
        }
        else if (change.Type == "double") {
            change.Value = MakeShareable(new FJsonValueNumber(dllResult->changes[i].double_result));
        }
        else if (change.Type == "bool") {
            change.Value = MakeShareable(new FJsonValueBoolean(dllResult->changes[i].bool_result));
        }
        result.Changes.Add(change);
    }

    /*FString lines;
    for (i = 0; i < dllResult.changesLen; i++) {
        FString line = dllResult.changes[i].varId + FString(": ");
        if (strcmp(dllResult.changes[i].type, "string") == 0) {
            line += dllResult.changes[i].string_result;
        }
        else if (strcmp(dllResult.changes[i].type, "integer") == 0) {
            line += FString::FromInt(dllResult.changes[i].int_result);
        }
        else if (strcmp(dllResult.changes[i].type, "double") == 0) {
            line += FString::SanitizeFloat(dllResult.changes[i].double_result);
        }
        else if (strcmp(dllResult.changes[i].type, "bool") == 0) {
            line += dllResult.changes[i].bool_result ? FString("true") : FString("false");
        }
        line += FString("\n");

        lines += line;
    }*/
    //FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(lines));

    // Clean up allocated memory before returning
    free((char*)dllCode);
    free((char*)dllElId);
    for (i = 0; i < varLength; i++) {
        free((char*)dllVars[i].id);
        free((char*)dllVars[i].name);
        if (dllVars[i].type == VariableType::AW_STRING) {
            free((char*)dllVars[i].string_val);
        }
    }
    delete[] dllVars;
    for (i = 0; i < visitsLength; i++) {
        free((char*)dllVisits[i].elId);
    }
    delete[] dllVisits;

    deallocateOutput(dllResult);

	return result;
}