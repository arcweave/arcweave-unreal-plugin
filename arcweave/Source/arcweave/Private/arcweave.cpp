// Copyright Epic Games, Inc. All Rights Reserved.

#include "Arcweave.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"
#include "..\Public\ArcweaveSettings.h"
#include "ISettingsModule.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY(LogArcwarePlugin);

#define LOCTEXT_NAMESPACE "FarcweaveModule"

void FarcweaveModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcware plugin module started!"));

	// Add on the relative location of the third party dll and load it
	FString BaseDir = IPluginManager::Get().FindPlugin("arcweave")->GetBaseDir();
	FString ArcscriptTranspilerPath;
#if PLATFORM_WINDOWS
    FPlatformProcess::AddDllDirectory(*FPaths::Combine(*BaseDir, TEXT("/Source/ThirdParty/ArcscriptTranspiler/x64/Release")));
    ArcscriptTranspilerPath = FPaths::Combine(*BaseDir, TEXT("/Source/ThirdParty/ArcscriptTranspiler/x64/Release/ArcscriptTranspiler.dll"));
#elif PLATFORM_MAC
	//Antlr4LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/arcweaveLibrary/Mac/Release/libExampleLibrary.dylib"));
	#elif PLATFORM_LINUX
	//Antlr4LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/arcweaveLibrary/Linux/x86_64-unknown-linux-gnu/libExampleLibrary.so"));
	#endif // PLATFORM_WINDOWS
	ArcscriptTranspilerHandle = !ArcscriptTranspilerPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*ArcscriptTranspilerPath) : nullptr;

	if (ArcscriptTranspilerHandle)
	{
        // Initialize the UArcscriptTranspilerWrapper instance
        ArcscriptWrapper = NewObject<UArcscriptTranspilerWrapper>();
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Address of ArcscriptWrapper: %p"), (void*)ArcscriptWrapper);
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Antlr4LibraryError", "Failed to load ArcscriptTranspiler.dll"));
	}
#if WITH_EDITOR

	//Project settings arcware
	if (ISettingsModule* SettingModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingModule->RegisterSettings("Project", "Plugins", "Arcweave",
			LOCTEXT("ArcweaveSettingsName", "Arcweave"),
			LOCTEXT("ArcweaveSettingsDescription", "Settings for the Arcweave plugin"),
			GetMutableDefault<UArcweaveSettings>()
		);
	}
#endif
}

void FarcweaveModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcware plugin module shutdown!"));
	// Free the dll handle
	FPlatformProcess::FreeDllHandle(ArcscriptTranspilerHandle);
	ArcscriptTranspilerHandle = nullptr;
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Arcweave");
	}
#endif
}



