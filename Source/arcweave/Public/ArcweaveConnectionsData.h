#pragma once

// Engine includes
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveConnectionsData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveConnectionsData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString Type = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString Label = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString Theme = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString Sourceid = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString Targetid = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString SourceType = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString TargetType = FString("");

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Arcweave")
    FString TargetFace = FString("");

    FArcweaveConnectionsData()
        : Id(FString(""))
        , Type(FString(""))
        , Label(FString(""))
        , Theme(FString(""))
        , Sourceid(FString(""))
        , Targetid(FString(""))
        , SourceType(FString(""))
        , TargetType(FString(""))
        , TargetFace(FString(""))
    {}
};