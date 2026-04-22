#pragma once

// Engine includes
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveJumpersData.h"
#include "ArcweaveElementData.h"
#include "ArcweaveBranchData.h"
#include "ArcweaveConnectionsData.h"

// Generated include
#include "ArcweaveBoardData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveBoardData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString BoardId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString CustomId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FString> Notes;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveJumpersData> Jumpers;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveElementData>  Elements = TArray<FArcweaveElementData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveBranchData>  Branches = TArray<FArcweaveBranchData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConnectionsData> Connections = TArray<FArcweaveConnectionsData>();

    FArcweaveBoardData()
        : BoardId(FString(""))
        , Name(FString(""))
        , Notes(TArray<FString>())
        , Jumpers(TArray<FArcweaveJumpersData>())
        , Elements(TArray<FArcweaveElementData>())
        , Branches(TArray<FArcweaveBranchData>())
        , Connections(TArray<FArcweaveConnectionsData>())
    {}
};