#pragma once

// Arcweave includes
#include "ArcweaveBoardData.h"
#include "ArcweaveComponentData.h"
#include "ArcweaveVariable.h"
#include "ArcweaveConditionData.h"
#include "ArcweaveConnectionsData.h"
#include "ArcweaveCoverData.h"

// Generated include
#include "ArcweaveProjectData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveProjectData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    /** Authored project starting element; empty when no starting element is set. */
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString StartingElementId = FString("");

    //project cover
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveCoverData Cover = FArcweaveCoverData();

    //project intial variables
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, FArcweaveVariable> CurrentVars = TMap<FString, FArcweaveVariable>();
    
    //project boards
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveBoardData> Boards = TArray<FArcweaveBoardData>();

    //project components
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveComponentData> Components = TArray<FArcweaveComponentData>();

    //project conditions
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConditionData> Conditions = TArray<FArcweaveConditionData>();

    //project connections
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConnectionsData> Connections = TArray<FArcweaveConnectionsData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, int> Visits = TMap<FString, int>();
    
    //constructor
    FArcweaveProjectData()
        : Name(FString(""))
        , StartingElementId(FString(""))
        , Cover(FArcweaveCoverData())
        , CurrentVars(TMap<FString, FArcweaveVariable>())
        , Boards(TArray<FArcweaveBoardData>())
        , Components(TArray<FArcweaveComponentData>())
        , Visits(TMap<FString, int>())
    {}
};
