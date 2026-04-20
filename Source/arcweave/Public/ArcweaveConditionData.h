#pragma once

// Engine includes
#include "CoreMinimal.h"

#include "ArcweaveConditionData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveConditionData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Output = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Script = FString("");

    FArcweaveConditionData()
        : Output(FString(""))
        , Script(FString(""))
    {}
};