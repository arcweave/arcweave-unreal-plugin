

#pragma once

// Engine include
#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "UObject/SoftObjectPtr.h"

// Arcweave include
#include "ArcweaveCoverData.h"

// Generated include
#include "ArcweaveCoverDataAssetInfo.generated.h"

/**
 *  Class representing the mapping between cover data(the information retrieved from the json) and texture in Unreal Engine.
 */
USTRUCT(BlueprintType)
struct FArcweaveCoverDataAssetInfo
{

    GENERATED_BODY();

    UPROPERTY(EditAnywhere)
    FArcweaveCoverData CoverData;

    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<UTexture2D> Texture;

};
