// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ArcweaveTypes.h"

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

    /** Run Arcscript code using the external library DLL */
	FArcscriptTranspilerOutput RunScript(FString code, FString elementId, TMap<FString, FArcweaveVariable>& initialVars, TMap<FString, int> visits);
	// Additional helper methods can be added here if needed.
};