#pragma once

#include "CoreMinimal.h"
#include "ArcweaveSavedVariable.h"
#include "ArcweaveRuntimeState.generated.h"

/** Runtime state for the same imported project content. Store in the game's USaveGame. */
USTRUCT(BlueprintType)
struct ARCWEAVE_API FArcweaveRuntimeState
{
    GENERATED_BODY()

    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Arcweave")
    int32 FormatVersion = 1;

    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Arcweave")
    FString ProjectFingerprint;

    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, FArcweaveSavedVariable> Variables;

    UPROPERTY(SaveGame, BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, int32> Visits;
};
