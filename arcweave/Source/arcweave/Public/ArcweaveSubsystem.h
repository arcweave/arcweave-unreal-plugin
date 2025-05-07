// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ArcweaveTypes.h"
#include "ArcweaveSubsystem.generated.h"

struct FArcweaveAPISettings;
class UArcscriptTranspilerWrapper;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArcweaveResponseReceived, const FArcweaveProjectData&, ArcweaveProjectData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArcweaveVariableChanged, const TArray<FArcweaveVariable>&, ArcweaveVariables);
UCLASS()
class ARCWEAVE_API UArcweaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    void FetchDataFromAPI(FString APIToken, FString ProjectHash);
	/*
	 * Fetch the data from Arcweave API
	 */
	UFUNCTION(BlueprintCallable, Category = "Arcweave")
	void FetchData(FString APIToken, FString ProjectHash);
    bool LoadJsonFile();
    /*
	 * Get Arcweave API token from settings
	 */
    UFUNCTION(BlueprintPure, Category = "Arcweave")
    FArcweaveAPISettings LoadArcweaveSettings() const;

    /*
     * Save Arcweave API token to settings
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    void SaveArcweaveSettings(const FString& APIToken, const FString& ProjectHash);

    /*
     * Get Arcweave project data
     */
    UFUNCTION(BlueprintPure, Category = "Arcweave")
    FArcweaveProjectData GetArcweaveProjectData() const {return ProjectData;};

    /*
     * Run transpiler for the element
     * Increase visits counter for the element
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FArcweaveElementData TranspileObject(FString ObjectId, bool& Success, bool bStripHtmlTags = true);

    /*
     * Run transpiler for the connection, labels only for now
     * Increase visits counter for the element
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FArcscriptTranspilerOutput TranspileConnection(
    FString ConnectionId,
    const FString ScriptData,
    bool& Success,
    bool bStripHtmlTags,
    FArcweaveBoardData& BoardObjRef);
    bool GetBoardForConnection(FString ConnectionId, FArcweaveConnectionsData& OutConnection, FArcweaveBoardData*& OutBoardObj);

    /*
     * Run transpiler for the condition
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FArcscriptTranspilerOutput TranspileCondition(FString ConditionId, bool& Success);
    bool GetBoardForObject(FString ObjectId, FArcweaveElementData& OutElement, FArcweaveBoardData*& OutBoardObj);

    /*
     * Sets the current state of the variable
     * This will not change the value in the Arcweave project
     * Be careful with new values, they should be in the same format as the original value
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    void SetVariable(FString Id, FString NewValue);

    /*
     * Check if the target is the branch
     */    
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FGetIsTargetBranchOutput GetIsTargetBranch(const FArcweaveBoardData& BoardData,
    const FArcweaveConnectionsData& TargetConnection);

    /*
     * Get the connections data for the given connection id
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")    
    FArcweaveConnectionsData GetConnectionsData(const FArcweaveBoardData BoardData, const FString& ConnectionId) const;

public:
    
	UPROPERTY(BlueprintAssignable, Category = "Arcweave")
	FOnArcweaveResponseReceived OnArcweaveResponseReceived;

    UPROPERTY(BlueprintAssignable, Category = "Arcweave")
    FOnArcweaveVariableChanged OnArcweaveVariableChanged;

protected:
    //override init function
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    void LogFetchStatus(const bool& Success, const FString& Message);

private:
	void HandleFetch(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
    FString RemoveHtmlTags(const FString& InputString);
    TArray<FArcweaveAssetData> ParseComponentAsset(const TSharedPtr<FJsonObject>& ComponentValueObject);
    TArray<FArcweaveAttributeData> ParseObjectAttributes(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ParentValueObject);
    void ParseAttributeValue(const TSharedPtr<FJsonObject>& ValueObject, FArcweaveAttributeValueData& AttributeValue);
    TArray<FArcweaveBoardData> ParseBoard(const TSharedPtr<FJsonObject>& MainJsonObject);
    TMap<FString, FArcweaveVariable> ParseVariables(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveConnectionsData> ParseConnections(
        const FString& FieldName,
        const TSharedPtr<FJsonObject>& MainJsonObject,
        const TSharedPtr<FJsonObject>& BoardValueObject,
        FArcweaveBoardData& BoardObjRef);
    TArray<FArcweaveElementData> ParseElements(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& BoardObjRef);
    TArray<FArcweaveBranchData> ParseBranches(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj);
    TArray<FArcweaveJumpersData> ParseJumpers(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj);
    FArcweaveConditionData ParseConditionData(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ConditionsObject, const FString& ConditionName, FArcweaveBoardData& OutBoardObj);
    FArcweaveConditionData ParseConditionById(const TSharedPtr<FJsonObject>& MainJsonObject, const FString& ConditionId, FArcweaveBoardData& OutBoardObj);
    TMap<FString, int> InitVisist(const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj);
    TArray<FArcweaveComponentData> ParseComponents(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ElementValueObject);
    TArray<FArcweaveComponentData> ParseAllComponents(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveConditionData> ParseAllConditions(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveConnectionsData> ParseAllConnections(const TSharedPtr<FJsonObject>& MainJsonObject);
    FArcweaveCoverData ParseCoverData(const TSharedPtr<FJsonObject>& CoverValueObject);
    void ParseResponse(const FString& ResponseString);
    FArcscriptTranspilerOutput RunTranspiler(FString Code, FString ElementId, TMap<FString, FArcweaveVariable> InitialVars, TMap<FString, int> Visits);
    FArcweaveElementData ExtractElementData(const TSharedPtr<FJsonObject>& MainJsonObject, const FString& ElementId, FArcweaveBoardData& BoardObjRef);
    void EvaluateCondition(const FArcweaveConditionData& Condition, FArcscriptTranspilerOutput& TranspilerOutput);
    FArcweaveConnectionsData TryGetNExtConnectionData(const FArcweaveBoardData& BoardData, const FArcweaveBranchData& Branch, const FArcweaveConditionData* FiredConditionData);

    FString ExtractDataIdFromConditionScriptString(const FString& ConditionScript);
    void LogTranspilerOutput(const FArcscriptTranspilerOutput& TranspilerOutput);
    bool GetBoardObjectForElement(FString ConditionId, FArcweaveConditionData& OutConditionData, FArcweaveBoardData*& OutBoardObj);
    bool IsScriptVisitsPositive(const FString& ConditionScript);

private:
    UPROPERTY()
    FArcweaveProjectData ProjectData = FArcweaveProjectData();
    UPROPERTY()
    FArcweaveBoardData BoardObj = FArcweaveBoardData();
    /*UPROPERTY()
    FArcweaveAPISettings ArcweaveAPISettings = FArcweaveAPISettings();*/

};