bool FarcweaveModule::TestJsonFile()
{
	FString BaseDir = IPluginManager::Get().FindPlugin("arcweave")->GetBaseDir();
	FString JsonFilePath = FPaths::Combine(*BaseDir, TEXT("Source/arcweave/test/valid.json"));
	FString JsonRaw;

	// Load the file to a FString
	if (!FFileHelper::LoadFileToString(JsonRaw, *JsonFilePath))
	{
		UE_LOG(LogArcwarePlugin, Log, TEXT("Failed to load JSON file!"));
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonRaw);
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		TMap<FString, FArcweaveVariable> initialVars;
		if (JsonObject->HasField("initialVars"))
		{
			initialVars = GetInitialVars(JsonObject);
		}
		
		const TArray<TSharedPtr<FJsonValue>>* CasesArray = nullptr;
		if (JsonObject->TryGetArrayField("cases", CasesArray))
		{
			for (TSharedPtr<FJsonValue> CaseValue : *CasesArray)
			{
				UE_LOG(LogArcwarePlugin, Log, TEXT("---- Case object ----"));

				TSharedPtr<FJsonObject> CaseObject = CaseValue->AsObject();
				FString code = CaseObject->GetStringField("code");
				if (code.IsEmpty())
				{
					UE_LOG(LogArcwarePlugin, Log, TEXT("//// code field is empty, exiting ///// "));
					return false;
				}
				UE_LOG(LogArcwarePlugin, Log, TEXT("Code: %s"), *code);
				TMap<FString, int> currentVisits;
				FString currentElement = "";

				if (CaseObject->HasField("elementId"))
				{
					currentElement = CaseObject->GetStringField("elementId");
					UE_LOG(LogArcwarePlugin, Log, TEXT("elementId %s"), *currentElement);
				}

				if (CaseObject->HasField("visits"))
				{
					TSharedPtr<FJsonObject> visitsObject = CaseObject->GetObjectField("visits");
	
					for (auto& VisitPair : visitsObject->Values)
					{
						FString Key = VisitPair.Key;
						int32 Value = 0; // Initialize with a default value
						Value = VisitPair.Value->AsNumber();
						currentVisits.Add(Key, Value);
						UE_LOG(LogTemp, Warning, TEXT("Key: %s, Value: %d"), *Key, Value);
					}
				}

				bool hasError = false;
				if (CaseObject->HasField("error"))
				{
					hasError = true;
				}
				FArcscriptTranspilerOutput result;
				bool transpilerFailed = false;
				try {
					result = ArcscriptWrapper->RunScript(code, currentElement, initialVars, currentVisits);
				}
				catch (std::exception& e) {
					transpilerFailed = true;
					UE_LOG(LogArcwarePlugin, Log, TEXT("Test Failed!\n%s"), *FString(e.what()));
					return false;
				}
				// Compare the result (Only applicable in conditions)
				if (CaseObject->HasField("result"))
				{
					bool expectedResult = CaseObject->GetBoolField("result");
					if (result.Type == FArcscriptInputType::CONDITION) {
						if (expectedResult != result.ConditionResult) {
							UE_LOG(LogArcwarePlugin, Log, TEXT("Errors in code:\n%s"), *code);
							UE_LOG(LogArcwarePlugin, Log, TEXT("Expected Condition result different from actual:"));
							UE_LOG(LogArcwarePlugin, Log, TEXT("Expected: %d, Actual: %d"), expectedResult, result.ConditionResult);
						}
					}
				}
				//// Compare the outputs
				if (CaseObject->HasField("output"))
				{
					FString expectedOutput = CaseObject->GetStringField("output");
					if (result.Output != expectedOutput) {
						UE_LOG(LogArcwarePlugin, Log, TEXT("Errors in code:\n%s"), *code);
						UE_LOG(LogArcwarePlugin, Log, TEXT("Expected output different from actual:"));
						UE_LOG(LogArcwarePlugin, Log, TEXT("Expected: \"%s\"\nActual: \"%s\""), *expectedOutput, *result.Output);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogArcwarePlugin, Log, TEXT("Error transpiling arcscript, missing cases field"));
		}
	}
	return false;
}

/**
 * Creates the Variable instances for the variables from the imported JSON.
 * @param initialVarsJson The json object of the initial variable values.
 * @returns A map with the variable ID as key and the Variable instance as value.
*/
TMap<FString, FArcweaveVariable> FarcweaveModule::GetInitialVars(TSharedPtr<FJsonObject> JsonObject) {
	const TSharedPtr<FJsonObject>* InitialVarsObject;
	TMap<FString, FArcweaveVariable> initialVars;

	if (JsonObject->TryGetObjectField("initialVars", InitialVarsObject))
	{
		for (const auto& VarObj : (*InitialVarsObject)->Values)
		{
			FArcweaveVariable var;
			TSharedPtr<FJsonObject> VarObject = VarObj.Value->AsObject();
			if(VarObject.IsValid() && VarObject->HasField("type"))
			{
				var.Id = VarObject->GetStringField("id");
				var.Name = VarObject->GetStringField("name");
				var.Type = VarObject->GetStringField("type");

				if (var.Type == "string") {
					var.Value = VarObject->GetStringField("value");
				}
				else if (var.Type == "integer") {
					var.Value.AppendInt(VarObject->GetIntegerField("value"));
				}
				else if (var.Type == "boolean") {
					var.Value = FString::Printf(TEXT("%s"), VarObject->GetBoolField("value") ? TEXT("true") : TEXT("false"));
				}
				else if (var.Type == "float") {
					var.Value = FString::SanitizeFloat(VarObject->GetNumberField("value"));
				}
				initialVars.Add(var.Id, var);
			}
			else
			{
				UE_LOG(LogArcwarePlugin, Log, TEXT("Error reading initial vars, missing type field"));
			}
		}
	}
	return initialVars;
}

FString FarcweaveModule::CompareResults(TSharedPtr<FJsonObject> expected, TSharedPtr<FJsonValue> actual) {
	FString errors;

	if (!actual.IsValid()) {
		errors += TEXT("Expected result != Actual result:\n");
		errors += TEXT("Expected: ");

		// Serialize the JSON object to an FString
		FString ExpectedJsonString;
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&ExpectedJsonString);
		FJsonSerializer::Serialize(expected.ToSharedRef(), JsonWriter);

		errors += ExpectedJsonString;
		errors += TEXT("\nActual: No Value!\n");
	}
	else if (actual->Type == EJson::String) {
		FString actualStr = actual->AsString();
		FString expectedStr = expected->GetStringField("result");

		if (actualStr != expectedStr) {
			errors += TEXT("Expected result != Actual result:\n");
			errors += TEXT("Expected: ") + expectedStr;
			errors += TEXT("\nActual: ") + actualStr + TEXT("\n");
		}
	}
	else if (actual->Type == EJson::Number) {
		double actualNum = actual->AsNumber();
		double expectedNum = expected->GetNumberField("result");

		if (FMath::Abs(actualNum - expectedNum) > KINDA_SMALL_NUMBER) {
			errors += TEXT("Expected result != Actual result:\n");
			errors += FString::Printf(TEXT("Expected: %f\nActual: %f\n"), expectedNum, actualNum);
		}
	}
	else if (actual->Type == EJson::Boolean) {
		bool actualBool = actual->AsBool();
		bool expectedBool = expected->GetBoolField("result");

		if (actualBool != expectedBool) {
			errors += TEXT("Expected result != Actual result:\n");
			errors += TEXT("Expected: ") + FString(expectedBool ? TEXT("True") : TEXT("False"));
			errors += TEXT("\nActual: ") + FString(actualBool ? TEXT("True") : TEXT("False")) + TEXT("\n");
		}
	}
	else {
		errors += FString::Printf(TEXT("Actual type unknown: %d\n"), static_cast<int32>(actual->Type));
	}

	return errors;
}

