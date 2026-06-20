#pragma once

// Engine includes
#include "CoreMinimal.h"

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
    
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave", meta = (ToolTip = "Component Type"))
    FString cType;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave", meta = (ToolTip = "E.g. board unique id"))
    FString Scope;

	FArcweaveVariable() {
		Id = FString("");
		Name = FString("");
		Type = FString("");
		Value = FString("");
        cType = FString("");
        Scope = FString("");
	}
};