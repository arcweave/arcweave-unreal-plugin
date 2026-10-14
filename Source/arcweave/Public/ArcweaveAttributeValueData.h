#pragma once

// Engine include
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveAttributeValueData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveAttributeValueData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Data = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FString> ComponentIds = TArray<FString>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Type = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    bool Plain = false;

    UPROPERTY(BlueprintReadOnly, Category = "Arcweave")
    bool bHasData = false;
};
