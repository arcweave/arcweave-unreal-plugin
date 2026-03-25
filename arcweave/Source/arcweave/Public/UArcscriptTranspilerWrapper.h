// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Plugin headers
#include "ArcweaveTypes.h"

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include  <functional>

#include "UArcscriptTranspilerWrapper.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogArcweavePlugin, Log, All);
/**
 * 
 */
UCLASS()
class ARCWEAVE_API UArcscriptTranspilerWrapper : public UObject
{
	GENERATED_BODY()
public:

private:

    

public:

	UArcscriptTranspilerWrapper() { };

    /**
    * Executes Arcscript code using the external library DLL.
    *
    * @param code The Arcscript code to execute.
    * @param elementId The ID of the Arcweave element parent of the script execution
    * (e.g. if you want to run a condition code, send the element id of the object from which the condition starts from).
    * @param initialVars A map of variable IDs to their initial values for the script context.
    * @param visits A map tracking the number of visits per element, used for script logic (The code may involve more than one element e.g. visit(node_name)).
    * @param onEvent Callback function invoked when an event occurs during script execution.
    * @return FArcscriptTranspilerOutput containing the result of the script execution, including output, type, variable changes, and condition result.
    */
    FArcscriptTranspilerOutput RunScript(
        const FString& code,
        const FString& elementId,
        const TMap<FString, FArcweaveVariable>& initialVars,
        const TMap<FString, int>& visits,
        std::function<void(const char*)> onEvent
    );
};