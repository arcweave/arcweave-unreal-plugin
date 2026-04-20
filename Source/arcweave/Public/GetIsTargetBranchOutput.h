
#pragma once

// Arcweave includes
#include "ArcweaveConnectionsData.h"
#include "ArcweaveBranchData.h"

// Generated include
#include "GetIsTargetBranchOutput.generated.h"

USTRUCT(BlueprintType)
struct FGetIsTargetBranchOutput
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave", meta = (ToolTip = "Has at least one if condition"))
    bool IsBranch = false;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConnectionsData> BranchConnections = TArray<FArcweaveConnectionsData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    bool BranchConditionResult = false;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveBranchData BranchData = FArcweaveBranchData();

    FGetIsTargetBranchOutput()
        : IsBranch(false)
        , BranchConnections(TArray<FArcweaveConnectionsData>())
        , BranchConditionResult(false)
        , BranchData(FArcweaveBranchData())
    {}
};