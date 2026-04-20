#pragma once

// Engine includes
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveConditionData.h"

// Generated include
#include "ArcweaveBranchData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveBranchData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveConditionData IfCondition = FArcweaveConditionData();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveConditionData ElseCondition = FArcweaveConditionData();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConditionData> ElseIfConditions = TArray<FArcweaveConditionData>();

    FArcweaveBranchData()
        : Id(FString(""))
        , IfCondition(FArcweaveConditionData())
        , ElseCondition(FArcweaveConditionData())
        , ElseIfConditions(TArray<FArcweaveConditionData>())
    {}
};