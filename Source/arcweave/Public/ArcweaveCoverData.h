#pragma once

// Engine include
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveCoverData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveCoverData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString File = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Type = FString("");

    FArcweaveCoverData()
        : Id(FString(""))
        , File(FString(""))
        , Type(FString(""))
    {
    }
};