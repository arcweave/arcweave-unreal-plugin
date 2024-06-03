// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ArcweaveTypes.generated.h"

/**
 * Types for arweave to unreal engine
 */

//struct for dialogue
USTRUCT(BlueprintType)
struct FArcweaveDialogue
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString CharacterName = FString("");

	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString QuestionTitle = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Content = FString("");

	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	TArray<FString> Connections;

	FArcweaveDialogue()
		: CharacterName(FString(""))
		, QuestionTitle(FString(""))
		, Content(FString(""))
		, Connections(TArray<FString>())
	{}
};

USTRUCT(BlueprintType)
struct FArcweaveVariable
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Id;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Name;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Type;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Value;

	FArcweaveVariable() {
		Id = FString("");
		Name = FString("");
		Type = FString("");
		Value = FString("");
	}
};

UENUM(BlueprintType)
enum FArcscriptInputType {
	CONDITION,
	SCRIPT
};

USTRUCT(BlueprintType)
struct FArcscriptVariableChange
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Id;
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Type;
    
	TSharedPtr<FJsonValue> Value;

	FArcscriptVariableChange() {
		Id = FString("");
		Type = FString("");
		Value = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FArcscriptTranspilerOutput
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Output;
    
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	TEnumAsByte<FArcscriptInputType> Type;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	TArray<FArcscriptVariableChange> Changes;
    
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	bool ConditionResult;

	FArcscriptTranspilerOutput() {
		Output = FString("");
		Type = FArcscriptInputType::SCRIPT;
		Changes = TArray<FArcscriptVariableChange>();
		ConditionResult = false;
	}
};
//struct holding all the settings for the plugin
USTRUCT(BlueprintType)
struct FArcweaveAPISettings
{
	GENERATED_BODY()

    /*
     * API token that you can find in your Arcweave account settings.
     */
    UPROPERTY(Config, EditAnywhere, Category = ArcweaveSettings)
    bool EnableRecieveMethodFromLocalJSON = false;

	/*
	 * API token that you can find in your Arcweave account settings.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString APIToken = FString("");

	/*
	 * Project hash that we want to retrieve the information for. You can find it by looking at the URL of your project.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString Hash = FString("");

	FArcweaveAPISettings()
		: EnableRecieveMethodFromLocalJSON(false)
		, APIToken(FString(""))
		, Hash(FString(""))
	{}
};

USTRUCT(BlueprintType)
struct FArcweaveCoverData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");
    
    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString File = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Type = FString("");

    FArcweaveCoverData()
        : Id(FString(""))
        , File(FString(""))
        , Type(FString(""))
    {}
};

USTRUCT(BlueprintType)
struct FArcweaveAssetData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveCoverData Cover = FArcweaveCoverData();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString AudioId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Mode = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Asset = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Delay = FString("");
};

USTRUCT(BlueprintType)
struct FArcweaveAttributeValueData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Data = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Type = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    bool Plain = false;
};

USTRUCT(BlueprintType)
struct FArcweaveAttributeData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString cId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString cType = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveAttributeValueData Value = FArcweaveAttributeValueData();
};

USTRUCT(BlueprintType)
struct FArcweaveComponentData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    bool Root = false;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FString> Children = TArray<FString>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveAssetData> Assets = TArray<FArcweaveAssetData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveAttributeData> Attributes = TArray<FArcweaveAttributeData>();

    FArcweaveComponentData()
        : Id(FString(""))
        , Name(FString(""))
        , Root(false)
        , Children(TArray<FString>())
        , Assets(TArray<FArcweaveAssetData>())
        , Attributes(TArray<FArcweaveAttributeData>())
    {}
};

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

USTRUCT(BlueprintType)
struct FArcweaveConditionData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Output = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Script = FString("");

    FArcweaveConditionData()
        : Output(FString(""))
        , Script(FString(""))
    {}
};

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

USTRUCT(BlueprintType)
struct FArcweaveElementData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Theme = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Title = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Content = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConnectionsData> Outputs = TArray<FArcweaveConnectionsData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveComponentData> Components = TArray<FArcweaveComponentData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, FArcweaveAssetData> Assets;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveAttributeData> Attributes = TArray<FArcweaveAttributeData>();

    FArcweaveElementData()
        : Id(FString(""))
        , Theme(FString(""))
        , Title(FString(""))
        , Content(FString(""))
        , Outputs(TArray<FArcweaveConnectionsData>())
        , Components(TArray<FArcweaveComponentData>())
        , Assets(TMap<FString, FArcweaveAssetData>())
        , Attributes(TArray<FArcweaveAttributeData>())
    {}
};

USTRUCT(BlueprintType)
struct FArcweaveJumpersData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Id = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FArcweaveElementData ElementData = FArcweaveElementData();

    FArcweaveJumpersData()
        : Id(FString(""))
        , ElementData(FArcweaveElementData())
    {}
};

USTRUCT(BlueprintType)
struct FArcweaveBoardData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString BoardId = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    UPROPERTY(BlueprintReadWrite)
    TArray<FString> Notes;

    UPROPERTY(BlueprintReadWrite)
    TArray<FArcweaveJumpersData> Jumpers;

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveElementData>  Elements = TArray<FArcweaveElementData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveBranchData>  Branches = TArray<FArcweaveBranchData>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TMap<FString, int>  Visits =TMap<FString, int>();

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    TArray<FArcweaveConnectionsData> Connections = TArray<FArcweaveConnectionsData>();

    FArcweaveBoardData()
        : BoardId(FString(""))
        , Name(FString(""))
        , Notes(TArray<FString>())
        , Jumpers(TArray<FArcweaveJumpersData>())
        , Elements(TArray<FArcweaveElementData>())
        , Branches(TArray<FArcweaveBranchData>())
        , Visits(TMap<FString, int>())
        , Connections(TArray<FArcweaveConnectionsData>())
    {}
};

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
    
    //constructor
    FArcweaveProjectData()
        : Name(FString(""))
        , Cover(FArcweaveCoverData())
        , CurrentVars(TMap<FString, FArcweaveVariable>())
        , Boards(TArray<FArcweaveBoardData>())
        , Components(TArray<FArcweaveComponentData>())
    {}
};

