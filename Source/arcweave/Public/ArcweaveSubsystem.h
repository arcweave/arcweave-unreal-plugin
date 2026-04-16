// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Plugin includes
#include "ArcweaveTypes.h"

// Engine includes
#include "CoreMinimal.h"
#include "EngineGlobals.h"
#include "HAL/FileManager.h"
#include "Interfaces/IHttpRequest.h"
#include "Internationalization/Regex.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Subsystems/EngineSubsystem.h"

#include "ArcweaveSubsystem.generated.h"

struct FArcweaveAPISettings;
class UArcscriptTranspilerWrapper;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArcweaveResponseReceived, const FArcweaveProjectData&, ArcweaveProjectData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArcweaveVariableChanged, const TArray<FArcweaveVariable>&, ArcweaveVariables);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnArcweaveArcscriptEventReceived, const FString&, EventName);
UCLASS()
class ARCWEAVE_API UArcweaveSubsystem : public UEngineSubsystem
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
    UFUNCTION(BlueprintCallable, Category = "Arcweave| Settings")
    void SaveArcweaveSettings(const FString& APIToken, const FString& ProjectHash);

    /*
     * Save Arcweave language preferences to settings
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave| Settings")
    void SaveArcweaveLanguageSettings(bool bUseLocale, bool bFallbackToDefaultLocale, const FString& CustomLocale);

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
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FArcscriptTranspilerOutput TranspileConnection(
        const FString& ConnectionId,
        const FString& ScriptData,
        const FString& OriginElementId,
        bool& Success,
        bool bStripHtmlTags,
        const FArcweaveBoardData& BoardObjRef);
    bool GetBoardForConnection(FString ConnectionId, FArcweaveConnectionsData& OutConnection, FArcweaveBoardData*& OutBoardObj);

    /*
     * Run transpiler for the condition
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FArcscriptTranspilerOutput TranspileCondition(const FString& ConditionId, const FString& OriginElementId, bool& Success);
    bool GetBoardForObject(FString ObjectId, FArcweaveElementData& OutElement, FArcweaveBoardData*& OutBoardObj);
    /* Given a condition Id (e.g. if visit()) gets the corresponding branch id */
    bool GetBranchForObject(FArcweaveBranchData& OutBranch, const FString& ObjectId, const FArcweaveBoardData& InBoardObj) const;

    /*
     * Sets the current state of the variable
     * This will not change the value in the Arcweave project
     * Be careful with new values, they should be in the same format as the original value
     */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    void SetVariable(FString Id, FString NewValue);

    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    void UpdateVariablesFromConnection(const FArcweaveConnectionsData& Connection);

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

    /*
    * Update the label for the connection if contains some code,
    * otherwise fallback to the raw label stored while parsing the content.
    * Warning: Will not update the global variable values
    */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FString TranspileConnectionLabel(const FArcweaveConnectionsData& Connection, const FArcweaveBoardData& BoardData);

public:
    
	UPROPERTY(BlueprintAssignable, Category = "Arcweave")
	FOnArcweaveResponseReceived OnArcweaveResponseReceived;

    UPROPERTY(BlueprintAssignable, Category = "Arcweave")
    FOnArcweaveVariableChanged OnArcweaveVariableChanged;

    UPROPERTY(BlueprintAssignable, Category = "Arcweave")
    FOnArcweaveArcscriptEventReceived OnArcscriptEventReceived;

protected:
    //override init function
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    void LogFetchStatus(const bool& Success, const FString& Message);

private:
 
    /**
     * Adds the language option to the provided API URL if a specific locale is set.
     * This function modifies the ApiUrl string in-place by appending a language query parameter
     * (e.g., "?lang=en" or "&lang=en") based on the DefaultLocale property of the subsystem.
     * If DefaultLocale is empty or already present in the URL, no changes are made.
     *
     * @param ApiUrl The API URL string to which the language option will be added.
     */
    void TryAddLanguageOptionToURL(FString& ApiUrl);
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
    FArcweaveConditionData ParseConditionById(const TSharedPtr<FJsonObject>& MainJsonObject, const FString& ConditionId);
    TMap<FString, int> InitVisits(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveComponentData> ParseComponents(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ElementValueObject);
    TArray<FArcweaveComponentData> ParseAllComponents(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveConditionData> ParseAllConditions(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveConnectionsData> ParseAllConnections(const TSharedPtr<FJsonObject>& MainJsonObject);
    FArcweaveCoverData ParseCoverData(const TSharedPtr<FJsonObject>& CoverValueObject);
    void ParseResponse(const FString& ResponseString);
    void OnEventCallback(const char* EventName);
    FArcscriptTranspilerOutput RunTranspiler(const FString& NodeCode, const FString& OriginElementId,
        const TMap<FString, FArcweaveVariable>& InitialVars, const TMap<FString, int>& Visits, bool bShouldUpdateVariables = true);
    void UpdateVariables(const FArcscriptTranspilerOutput& Output);
    FArcweaveElementData ExtractElementData(const TSharedPtr<FJsonObject>& MainJsonObject, const FString& ElementId, FArcweaveBoardData& BoardObjRef);
    void EvaluateCondition(const FArcweaveConditionData& Condition, const FString& OriginElementId, FArcscriptTranspilerOutput& TranspilerOutput);
    FArcweaveConnectionsData TryGetNExtConnectionData(const FArcweaveBoardData& BoardData, const FArcweaveBranchData& Branch, const FArcweaveConditionData* FiredConditionData);
    void LogTranspilerOutput(const FArcscriptTranspilerOutput& TranspilerOutput);
    bool GetBoardObjectForElement(FString ConditionId, FArcweaveConditionData& OutConditionData, FArcweaveBoardData*& OutBoardObj);
    /* Increment visit counter for the given element id*/
    void IncrementVisits(const FString& ElementId);
    void ResetVisits();
    /** Check if ContentToTest contains code that needs transpiling */
    bool ContainsCodePattern(const FString& ContentToTest) const;

    UFUNCTION(BlueprintCallable, Category = "Arcweave | Debug")
    void PrintBranchData(const FArcweaveBranchData &InData);
private:
    UPROPERTY()
    FArcweaveProjectData ProjectData = FArcweaveProjectData();
    UPROPERTY()
    FArcweaveBoardData BoardObj = FArcweaveBoardData();
    /*UPROPERTY()
    FArcweaveAPISettings ArcweaveAPISettings = FArcweaveAPISettings();*/

};