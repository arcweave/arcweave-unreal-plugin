
#pragma once

// Generated include
#include "ArcweaveVariable.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveVariable
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Id;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Name;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Type;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Value;

	FArcweaveVariable() {
		Id = FString("");
		Name = FString("");
		Type = FString("");
		Value = FString("");
	}
};