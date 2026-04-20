#pragma once

// Engine includes
#include "CoreMinimal.h"
#include "Dom/JsonValue.h"

#include "ArcscriptVariableChange.generated.h"

USTRUCT(BlueprintType)
struct FArcscriptVariableChange
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Id;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Type;
    
	TSharedPtr<FJsonValue> Value;

	FArcscriptVariableChange() {
		Id = FString("");
		Type = FString("");
		Value = nullptr;
	}
};