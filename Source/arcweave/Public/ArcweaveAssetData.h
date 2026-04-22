#pragma once

// Engine include
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveCoverData.h"

// Generated include
#include "ArcweaveAssetData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveAssetData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveCoverData Cover = FArcweaveCoverData();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString AudioId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Mode = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Asset = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Delay = FString("");
};