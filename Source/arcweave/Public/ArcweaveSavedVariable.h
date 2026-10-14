#pragma once

#include "CoreMinimal.h"
#include "ArcweaveSavedVariable.generated.h"

/** A variable's mutable value, identified by its stable ID in the snapshot map. */
USTRUCT(BlueprintType)
struct ARCWEAVE_API FArcweaveSavedVariable
{
    GENERATED_BODY()

    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Arcweave")
    FString Type;

    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Arcweave")
    FString Value;
};
