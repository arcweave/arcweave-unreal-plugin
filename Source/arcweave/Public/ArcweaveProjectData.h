#pragma once

// Arcweave includes
#include "ArcweaveBoardData.h"
#include "ArcweaveComponentData.h"
#include "ArcweaveConditionData.h"
#include "ArcweaveConnectionsData.h"
#include "ArcweaveContents.h"
#include "ArcweaveCoverData.h"
#include "ArcweaveVariable.h"
#include "ArcweaveLocaleData.h"

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
    
    /* Project languages, it can be one so this value is an optional */
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveLocaleData> Locales = TArray<FArcweaveLocaleData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveContents Contents = FArcweaveContents();

    //constructor
    FArcweaveProjectData()
        : Name(FString(""))
        , Cover(FArcweaveCoverData())
        , CurrentVars(TMap<FString, FArcweaveVariable>())
        , Boards(TArray<FArcweaveBoardData>())
        , Components(TArray<FArcweaveComponentData>())
        , Visits(TMap<FString, int>())
        , Locales(TArray<FArcweaveLocaleData>())
        , Contents(FArcweaveContents())
    {}
};