#pragma once

// Engine includes
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveConnectionsData.h"
#include "ArcweaveComponentData.h"
#include "ArcweaveAssetData.h"
#include "ArcweaveAttributeData.h"

#include "ArcweaveElementData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveElementData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Theme = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Title = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Content = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConnectionsData> Outputs = TArray<FArcweaveConnectionsData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveComponentData> Components = TArray<FArcweaveComponentData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, FArcweaveAssetData> Assets;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveAttributeData> Attributes = TArray<FArcweaveAttributeData>();

    FArcweaveElementData()
        : Id(FString(""))
        , Theme(FString(""))
        , Title(FString(""))
        , Content(FString(""))
        , Outputs(TArray<FArcweaveConnectionsData>())
        , Components(TArray<FArcweaveComponentData>())
        , Assets(TMap<FString, FArcweaveAssetData>())
        , Attributes(TArray<FArcweaveAttributeData>())
    {}

};