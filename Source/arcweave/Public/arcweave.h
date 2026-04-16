// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

// Check if ARCWEAVE_API is not defined, then define it as DLL_IMPORT
/*#ifndef ARCWEAVE_API
#define ARCWEAVE_API DLL_IMPORT
#endif*/

#include "ArcweaveTypes.h"
#include "UArcscriptTranspilerWrapper.h"
#include "Modules/ModuleManager.h"
#include "UObject/ObjectMacros.h"

#define ARCWEAVE_SETTINGS_SECTION TEXT("/Script/arcweave.ArcweaveSettings")

class FJsonObject;
DECLARE_LOG_CATEGORY_EXTERN(LogArcwarePlugin, Log, All);

class FarcweaveModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    bool TestJsonFile();

    inline UArcscriptTranspilerWrapper* getArcscriptWrapper() { return ArcscriptWrapper; };
private:
    /** Handle to the test antlr dll we will load */
    void*	ArcscriptTranspilerHandle;

    TMap<FString, FArcweaveVariable> GetInitialVars(TSharedPtr<FJsonObject> JsonObject);
    FString CompareResults(TSharedPtr<FJsonObject> expected, TSharedPtr<FJsonValue> actual);
    TMap<FString, TSharedPtr<FJsonValue>> GetExpectedVars(TSharedPtr<FJsonObject> expectedVarsJson);
    FString CompareVars(const TMap<FString, TSharedPtr<FJsonValue>>& expected, const TMap<FString, TSharedPtr<FJsonValue>>& actual);
	

    UPROPERTY()
    UArcscriptTranspilerWrapper* ArcscriptWrapper = nullptr;

};
