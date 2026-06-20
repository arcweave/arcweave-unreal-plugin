#pragma once

// Engine include
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveAttributeValueData.h"
#include "ArcweaveComponentType.h"

// Generated include
#include "ArcweaveAttributeData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveAttributeData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString cId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    EArcweaveComponentType cType = EArcweaveComponentType::Undefined;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveAttributeValueData Value = FArcweaveAttributeValueData();
};