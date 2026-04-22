#pragma once

// Engine includes
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcscriptVariableChange.h"
#include "ArcscriptInputType.h"

#include "ArcscriptTranspilerOutput.generated.h"

USTRUCT(BlueprintType)
struct FArcscriptTranspilerOutput
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Output;
    
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	TEnumAsByte<FArcscriptInputType> Type;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	TArray<FArcscriptVariableChange> Changes;
    
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	bool ConditionResult;

	FArcscriptTranspilerOutput() {
		Output = FString("");
		Type = FArcscriptInputType::SCRIPT;
		Changes = TArray<FArcscriptVariableChange>();
		ConditionResult = false;
	}
};