/**
 * Creates the map with the expected variables from a certain test
*/
TMap<FString, TSharedPtr<FJsonValue>> FarcweaveModule::GetExpectedVars(TSharedPtr<FJsonObject> expectedVarsJson) {
	TMap<FString, TSharedPtr<FJsonValue>> expectedVars;
	const TMap<FString, TSharedPtr<FJsonValue>>& expectedVarsJsonMap = expectedVarsJson->Values;

	for (const TPair<FString, TSharedPtr<FJsonValue>>& varPair : expectedVarsJsonMap)
	{
		FString key = varPair.Key;
		TSharedPtr<FJsonValue> jsonValue = varPair.Value;

		if (jsonValue->Type == EJson::String)
		{
			expectedVars.Add(key, MakeShareable(new FJsonValueString(jsonValue->AsString())));
		}
		else if (jsonValue->Type == EJson::Boolean)
		{
			expectedVars.Add(key, MakeShareable(new FJsonValueBoolean(jsonValue->AsBool())));
		}
		else if (jsonValue->Type == EJson::Number)
		{
			double dblValue = jsonValue->AsNumber();
			if (FMath::IsNearlyEqual(dblValue, FMath::FloorToDouble(dblValue)))
			{
				expectedVars.Add(key, MakeShareable(new FJsonValueNumber(dblValue)));
			}
			else
			{
				expectedVars.Add(key, MakeShareable(new FJsonValueNumber(dblValue)));
			}
		}
	}
	return expectedVars;
}
/**
 * Compares two maps of variables for their values and types. It ignores the int/double distinction.
 * @param expected The expected variable values
 * @param actual The actual variable values
 * @returns A string containing the output messages of the comparison.
*/
FString FarcweaveModule::CompareVars(const TMap<FString, TSharedPtr<FJsonValue>>& expected, const TMap<FString, TSharedPtr<FJsonValue>>& actual) {
	FString errors;
	bool hasErrors = false;

	for (const auto& pair : expected) {
		FString varId = pair.Key;
		const TSharedPtr<FJsonValue>& expValue = pair.Value;
		const TSharedPtr<FJsonValue>* actValuePtr = actual.Find(varId);
		if (!actValuePtr) {
			hasErrors = true;
			errors += FString::Printf(TEXT("Error in test: var %s not found in actual values.\n"), *varId);
			continue;
		}
		const TSharedPtr<FJsonValue>& actValue = *actValuePtr;

		// Compare integer values
		if (expValue->Type == EJson::Number && FMath::IsNearlyEqual(expValue->AsNumber(), FMath::FloorToDouble(expValue->AsNumber()))) {
			if (actValue->Type == EJson::Number) {
				if (expValue->AsNumber() != actValue->AsNumber()) {
					hasErrors = true;
					errors += FString::Printf(TEXT("Error in test: var %s: Expected: %d, Actual: %d\n"), *varId, FMath::FloorToInt(expValue->AsNumber()), FMath::FloorToInt(actValue->AsNumber()));
				}
			} else {
				hasErrors = true;
				errors += FString::Printf(TEXT("Error in test: var %s: Mismatched types.\n"), *varId);
			}
		}
		// Compare floating point values
		else if (expValue->Type == EJson::Number) {
			if (actValue->Type == EJson::Number) {
				if (!FMath::IsNearlyEqual(expValue->AsNumber(), actValue->AsNumber())) {
					hasErrors = true;
					errors += FString::Printf(TEXT("Error in test: var %s: Expected: %f, Actual: %f\n"), *varId, expValue->AsNumber(), actValue->AsNumber());
				}
			} else {
				hasErrors = true;
				errors += FString::Printf(TEXT("Error in test: var %s: Mismatched types.\n"), *varId);
			}
		}
		// Compare boolean values
		else if (expValue->Type == EJson::Boolean) {
			if (actValue->Type == EJson::Boolean && expValue->AsBool() != actValue->AsBool()) {
				hasErrors = true;
				errors += FString::Printf(TEXT("Error in test: var %s: Expected: %s, Actual: %s\n"), *varId, expValue->AsBool() ? TEXT("true") : TEXT("false"), actValue->AsBool() ? TEXT("true") : TEXT("false"));
			}
		}
		// Compare string values
		else if (expValue->Type == EJson::String) {
			if (actValue->Type == EJson::String && expValue->AsString() != actValue->AsString()) {
				hasErrors = true;
				errors += FString::Printf(TEXT("Error in test: var %s: Expected: %s, Actual: %s\n"), *varId, *expValue->AsString(), *actValue->AsString());
			}
		}
	}

	return errors;
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FarcweaveModule, arcweave)
