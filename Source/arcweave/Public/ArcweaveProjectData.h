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

    //project cover
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveCoverData Cover = FArcweaveCoverData();

    //project intial variables
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, FArcweaveVariable> CurrentVars = TMap<FString, FArcweaveVariable>();
    
    //project boards
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveBoardData> Boards = TArray<FArcweaveBoardData>();
    /** Records all the components present in the project by their id */
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, FArcweaveComponentData> ComponentsMap;

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
        , Cover(FArcweaveCoverData())
        , CurrentVars(TMap<FString, FArcweaveVariable>())
        , Boards(TArray<FArcweaveBoardData>())
        , Visits(TMap<FString, int>())
    {}
};