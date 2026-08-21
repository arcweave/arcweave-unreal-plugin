

#pragma once


// Engine include
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Containers/Map.h"

// Arcweave include
#include "ArcweaveCoverDataAssetInfo.h"

// Generated include
#include "ArcweaveCoverDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class ARCWEAVE_API UArcweaveCoverDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arcweave | Cover Data")
    TMap<uint32, TSoftObjectPtr<UTexture2D>> CoverDataMap;
};
