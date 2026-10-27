// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Plugin includes
#include "ArcweaveComponentData.h"
#include "ArcweaveAssetData.h"
#include "ArcweaveAttributeData.h"
#include "ArcweaveCoverData.h"
#include "ArcweaveProjectData.h"
#include "ArcweaveRuntimeState.h"
#include "ArcweaveConditionData.h"
#include "ArcweaveJumpersData.h"

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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArcweaveFetchCompleted, bool, bSuccess, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnArcweaveStateRestored);
UCLASS()
class ARCWEAVE_API UArcweaveSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
public:
    void FetchDataFromAPI(FString APIToken, FString ProjectHash);

    /** Cancel the pending API import without changing the loaded project. */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    void CancelFetch();

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

    /** Try to get the component data with the Id given for the current project data, returns true if success false otherwise */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    bool TryGetArcweaveComponentById(FArcweaveComponentData& AWComponent, const FString& AWComponentId) const;

    /** Capture completed runtime state. Fails during imports or script callbacks; leaves State unchanged on failure. */
    UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Arcweave|State")
    bool CaptureState(FArcweaveRuntimeState& State, FString& Error) const;

    /** Restore into matching imported content without executing scripts or broadcasting variable changes. */
    UFUNCTION(BlueprintCallable, Category = "Arcweave|State")
    bool RestoreState(const FArcweaveRuntimeState& State, FString& Error);

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
    * Text to show for the connection as an option, as in play mode: the label,
    * else the title of the element it leads to through jumpers and branches,
    * else the start of that element's content, else "[ Empty element ]".
    * Empty when no branch condition on the way holds.
    * Running the label's code can change variables
    */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    FString TranspileConnectionLabel(const FArcweaveConnectionsData& Connection, const FArcweaveBoardData& BoardData);

    /*
    * False when the element has no options, or a single one without label text.
    * Play mode continues to the next element without showing that option.
    * Runs label code and branch conditions without changing variables
    */
    UFUNCTION(BlueprintCallable, Category = "Arcweave")
    bool HasOptions(const FArcweaveElementData& Element, const FArcweaveBoardData& BoardData);

public:
    
	UPROPERTY(BlueprintAssignable, Category = "Arcweave")
	FOnArcweaveResponseReceived OnArcweaveResponseReceived;

    UPROPERTY(BlueprintAssignable, Category = "Arcweave")
    FOnArcweaveVariableChanged OnArcweaveVariableChanged;

    UPROPERTY(BlueprintAssignable, Category = "Arcweave")
    FOnArcweaveArcscriptEventReceived OnArcscriptEventReceived;

    /** API import result, including transport, HTTP and invalid-JSON failures. */
    UPROPERTY(BlueprintAssignable, Category = "Arcweave")
    FOnArcweaveFetchCompleted OnArcweaveFetchCompleted;

    /** The complete snapshot has been restored. Ordinary gameplay change events are not emitted. */
    UPROPERTY(BlueprintAssignable, Category = "Arcweave|State")
    FOnArcweaveStateRestored OnArcweaveStateRestored;

protected:
    //override init function
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
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
    TArray<FString> ParseComponentIds(const TSharedPtr<FJsonObject>& ElementValueObject);
    TMap<FString, FArcweaveComponentData> ParseAllComponents(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveConditionData> ParseAllConditions(const TSharedPtr<FJsonObject>& MainJsonObject);
    TArray<FArcweaveConnectionsData> ParseAllConnections(const TSharedPtr<FJsonObject>& MainJsonObject);
    FArcweaveCoverData ParseCoverData(const TSharedPtr<FJsonObject>& CoverValueObject);
    bool ParseResponse(const FString& ResponseString);
    void OnEventCallback(const char* EventName);
    FArcscriptTranspilerOutput RunTranspiler(const FString& NodeCode, const FString& OriginElementId,
        const TMap<FString, FArcweaveVariable>& InitialVars, const TMap<FString, int>& Visits, bool bShouldUpdateVariables = true);
    void UpdateVariables(const FArcscriptTranspilerOutput& Output);
    FArcweaveElementData ExtractElementData(const TSharedPtr<FJsonObject>& MainJsonObject, const FString& ElementId, FArcweaveBoardData& BoardObjRef);
    void EvaluateCondition(const FArcweaveConditionData& Condition, const FString& OriginElementId,
        FArcscriptTranspilerOutput& TranspilerOutput, bool bShouldUpdateVariables = true);
    FArcscriptTranspilerOutput RunConditionScript(const FString& ConditionId, const FString& OriginElementId,
        bool& Success, bool bShouldUpdateVariables);
    FArcweaveConnectionsData TryGetNExtConnectionData(const FArcweaveBoardData& BoardData, const FArcweaveBranchData& Branch, const FArcweaveConditionData* FiredConditionData);
    void LogTranspilerOutput(const FArcscriptTranspilerOutput& TranspilerOutput);
    bool GetBoardObjectForElement(FString ConditionId, FArcweaveConditionData& OutConditionData, FArcweaveBoardData*& OutBoardObj);
    /* Increment visit counter for the given element id*/
    void IncrementVisits(const FString& ElementId);
    void ResetVisits();
    /** Check if ContentToTest contains code that needs transpiling */
    bool ContainsCodePattern(const FString& ContentToTest) const;
    /**
     * Follow the connection through branches and jumpers to the element it leads to.
     * OutLabel gets the last label text on the way. False when no branch condition holds
     */
    bool ResolveConnectionPath(const FArcweaveConnectionsData& Connection, const FArcweaveBoardData& BoardData,
        const FString& OriginElementId, bool bEvaluateLabel, FString& OutLabel, FArcweaveElementData& OutTarget);
    /** Evaluate the branch's conditions for the element the path started from */
    FGetIsTargetBranchOutput EvaluateBranch(const FArcweaveBoardData& BoardData, const FString& BranchId,
        const FString& OriginElementId, bool bShouldUpdateVariables);
    /** Label text without HTML, running its code without changing variables */
    FString GetLabelText(const FString& Label, const FString& OriginElementId);
    /** Option text for an element when its connection has no label, as in play mode */
    FString GetElementOptionText(const FArcweaveElementData& Element);

    UFUNCTION(BlueprintCallable, Category = "Arcweave | Debug")
    void PrintBranchData(const FArcweaveBranchData &InData);

private:
    friend class FArcweaveAttributeTypesTest;
    friend class FArcweaveComponentBoardVariablesTest;
    friend class FArcweaveConnectionLabelFallbackTest;
    friend class FArcweaveConnectionLabelTest;
    friend class FArcweaveImportFailuresTest;
    friend class FArcweaveRuntimeStateTest;
    friend class FArcweaveStartingElementTest;

    bool CanAccessRuntimeState(FString& Error) const;

    FString ProjectFingerprint;
    bool bIsRunningScript = false;

    FHttpRequestPtr ActiveFetchRequest;

    UPROPERTY()
    FArcweaveProjectData ProjectData = FArcweaveProjectData();
    UPROPERTY()
    FArcweaveBoardData BoardObj = FArcweaveBoardData();

};
