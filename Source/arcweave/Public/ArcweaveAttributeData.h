#pragma once

// Engine include
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveAttributeValueData.h"

// Generated include
#include "ArcweaveAttributeData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveAttributeData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString CustomId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString cId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString cType = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveAttributeValueData Value = FArcweaveAttributeValueData();
};
