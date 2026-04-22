#pragma once

// Engine includes
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveElementData.h"

// Generated include
#include "ArcweaveJumpersData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveJumpersData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveElementData ElementData = FArcweaveElementData();

    FArcweaveJumpersData()
        : Id(FString(""))
        , ElementData(FArcweaveElementData())
    {}
};