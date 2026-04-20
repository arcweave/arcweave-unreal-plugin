#pragma once

// Engine include
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveAssetData.h"
#include "ArcweaveAttributeData.h"

// Generated include
#include "ArcweaveComponentData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveComponentData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    bool Root = false;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FString> Children = TArray<FString>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveAssetData> Assets = TArray<FArcweaveAssetData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveAttributeData> Attributes = TArray<FArcweaveAttributeData>();

    FArcweaveComponentData()
        : Id(FString(""))
        , Name(FString(""))
        , Root(false)
        , Children(TArray<FString>())
        , Assets(TArray<FArcweaveAssetData>())
        , Attributes(TArray<FArcweaveAttributeData>())
    {
    }
};