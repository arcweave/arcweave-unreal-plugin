// Fill out your copyright notice in the Description page of Project Settings.

// File includes
#include "ArcweaveSubsystem.h"

// Arcweave includes
#include "Arcweave.h"
#include "ArcweaveAPISettings.h"
#include "ArcweaveBranchData.h"
#include "ArcweaveConditionData.h"
#include "ArcweaveConnectionsData.h"
#include "ArcweaveSettings.h"
#include "GetIsTargetBranchOutput.h"
#include "UArcscriptTranspilerWrapper.h"

// Engine includes
#include "Dom/JsonObject.h"
#include "Engine/Engine.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "HAL/FileManager.h"
#include "Http.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"

void UArcweaveSubsystem::FetchDataFromAPI(FString APIToken, FString ProjectHash)
{
    FString ApiUrl = FString::Printf(TEXT("https://arcweave.com/api/%s/unreal"), *ProjectHash);
    TryAddLanguageOptionToURL(ApiUrl);

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->SetVerb("GET");
    Request->SetURL(ApiUrl);
    Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *APIToken));
    Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

    // Set the request complete callback
    Request->OnProcessRequestComplete().BindUObject(this, &UArcweaveSubsystem::HandleFetch);

    // Execute the request
    Request->ProcessRequest();
}

void UArcweaveSubsystem::TryAddLanguageOptionToURL(FString& ApiUrl)
{
    const UArcweaveSettings* ArcweaveSettings = GetMutableDefault<UArcweaveSettings>();
    if (!IsValid(ArcweaveSettings))
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("ArcweaveSettings is not valid, cannot add language option to URL"));
        return;
    }

    const FString DefaultLocale = ArcweaveSettings->GetLocale();
    if (ArcweaveSettings->GetUseLocale() && !DefaultLocale.IsEmpty())
    {
        // Ensure the variable can be safely inserted in a URL by encoding it
        FString EscapedDefaultLocale = FGenericPlatformHttp::UrlEncode(DefaultLocale);
        // Add '?' or '&' depending on whether the URL already has query parameters
        if (!ApiUrl.Contains(TEXT("?")))
        {
            ApiUrl += FString::Printf(TEXT("?locale=%s"), *EscapedDefaultLocale);
        }
        else
        {
            ApiUrl += FString::Printf(TEXT("&locale=%s"), *EscapedDefaultLocale);
        }

        if (ArcweaveSettings->GetFallbackToDefaultLocale())
        {
            ApiUrl += TEXT("&fallbackContents=true");
        }
    }
}

void UArcweaveSubsystem::FetchData(FString APIToken, FString ProjectHash)
{
    FArcweaveAPISettings NewArcweaveAPISettings = LoadArcweaveSettings();
    if (NewArcweaveAPISettings.EnableReceiveMethodFromLocalJSON)
    {
        LoadJsonFile();
    }
    else
    {
        FetchDataFromAPI(APIToken, ProjectHash);
    }
}

bool UArcweaveSubsystem::LoadJsonFile()
{
    FString JsonRaw;
    FString DirectoryPath = FPaths::ProjectDir() + TEXT("Content/ArcweaveExport/");
    // Normalize the directory path
    FPaths::NormalizeDirectoryName(DirectoryPath);
    // Get the file manager instance
    IFileManager& FileManager = IFileManager::Get();
    // Find all files in the directory (assuming you want to include files in subdirectories as well)
    TArray<FString> Files;
    FileManager.FindFilesRecursive(Files, *DirectoryPath, TEXT("*.json*"), true, false, false);
    // Log the found files
    for (FString& File : Files)
    {
        // Convert the relative path to an absolute path
        File = FPaths::ConvertRelativePathToFull(File);
        FString Message = FString::Printf(TEXT("Found file: %s"), *File);
        LogFetchStatus(true, Message);
    }
    //always get the 0 one if there are mutiple ones
    if (Files.IsValidIndex(0) == false)
    {
        FString Message = FString::Printf(TEXT("There is no JSON folder in the ArcweaveExport directory!"));
        LogFetchStatus(true, Message);
        return false;
    }
    if (!FFileHelper::LoadFileToString(JsonRaw, *Files[0]))
    {
        FString Message = FString::Printf(TEXT("Failed to load JSON file!"));
        LogFetchStatus(true, Message);
        return false;
    }
    ParseResponse(JsonRaw);
    return true;
}

FArcweaveAPISettings UArcweaveSubsystem::LoadArcweaveSettings() const
{
    FArcweaveAPISettings OutSetttings = FArcweaveAPISettings();
    UArcweaveSettings* ArcweaveSettings = GetMutableDefault<UArcweaveSettings>();
    if (ArcweaveSettings)
    {
        ArcweaveSettings->ReloadConfig();
        if (GConfig)
        {
            if (GConfig->GetBool(ARCWEAVE_SETTINGS_SECTION, TEXT("EnableReceiveMethodFromLocalJSON"), OutSetttings.EnableReceiveMethodFromLocalJSON, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read EnableReceiveMethodFromLocalJSON: %d"), OutSetttings.EnableReceiveMethodFromLocalJSON);
            }

            if (GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, TEXT("APIToken"), OutSetttings.APIToken, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read APIToken: %s"), *OutSetttings.APIToken);
            }

            if (GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, TEXT("Hash"), OutSetttings.Hash, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read Hash: %s"), *OutSetttings.Hash);
            }

            if (GConfig->GetBool(ARCWEAVE_SETTINGS_SECTION, TEXT("bUseLocale"), OutSetttings.bUseLocale, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read bUseLocale: %d"), OutSetttings.bUseLocale);
            }

            if (GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, TEXT("Locale"), OutSetttings.Locale, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read Locale: %s"), *OutSetttings.Locale);
            }

            if (GConfig->GetBool(ARCWEAVE_SETTINGS_SECTION, TEXT("bFallbackToDefaultLocale"), OutSetttings.bFallbackToDefaultLocale, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read bFallbackToDefaultLocale: %d"), OutSetttings.bFallbackToDefaultLocale);
            }
        }
    }
    return OutSetttings;
}

void UArcweaveSubsystem::SaveArcweaveSettings(const FString& APIToken, const FString& ProjectHash)
{
    if (GConfig == nullptr)
    {
        return;
    }

    UArcweaveSettings* ArcweaveSettings = GetMutableDefault<UArcweaveSettings>();
    if (ArcweaveSettings)
    {
        ArcweaveSettings->APIToken = APIToken;
        ArcweaveSettings->Hash = ProjectHash;
        ArcweaveSettings->SaveConfig();
    }
}

void UArcweaveSubsystem::SaveArcweaveLanguageSettings(bool bUseLocale, bool bFallbackToDefaultLocale, const FString& CustomLocale)
{
    if (GConfig == nullptr)
    {
        return;
    }

    UArcweaveSettings* ArcweaveSettings = GetMutableDefault<UArcweaveSettings>();
    check(IsValid(ArcweaveSettings));

    ArcweaveSettings->SetUseLocale(bUseLocale);
    if (bUseLocale)
    {
        ArcweaveSettings->SetFallbackToDefaultLocale(bFallbackToDefaultLocale);
        ArcweaveSettings->SetLocale(CustomLocale);
    }

    ArcweaveSettings->SaveConfig();

}

bool UArcweaveSubsystem::GetBoardObjectForElement(FString ConditionId, FArcweaveConditionData& OutConditionData, FArcweaveBoardData*& OutBoardObj)
{
    for (auto& Board : ProjectData.Boards)
    {
        for (auto& BranchObj : Board.Branches)
        {
            if (BranchObj.IfCondition.Id == ConditionId)
            {
                OutBoardObj = &Board;
                OutConditionData = BranchObj.IfCondition;
                return true;
            }
            else if (BranchObj.ElseCondition.Id == ConditionId)
            {
                OutBoardObj = &Board;
                OutConditionData = BranchObj.ElseCondition;
                return true;
            }
            else
            {
                for (const auto& ElseIfCondition : BranchObj.ElseIfConditions)
                {
                    if (ElseIfCondition.Id == ConditionId)
                    {
                        OutBoardObj = &Board;
                        OutConditionData = ElseIfCondition;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool UArcweaveSubsystem::ContainsCodePattern(const FString& ContentToTest) const
{
    const FRegexPattern CodeBlockPattern(TEXT(R"(<pre><code>[\s\S]*?</code></pre>)"));
    FRegexMatcher Matcher(CodeBlockPattern, ContentToTest);

    return Matcher.FindNext();
}

void UArcweaveSubsystem::IncrementVisits(const FString& ElementId)
{
    if (ElementId.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Cannot increment visits counter for empty object id"));
        return;
    }

    if (ProjectData.Visits.Contains(ElementId))
    {
        ProjectData.Visits[ElementId]++;
    }
    else
    {
        ProjectData.Visits.Add(ElementId, 1);
    }
}

void UArcweaveSubsystem::PrintBranchData(const FArcweaveBranchData& InData)
{
    UE_LOG(LogArcwarePlugin, Display, TEXT("------------- START DEBUG BRANCH DATA-------------"), *InData.Id);
    UE_LOG(LogArcwarePlugin, Display, TEXT("Branch Id: %s"), *InData.Id);
    UE_LOG(LogArcwarePlugin, Display, TEXT("  IfCondition: Id=%s, Output=%s, Script=%s"),
        *InData.IfCondition.Id, *InData.IfCondition.Output, *InData.IfCondition.Script);
    UE_LOG(LogArcwarePlugin, Display, TEXT("  ElseCondition: Id=%s, Output=%s, Script=%s"),
        *InData.ElseCondition.Id, *InData.ElseCondition.Output, *InData.ElseCondition.Script);

    if (InData.ElseIfConditions.Num() > 0)
    {
        for (int32 i = 0; i < InData.ElseIfConditions.Num(); ++i)
        {
            const FArcweaveConditionData& ElseIf = InData.ElseIfConditions[i];
            UE_LOG(LogArcwarePlugin, Display, TEXT("  ElseIfCondition[%d]: Id=%s, Output=%s, Script=%s"),
                i, *ElseIf.Id, *ElseIf.Output, *ElseIf.Script);
        }
    }

    UE_LOG(LogArcwarePlugin, Display, TEXT("------------- END DEBUG BRANCH DATA-------------"), *InData.Id);

}

FString UArcweaveSubsystem::GetFallbackLanguageForLocale(const FString& Locale) const
{
    if (ProjectData.Locales.Num() == 0)
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("No locales found in project data, cannot get fallback language for locale: %s"), *Locale);
        return FString();
    }

    for (const FArcweaveLocaleData& LocaleData : ProjectData.Locales)
    {
        if (LocaleData.Iso == Locale)
        {
            if (LocaleData.HasFallbackLanguage())
            {
                return LocaleData.Base;
            }
            else
            {
                UE_LOG(LogArcwarePlugin, Warning, TEXT("Locale %s does not have a fallback language defined or is the default language"), *Locale);
                return FString();
            }
        }
    }

    UE_LOG(LogArcwarePlugin, Error, TEXT("Cannot get fallback language for locale: %s in the current locales"), *Locale);

    return FString();
}

FArcscriptTranspilerOutput UArcweaveSubsystem::TranspileCondition(const FString& ConditionId, const FString& OriginElementId, bool& Success)
{
    UE_LOG(LogArcwarePlugin, Log, TEXT("----- TranspileCondition for id: %s -----"), *ConditionId);
    Success = false;
    FArcscriptTranspilerOutput Output;
    FArcweaveConditionData ConditionData;
    FArcweaveBoardData* NewBoardObj = nullptr;

    // Rertreive condition data
    if (GetBoardObjectForElement(ConditionId, ConditionData, NewBoardObj) == false)
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Cannot find transpile data for condition id: %s"), *ConditionId);
        return Output;
    }

    if (NewBoardObj->BoardId.IsEmpty() || ConditionData.Id.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Cannot find transpile data for condition id: %s"), *ConditionId);
        return Output;
    }

    try
    {

        //run the transpiler
        FString ScriptModified = FString("<pre><code>") + ConditionData.Script + FString("</code></pre>");
        Output = RunTranspiler(ScriptModified, OriginElementId, ProjectData.CurrentVars, ProjectData.Visits);

        Success = true;
    }
    catch (...)
    {
    }

    return Output;
}

bool UArcweaveSubsystem::GetBoardForObject(FString ElementId, FArcweaveElementData& OutElement, FArcweaveBoardData*& OutBoardObj)
{
    for (auto& Board : ProjectData.Boards)
    {
        for (auto& ElementObj : Board.Elements)
        {
            if (ElementObj.Id == ElementId)
            {
                OutBoardObj = &Board;
                OutElement = ElementObj;
                return true;
            }
        }
    }
    return false;
}

bool UArcweaveSubsystem::GetBoard(FArcweaveBoardData& OutBoardObj, const FString& BoardId)
{
    for (auto& Board : ProjectData.Boards)
    {
            if (Board.BoardId == BoardId)
            {
                OutBoardObj = Board;
                return true;
            }
    }
    return false;
}

bool UArcweaveSubsystem::GetBranchForObject(FArcweaveBranchData& OutBranch, const FString& ObjectId, const FArcweaveBoardData& InBoardObj) const
{
    for (auto& Branch : InBoardObj.Branches)
    {
        if (ObjectId == Branch.IfCondition.Id || ObjectId == Branch.ElseCondition.Id)
        {
            OutBranch = Branch;
            return true;
        }

        for (auto& ElseIfCondition : Branch.ElseIfConditions)
        {
            if (ElseIfCondition.Id == ObjectId)
            {
                OutBranch = Branch;
                return true;
            }
        }
    }

    return false;
}

void UArcweaveSubsystem::SetVariable(FString Id, FString NewValue)
{
    if (Id.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Cannot change the variable wothout the id, exiting"));
        return;
    }
    TArray<FArcweaveVariable> ChangedVariables;
    if (ProjectData.CurrentVars.Contains(Id))
    {
        ProjectData.CurrentVars[Id].Value = NewValue;
        ChangedVariables.Add(ProjectData.CurrentVars[Id]);
        OnArcweaveVariableChanged.Broadcast(ChangedVariables);
    }
    else
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Varible with id: %s, cannot be found in the project variables"), *Id);
    }
}

void UArcweaveSubsystem::EvaluateCondition(const FArcweaveConditionData& Condition, const FString& OriginElementId, FArcscriptTranspilerOutput& TranspilerOutput)
{
    UE_LOG(LogArcwarePlugin, Warning,
        TEXT("Transpiling condition %s..."), *Condition.Id);

    bool bTranspileSucceeded = false;
    TranspilerOutput = TranspileCondition(Condition.Id, OriginElementId, bTranspileSucceeded);

    if (!bTranspileSucceeded)
    {
        UE_LOG(LogArcwarePlugin, Error,
            TEXT("Transpile failed for condition %s"), *Condition.Id);
    }

    //log the result
    if (TranspilerOutput.ConditionResult)
    {
        UE_LOG(LogArcwarePlugin, Log,
            TEXT("Condition %s is true"), *Condition.Id);
    }
    else
    {
        UE_LOG(LogArcwarePlugin, Log,
            TEXT("Condition %s is false"), *Condition.Id);
    }
}

FArcweaveConnectionsData UArcweaveSubsystem::TryGetNExtConnectionData(const FArcweaveBoardData& BoardData,
    const FArcweaveBranchData& Branch, const FArcweaveConditionData* FiredConditionData)
{
    FArcweaveConnectionsData Next = GetConnectionsData(BoardData, FiredConditionData->Output);
    if (Next.Id.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error,
            TEXT("No connection found for branch %s → output %s"),
            *Branch.Id, *FiredConditionData->Output);
    }
    return Next;
}

FGetIsTargetBranchOutput UArcweaveSubsystem::GetIsTargetBranch(
    const FArcweaveBoardData& BoardData,
    const FArcweaveConnectionsData& TargetConnection)
{
    FGetIsTargetBranchOutput Result;

    for (const FArcweaveBranchData& Branch : BoardData.Branches)
    {
        if (Branch.Id != TargetConnection.Targetid)
        {
            continue;
        }

        Result.IsBranch = true;
        Result.BranchData = Branch;
        const FArcweaveConditionData* FiredConditionData = nullptr;
        FArcscriptTranspilerOutput TranspilerOutput = FArcscriptTranspilerOutput();
        EvaluateCondition(Branch.IfCondition, TargetConnection.Sourceid, TranspilerOutput);
        Result.BranchConditionResult = TranspilerOutput.ConditionResult;

        if (Result.BranchConditionResult)
        {
            FiredConditionData = &Branch.IfCondition;
            FArcweaveConnectionsData Next = TryGetNExtConnectionData(BoardData, Branch, FiredConditionData);
            if (!Next.Id.IsEmpty())
            {
                Result.BranchConnections.Add(MoveTemp(Next));
            }
            break;
        }
        else
        {
            for (const auto& ElseIf : Branch.ElseIfConditions)
            {
                EvaluateCondition(ElseIf, TargetConnection.Sourceid, TranspilerOutput);
                if (TranspilerOutput.ConditionResult)
                {
                    FiredConditionData = &ElseIf;
                    break;
                }
            }

            if (!Branch.ElseCondition.Id.IsEmpty())
            {
                if (!FiredConditionData)
                {
                    FiredConditionData = &Branch.ElseCondition;
                }
            }

            if (FiredConditionData)
            {
                FArcweaveConnectionsData Next = TryGetNExtConnectionData(BoardData, Branch, FiredConditionData);
                if (!Next.Id.IsEmpty())
                {
                    Result.BranchConnections.Add(MoveTemp(Next));
                }
                else
                {
                    UE_LOG(LogArcwarePlugin, Warning, TEXT("Connection ID is empty, not adding to BranchConnections"));
                }
            }
            break;
        }

    }

    return Result;
}

FArcweaveConnectionsData UArcweaveSubsystem::GetConnectionsData(const FArcweaveBoardData BoardData, const FString& ConnectionId) const
{
    FArcweaveConnectionsData Result = FArcweaveConnectionsData();
    for (const auto& Connection : BoardData.Connections)
    {
        if (Connection.Id == ConnectionId)
        {
            Result = Connection;
            break;
        }
    }
    return Result;
}

FString UArcweaveSubsystem::TranspileConnectionLabel(const FArcweaveConnectionsData& Connection, const FArcweaveBoardData& BoardData)
{
    bool bSuccess = false;
    FArcscriptTranspilerOutput Output = TranspileConnection(
        Connection.Id,
        Connection.Label,
        Connection.Sourceid,
        bSuccess,
        true,
        BoardData
    );

    if (bSuccess)
    {
        return Output.Output;
    }

    return Connection.Label;
}

bool UArcweaveSubsystem::HasLocales() const
{
    return ProjectData.Locales.Num() > 1;
}

FArcweaveElementData UArcweaveSubsystem::TranspileObject(FString ObjectId, bool& Success, bool bStripHtmlTags /*true*/)
{
    Success = false;
    FArcweaveElementData Element;
    //get the element
    FArcweaveBoardData* NewBoardObj = nullptr;
    if (GetBoardForObject(ObjectId, Element, NewBoardObj) == false)
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Cannot find transpile data for element id: %s"), *ObjectId);
        return Element;
    }

    if (NewBoardObj->BoardId.IsEmpty() || Element.Id.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT(" Cannot find transpile data for element id: %s"), *ObjectId);
        return Element;
    }
    //run the transpiler
    try
    {
        IncrementVisits(Element.Id);

        FArcscriptTranspilerOutput Output = RunTranspiler(Element.Content, Element.Id, ProjectData.CurrentVars, ProjectData.Visits);
        //UE_LOG(LogArcwarePlugin, Log, TEXT("Visits counter for id: %s is: %d"), *ObjectId, NewBoardObj->Visits[ObjectId]);
        if (bStripHtmlTags)
        {
            Element.Content = RemoveHtmlTags(Output.Output);
        }
        else
        {
            Element.Content = Output.Output;
        }
        Success = true;
    }
    catch (...)
    {
    }

    return Element;
}

FArcscriptTranspilerOutput UArcweaveSubsystem::TranspileConnection(
    const FString& ConnectionId,
    const FString& ScriptData,
    const FString& OriginElementId,
    bool& Success,
    bool bStripHtmlTags,
    const FArcweaveBoardData& BoardObjRef)
{
    Success = false;
    FArcscriptTranspilerOutput Output;
    FArcweaveConnectionsData Connection;

    // Validate input parameters
    if (ConnectionId.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("TranspileConnection failed: ConnectionId is empty"));
        return Output;
    }

    if (OriginElementId.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("TranspileConnection failed: OriginElementId is empty"));
        return Output;
    }

    if (ScriptData.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("TranspileConnection failed: ScriptData is empty for connection id: %s"), *ConnectionId);
        return Output;
    }

    if (BoardObjRef.BoardId.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("TranspileConnection failed: BoardObjRef.BoardId is empty for connection id: %s"), *ConnectionId);
        return Output;
    }

    //run the transpiler
    try
    {
        Output = RunTranspiler(ScriptData, OriginElementId, ProjectData.CurrentVars, ProjectData.Visits, true);
        if (bStripHtmlTags)
        {
            Output.Output = RemoveHtmlTags(Output.Output);
        }

        if (!Output.Output.IsEmpty())
        {
            Success = true;
        }
    }
    catch (...)
    {
    }

    return Output;
}

bool UArcweaveSubsystem::GetBoardForConnection(FString ConnectionId, FArcweaveConnectionsData& OutConnection,
    FArcweaveBoardData*& OutBoardObj)
{
    for (auto& Board : ProjectData.Boards)
    {
        for (auto& ConnectionObj : Board.Connections)
        {
            if (ConnectionObj.Id == ConnectionId)
            {
                OutBoardObj = &Board;
                OutConnection = ConnectionObj;
                return true;
            }
        }
    }
    return false;
}

FString UArcweaveSubsystem::RemoveHtmlTags(const FString& InputString)
{
    FString CleanedString = InputString;

    // Search for the opening '<' character in the string
    int32 TagStartIndex = CleanedString.Find(TEXT("<"));

    while (TagStartIndex != INDEX_NONE)
    {
        int32 TagEndIndex = CleanedString.Find(TEXT(">"), ESearchCase::IgnoreCase, ESearchDir::FromStart, TagStartIndex);

        // If both '<' and '>' are found, remove the tag
        if (TagEndIndex != INDEX_NONE)
        {
            CleanedString.RemoveAt(TagStartIndex, TagEndIndex - TagStartIndex + 1, EAllowShrinking::Yes);
            // No need to adjust the TagStartIndex since we've just removed a segment
        }
        else
        {
            // If no matching '>' is found or the string is finished, break the loop
            break;
        }

        TagStartIndex = CleanedString.Find(TEXT("<"));
    }

    return CleanedString;
}

TArray<FArcweaveAssetData> UArcweaveSubsystem::ParseComponentAsset(const TSharedPtr<FJsonObject>& ComponentValueObject)
{
    // Parse "assets" for components as an array of asset data structs
    TArray<FArcweaveAssetData> ComponentAssets;
    const TSharedPtr<FJsonObject>* ComponentAssetsObject;
    if (ComponentValueObject->TryGetObjectField(TEXT("assets"), ComponentAssetsObject))
    {
        FArcweaveAssetData ComponentAsset;
        ComponentAsset.Cover = ParseCoverData(*ComponentAssetsObject);
        ComponentAssets.Add(ComponentAsset);
    }
    return  ComponentAssets;
}

TArray<FArcweaveAttributeData> UArcweaveSubsystem::ParseObjectAttributes(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ParentValueObject)
{
    TArray<FArcweaveAttributeData> ObjectAttributes;
    TArray<FString> AttributesStringArray;
    if (ParentValueObject->TryGetStringArrayField(TEXT("attributes"), AttributesStringArray))
    {
        for (const auto& AttributeAssetId : AttributesStringArray)
        {
            FArcweaveAttributeData AttributeAsset;
            // Iterate through the array of attributes and find with this id
            const TSharedPtr<FJsonObject>* AttributesObject;
            if (MainJsonObject->TryGetObjectField(TEXT("attributes"), AttributesObject))
            {
                for (const auto& AttrPair : AttributesObject->Get()->Values)
                {
                    FArcweaveAttributeData AttributeData;
                    AttributeData.Id = AttrPair.Key;

                    if (AttributeAssetId == AttributeData.Id)
                    {
                        const TSharedPtr<FJsonObject> AttributeAssetValueObject = AttrPair.Value->AsObject();
                        if (AttributeAssetValueObject.IsValid())
                        {
                            // Extract the "cId", "name", and "cType"
                            AttributeAssetValueObject->TryGetStringField(TEXT("cId"), AttributeAsset.cId);
                            AttributeAssetValueObject->TryGetStringField(TEXT("name"), AttributeAsset.Name);
                            AttributeAssetValueObject->TryGetStringField(TEXT("cType"), AttributeAsset.cType);

                            // Parse "value" as FArcweaveAttributeValueData
                            const TSharedPtr<FJsonObject>* AttributeValueObject;
                            if (AttributeAssetValueObject->TryGetObjectField(TEXT("value"), AttributeValueObject))
                            {
                                ParseAttributeValue(*AttributeValueObject, AttributeAsset.Value);
                            }
                        }
                        ObjectAttributes.Add(AttributeAsset);
                    }
                }
            }
        }
    }
    return ObjectAttributes;
}

void UArcweaveSubsystem::ParseAttributeValue(const TSharedPtr<FJsonObject>& ValueObject, FArcweaveAttributeValueData& AttributeValue)
{
    ValueObject->TryGetStringField(TEXT("type"), AttributeValue.Type);
    if (AttributeValue.Type == TEXT("component-list"))
    {
        const TArray<TSharedPtr<FJsonValue>>* ComponentIds = nullptr;
        ValueObject->TryGetArrayField(TEXT("data"), ComponentIds);
        for (const auto& ComponentId : *ComponentIds)
        {
            AttributeValue.ComponentIds.Add(ComponentId->AsString());
        }
    }
    else
    {
        ValueObject->TryGetStringField(TEXT("data"), AttributeValue.Data);
        ValueObject->TryGetBoolField(TEXT("plain"), AttributeValue.Plain);
    }
}

TArray<FArcweaveBoardData> UArcweaveSubsystem::ParseBoard(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    TArray<FArcweaveBoardData> Boards;
    const TSharedPtr<FJsonObject>* BoardsObject;
    if (MainJsonObject->TryGetObjectField(TEXT("boards"), BoardsObject))
    {
        for (const auto& BoardPair : BoardsObject->Get()->Values)
        {
            const TSharedPtr<FJsonObject> BoardValueObject = BoardPair.Value->AsObject();
            FArcweaveBoardData Board;
            Board.BoardId = BoardPair.Key;

            if (!BoardValueObject->TryGetStringField(TEXT("name"), Board.Name))
            {
                UE_LOG(LogArcwarePlugin, Error, TEXT("Board name not found for board %s"), *Board.BoardId);
            }
            if (BoardValueObject->TryGetStringField(TEXT("customId"), Board.CustomId))
            {
                UE_LOG(LogArcwarePlugin, Log, TEXT("Custom id for board %s is: %s"), *Board.BoardId, *Board.CustomId);
            }

            Board.Elements = ParseElements(MainJsonObject, BoardValueObject, Board);
            Board.Branches = ParseBranches(MainJsonObject, BoardValueObject, Board);
            Board.Jumpers = ParseJumpers(MainJsonObject, BoardValueObject, Board);
            Board.Connections = ParseConnections(FString("connections"), MainJsonObject, BoardValueObject, Board);
            Boards.Add(Board);
        }
    }
    return Boards;
}

TMap<FString, FArcweaveVariable> UArcweaveSubsystem::ParseVariables(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    TMap<FString, FArcweaveVariable> InitialVars;
    if (ProjectData.Boards.IsEmpty())
    {
        UE_LOG(LogArcweavePlugin, Error, TEXT("Boards should be parsed before variables because they contains references to them \n"));
        return InitialVars;
    }

    const TSharedPtr<FJsonObject>* VariablesObject;
    if (MainJsonObject->TryGetObjectField(TEXT("variables"), VariablesObject))
    {
        for (const auto& VariablePair : VariablesObject->Get()->Values)
        {
            const TSharedPtr<FJsonObject> VarObject = VariablePair.Value->AsObject();
            bool isRoot = false;
            if (!(VarObject->TryGetBoolField(TEXT("root"), isRoot) && isRoot)) {
                FArcweaveVariable Variable;
                Variable.Id = VariablePair.Key;
                VarObject->TryGetStringField(TEXT("name"), Variable.Name);
                VarObject->TryGetStringField(TEXT("type"), Variable.Type);
                if (Variable.Type == "string") {
                    Variable.Value = VarObject->GetStringField(TEXT("value"));
                }
                else if (Variable.Type == "integer") {
                    Variable.Value.AppendInt(VarObject->GetIntegerField(TEXT("value")));
                }
                else if (Variable.Type == "boolean") {
                    Variable.Value = FString::Printf(TEXT("%s"), VarObject->GetBoolField(TEXT("value")) ? TEXT("true") : TEXT("false"));
                }
                else if (Variable.Type == "float")
                {
                    Variable.Value = FString::SanitizeFloat(VarObject->GetNumberField(TEXT("value")));
                }

                if (VarObject->TryGetStringField(TEXT("cType"), Variable.cType))
                {
                    if (Variable.cType == "boards")
                    {
                        FString ComponentId;
                        if (!VarObject->TryGetStringField(TEXT("cId"), ComponentId))
                        {
                            UE_LOG(LogArcweavePlugin, Error, TEXT("The value cId should be present in var with id: %s"), *Variable.Id);
                            continue;
                        }


                        FString BoardCustomId = FString("");
                        for (FArcweaveBoardData Board : ProjectData.Boards)
                        {
                            if (Board.BoardId == ComponentId)
                            {
                                BoardCustomId = Board.CustomId;
                                break;
                            }
                        }

                        if (BoardCustomId.IsEmpty())
                        {
                            UE_LOG(LogArcweavePlugin, Error, TEXT("Cannot find the board with id: %s for variable with id: %s"), *ComponentId, *Variable.Id);
                            continue;
                        }

                        Variable.Scope = BoardCustomId;
                    }

                }
                InitialVars.Add(Variable.Id, Variable);

            }
        }
    }
    return InitialVars;
}

TArray<FArcweaveConnectionsData> UArcweaveSubsystem::ParseConnections(const FString& FieldName,
    const TSharedPtr<FJsonObject>& MainJsonObject,
    const TSharedPtr<FJsonObject>& ParentValueObject,
    FArcweaveBoardData& BoardObjRef)
{
    // Parse "connections" as an array of connection data structs
    TArray<FArcweaveConnectionsData> Connections;
    TArray<FString> ConnectionsArrayStrings;

    FString DesiredLocale = FString("");
    bool bFallbackToDefaultLanguage = false;
    GetLanguageSettings(DesiredLocale, bFallbackToDefaultLanguage);

    if (ParentValueObject->TryGetStringArrayField(FieldName, ConnectionsArrayStrings))
    {
        for (const FString& ConnectionId : ConnectionsArrayStrings)
        {
            // Extract connections
            const TSharedPtr<FJsonObject>* ConnectionsObject;
            if (MainJsonObject->TryGetObjectField(TEXT("connections"), ConnectionsObject))
            {
                for (const auto& ConnectionPair : ConnectionsObject->Get()->Values)
                {
                    if (ConnectionPair.Key == ConnectionId)
                    {
                        FArcweaveConnectionsData Connection;
                        Connection.Id = ConnectionPair.Key;
                        const TSharedPtr<FJsonObject> ConObject = ConnectionPair.Value->AsObject();

                        if (ConObject.IsValid())
                        {
                            FString RawLabel = FString("");

                            if (HasLocales())
                            {
                                RawLabel = GetTranslatedContent(ConnectionId, TEXT("label"), DesiredLocale, bFallbackToDefaultLanguage);
                            }
                            else 
                            {
                                ConObject->TryGetStringField(TEXT("label"), RawLabel);
                            }

                            if (!RawLabel.IsEmpty())
                            {
                                if (ContainsCodePattern(RawLabel))
                                {
                                    // Keep the raw code so it can be analysed later
                                    Connection.Label = RawLabel;
                                }
                                else
                                {
                                    // no code: html tag can be removed
                                    Connection.Label = RemoveHtmlTags(RawLabel);
                                }
                            }
                            else
                            {
                                UE_LOG(LogArcwarePlugin, Warning, TEXT("No label text was provided for connection with ID: %s"), *ConnectionId);
                            }


                            ConObject->TryGetStringField(TEXT("type"), Connection.Type);
                            ConObject->TryGetStringField(TEXT("theme"), Connection.Theme);
                            ConObject->TryGetStringField(TEXT("sourceid"), Connection.Sourceid);
                            ConObject->TryGetStringField(TEXT("targetid"), Connection.Targetid);
                            ConObject->TryGetStringField(TEXT("sourceType"), Connection.SourceType);
                            ConObject->TryGetStringField(TEXT("targetType"), Connection.TargetType);
                            //LogStructFields(&Connection, FArcweaveConnectionsData::StaticStruct());
                        }
                        Connections.Add(Connection);
                    }
                }
            }
        }
    }
    return Connections;
}

TArray<FArcweaveElementData> UArcweaveSubsystem::ParseElements(
    const TSharedPtr<FJsonObject>& MainJsonObject,
    const TSharedPtr<FJsonObject>& BoardValueObject,
    FArcweaveBoardData& BoardObjRef)
{
    TArray<FArcweaveElementData> Elements;
    // Parse "elements" as an array of element data structs
    TArray<FString> ElementArrayStrings;
    if (BoardValueObject->TryGetStringArrayField(TEXT("elements"), ElementArrayStrings))
    {
        //then search for the element pairs
        for (const FString& ElementId : ElementArrayStrings)
        {
            FArcweaveElementData Element = ExtractElementData(MainJsonObject, ElementId, BoardObjRef);
            Elements.Add(Element);
        }
    }
    return Elements;
}

TArray<FArcweaveBranchData> UArcweaveSubsystem::ParseBranches(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj)
{
    TArray<FArcweaveBranchData> Branches;
    TArray<FString> BranchesArrayStrings;
    if (BoardValueObject->TryGetStringArrayField(TEXT("branches"), BranchesArrayStrings))
    {
        //then search for the element pairs
        for (const FString& BranchId : BranchesArrayStrings)
        {
            // Extract branches
            const TSharedPtr<FJsonObject>* BranchObject;
            if (MainJsonObject->TryGetObjectField(TEXT("branches"), BranchObject))
            {
                // Iterate through the "branches" object
                for (const auto& BranchPair : BranchObject->Get()->Values)
                {
                    if (BranchPair.Key == BranchId)
                    {
                        FArcweaveBranchData Branch = FArcweaveBranchData();
                        Branch.Id = BranchPair.Key;
                        const TSharedPtr<FJsonObject>& BranchDataObject = BranchPair.Value->AsObject();

                        // Extract "conditions" object
                        const TSharedPtr<FJsonObject>& ConditionsObject = BranchDataObject->GetObjectField(TEXT("conditions"));

                        // Extract "ifCondition"
                        Branch.IfCondition = ParseConditionData(MainJsonObject, ConditionsObject, FString("ifCondition"), OutBoardObj);
                        Branch.ElseCondition = ParseConditionData(MainJsonObject, ConditionsObject, FString("elseCondition"), OutBoardObj);

                        // Extract "elseIfConditions" array
                        const TArray<TSharedPtr<FJsonValue>>* ElseIfConditionsArray = nullptr;
                        if (ConditionsObject->TryGetArrayField(TEXT("elseIfConditions"), ElseIfConditionsArray))
                        {
                            for (const auto& ElseIfValue : *ElseIfConditionsArray)
                            {
                                FString ElseIfId = ElseIfValue->AsString();
                                FArcweaveConditionData ElseIfData = ParseConditionById(MainJsonObject, ElseIfId);

                                Branch.ElseIfConditions.Add(MoveTemp(ElseIfData));
                            }
                        }

                        // Add the parsed branch data to the map
                        Branches.Add(Branch); // Add the branch to the array
                    }
                }
            }
        }
    }
    return Branches;
}

FArcweaveConditionData UArcweaveSubsystem::ParseConditionById(
    const TSharedPtr<FJsonObject>& MainJsonObject,
    const FString& ConditionId)
{
    FArcweaveConditionData ConditionData;
    ConditionData.Id = ConditionId;

    // Pull out the "conditions" block from the root
    const TSharedPtr<FJsonObject>* ConditionsRoot = nullptr;
    if (!MainJsonObject->TryGetObjectField(TEXT("conditions"), ConditionsRoot))
    {
        return ConditionData;
    }

    if (const TSharedPtr<FJsonValue>* Found = ConditionsRoot->Get()->Values.Find(ConditionId))
    {
        const TSharedPtr<FJsonObject>& Obj = (*Found)->AsObject();

        FString Output;
        if (Obj->TryGetStringField(TEXT("output"), Output))
            ConditionData.Output = Output.IsEmpty() ? TEXT("empty") : Output;

        FString Script;
        if (Obj->TryGetStringField(TEXT("script"), Script))
            ConditionData.Script = Script.IsEmpty() ? TEXT("empty") : Script;
    }

    return ConditionData;
}


TArray<FArcweaveJumpersData> UArcweaveSubsystem::ParseJumpers(const TSharedPtr<FJsonObject>& MainJsonObject,
    const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj)
{
    TArray<FArcweaveJumpersData> Jumpers;
    TArray<FString> JumpersArrayStrings;
    if (BoardValueObject->TryGetStringArrayField(TEXT("jumpers"), JumpersArrayStrings))
    {
        //then search for the elements for jumpers
        for (const FString& JumperId : JumpersArrayStrings)
        {
            // Extract jumpers
            const TSharedPtr<FJsonObject>* JumperObject;
            if (MainJsonObject->TryGetObjectField(TEXT("jumpers"), JumperObject))
            {
                // Iterate through the "jumpers" object
                for (const auto& JumperPair : JumperObject->Get()->Values)
                {
                    if (JumperPair.Key == JumperId)
                    {
                        FArcweaveJumpersData Jumper = FArcweaveJumpersData();
                        Jumper.Id = JumperPair.Key;
                        const TSharedPtr<FJsonObject>& JumperDataObject = JumperPair.Value->AsObject();

                        if (JumperDataObject.IsValid())
                        {
                            FString ElementId = FString("");
                            JumperDataObject->TryGetStringField(TEXT("elementId"), ElementId);
                            FArcweaveElementData Element = ExtractElementData(MainJsonObject, ElementId, OutBoardObj);
                            Jumper.ElementData = Element;
                        }
                        Jumpers.Add(Jumper);
                    }
                }
            }
        }
    }
    return Jumpers;
}

FArcweaveElementData UArcweaveSubsystem::ExtractElementData(
    const TSharedPtr<FJsonObject>& MainJsonObject,
    const FString& ElementId,
    FArcweaveBoardData& BoardObjRef)
{
    FArcweaveElementData Element;
    const TSharedPtr<FJsonObject>* ElementsObject;

    FString DesiredLocale = FString("");
    bool bFallbackToDefaultLanguage = false;
    GetLanguageSettings(DesiredLocale, bFallbackToDefaultLanguage);

    if (MainJsonObject->TryGetObjectField(TEXT("elements"), ElementsObject))
    {
        for (const auto& ElementPair : ElementsObject->Get()->Values)
        {
            if (ElementPair.Key == ElementId)
            {
                Element.Id = ElementPair.Key;
                const TSharedPtr<FJsonObject> ElementValueObject = ElementPair.Value->AsObject();

                if (ElementValueObject.IsValid())
                {
                    //inti visits object for the transpiler

                    //get the values from the json object
                    ElementValueObject->TryGetStringField(TEXT("theme"), Element.Theme);
                    
                    FString DirtyTitle = FString("");

                    if (HasLocales()) 
                    {
                        DirtyTitle = GetTranslatedContent(Element.Id, TEXT("title"), DesiredLocale, bFallbackToDefaultLanguage);
                        Element.Content = GetTranslatedContent(Element.Id, TEXT("content"), DesiredLocale, bFallbackToDefaultLanguage);
                    }
                    else
                    {
                        ElementValueObject->TryGetStringField(TEXT("title"), DirtyTitle);
                        ElementValueObject->TryGetStringField(TEXT("content"), Element.Content);
                    }

                    Element.Title = RemoveHtmlTags(DirtyTitle);
                    //FArcscriptTranspilerOutput Output = RunTranspiler(DirtyContent, Element.Id, ProjectData.InitialVars, BoardObj.Visits);
                    Element.Outputs = ParseConnections(FString("outputs"), MainJsonObject, ElementValueObject, BoardObjRef);
                    Element.Components = ParseComponents(MainJsonObject, ElementValueObject);
                    Element.Attributes = ParseObjectAttributes(MainJsonObject, ElementValueObject);
                }
            }
        }
    }
    return Element;
}

FArcweaveConditionData UArcweaveSubsystem::ParseConditionData(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ConditionsObject, const FString& ConditionName, FArcweaveBoardData& OutBoardObj)
{
    FArcweaveConditionData ConditionData = FArcweaveConditionData();
    FString IfConditionOutputId = FString("");
    if (ConditionsObject->TryGetStringField(ConditionName, IfConditionOutputId))
    {
        const TSharedPtr<FJsonObject>* ConditionsObjectField;
        if (MainJsonObject->TryGetObjectField(TEXT("conditions"), ConditionsObjectField))
        {
            // Iterate through the "branches" object
            for (const auto& ConditionPair : ConditionsObjectField->Get()->Values)
            {
                if (ConditionPair.Key == IfConditionOutputId)
                {
                    const TSharedPtr<FJsonObject>& ConditionDataObject = ConditionPair.Value->AsObject();
                    ConditionData.Id = ConditionPair.Key;
                    //output
                    FString Output = FString("");
                    if (ConditionDataObject->TryGetStringField(TEXT("output"), Output))
                    {
                        if (Output.IsEmpty())
                        {
                            ConditionData.Output = FString("empty");
                        }
                        else
                        {
                            ConditionData.Output = Output;
                        }

                    }
                    //script
                    FString Script = FString("");
                    if (ConditionDataObject->TryGetStringField(TEXT("script"), Script))
                    {
                        if (Script.IsEmpty())
                        {
                            ConditionData.Script = FString("empty");
                        }
                        else
                        {
                            ConditionData.Script = Script;
                        }
                    }
                }
            }
        }
    }
    return ConditionData;
}


TMap<FString, int> UArcweaveSubsystem::InitVisits(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    //add the visits to the board data
    TMap<FString, int> AllVisits;
    const TSharedPtr<FJsonObject>* ElementsObject;
    if (MainJsonObject->TryGetObjectField(TEXT("elements"), ElementsObject))
    {
        for (const auto& ElementPair : ElementsObject->Get()->Values)
        {
            AllVisits.Add(ElementPair.Key, 0);
        }
    }
    const TSharedPtr<FJsonObject>* ConnectionsObject;
    if (MainJsonObject->TryGetObjectField(TEXT("connections"), ConnectionsObject))
    {
        for (const auto& ConnectionPair : ConnectionsObject->Get()->Values)
        {
            AllVisits.Add(ConnectionPair.Key, 0);
        }
    }
    const TSharedPtr<FJsonObject>* BranchesObject;
    if (MainJsonObject->TryGetObjectField(TEXT("branches"), BranchesObject))
    {
        for (const auto& BranchPair : BranchesObject->Get()->Values)
        {
            AllVisits.Add(BranchPair.Key, 0);
        }
    }

    const TSharedPtr<FJsonObject>* ConditionsObject;
    if (MainJsonObject->TryGetObjectField(TEXT("conditions"), ConditionsObject))
    {
        for (const auto& ConditionPair : ConditionsObject->Get()->Values)
        {
            AllVisits.Add(ConditionPair.Key, 0);
        }
    }

    const TSharedPtr<FJsonObject>* JumpersObject;
    if (MainJsonObject->TryGetObjectField(TEXT("jumpers"), JumpersObject))
    {
        for (const auto& JumperPair : JumpersObject->Get()->Values)
        {
            AllVisits.Add(JumperPair.Key, 0);
        }
    }

    return AllVisits;
}

TArray<FArcweaveComponentData> UArcweaveSubsystem::ParseComponents(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ElementValueObject)
{
    // Parse "components" as an array of component data structs
    TArray<FArcweaveComponentData> Components;
    TArray<FString> ComponentsStringArray;
 
    FString DesiredLocale = FString("");
    bool bFallbackToDefaultLanguage = false;
    GetLanguageSettings(DesiredLocale, bFallbackToDefaultLanguage);

    if (ElementValueObject->TryGetStringArrayField(TEXT("components"), ComponentsStringArray))
    {
        for (const auto& ComponentId : ComponentsStringArray)
        {
            // Iterate through the array of components and find with this id
            const TSharedPtr<FJsonObject>* CompObject;
            if (MainJsonObject->TryGetObjectField(TEXT("components"), CompObject))
            {
                for (const auto& CompPair : CompObject->Get()->Values)
                {
                    if (CompPair.Key == ComponentId)
                    {
                        FArcweaveComponentData ElComponent;
                        ElComponent.Id = CompPair.Key;
                        const TSharedPtr<FJsonObject> ComponentValueObject = CompPair.Value->AsObject();

                        if (ComponentValueObject.IsValid())
                        {
                            // If it has locale the content has been already saved in contents, so we just need to retrieve it
                            if (HasLocales())
                            {
                                ElComponent.Name = GetTranslatedContent(ElComponent.Id, TEXT("name"), DesiredLocale, bFallbackToDefaultLanguage);
                            }
                            else
                            {
                                ComponentValueObject->TryGetStringField(TEXT("name"), ElComponent.Name);
                            }

                            ComponentValueObject->TryGetBoolField(TEXT("root"), ElComponent.Root);
                            ComponentValueObject->TryGetStringArrayField(TEXT("children"), ElComponent.Children);
                            ElComponent.Assets = ParseComponentAsset(ComponentValueObject);
                            ElComponent.Attributes = ParseObjectAttributes(MainJsonObject, ComponentValueObject);

                            Components.Add(ElComponent);
                        }
                    }
                }
            }
        }
    }
    return Components;
}

TArray<FArcweaveComponentData> UArcweaveSubsystem::ParseAllComponents(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    // Parse "components" as an array of component data structs
    TArray<FArcweaveComponentData> Components;
    // Iterate through the array of components and find with this id
    const TSharedPtr<FJsonObject>* CompObject;
    if (MainJsonObject->TryGetObjectField(TEXT("components"), CompObject))
    {
        // Get settings 
        FString DesiredLocale = FString("");
        bool bFallbackToDefaultLanguage = false;
        GetLanguageSettings(DesiredLocale, bFallbackToDefaultLanguage);

        for (const auto& CompPair : CompObject->Get()->Values)
        {
            FArcweaveComponentData ElComponent;
            ElComponent.Id = CompPair.Key;
            const TSharedPtr<FJsonObject> ComponentValueObject = CompPair.Value->AsObject();

            // Extract the "name" and "root"
            if (ComponentValueObject.IsValid())
            {
                if (HasLocales())
                {
                    ElComponent.Name = GetTranslatedContent(CompPair.Key, TEXT("name"), DesiredLocale, bFallbackToDefaultLanguage);
                }
                else
                {
                    ComponentValueObject->TryGetStringField(TEXT("name"), ElComponent.Name);
                }
                ComponentValueObject->TryGetBoolField(TEXT("root"), ElComponent.Root);
                ComponentValueObject->TryGetStringArrayField(TEXT("children"), ElComponent.Children);
                ElComponent.Assets = ParseComponentAsset(ComponentValueObject);
                ElComponent.Attributes = ParseObjectAttributes(MainJsonObject, ComponentValueObject);

                Components.Add(ElComponent);
            }
        }
    }
    return Components;
}

TArray<FArcweaveConditionData> UArcweaveSubsystem::ParseAllConditions(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    TArray<FArcweaveConditionData> Conditions;
    const TSharedPtr<FJsonObject>* CondObject;
    if (MainJsonObject->TryGetObjectField(TEXT("conditions"), CondObject))
    {
        for (const auto& CompPair : CondObject->Get()->Values)
        {
            FArcweaveConditionData ConditionData;
            ConditionData.Id = CompPair.Key;
            const TSharedPtr<FJsonObject> ComponentValueObject = CompPair.Value->AsObject();

            if (ComponentValueObject.IsValid())
            {
                ComponentValueObject->TryGetStringField(TEXT("output"), ConditionData.Output);
                ComponentValueObject->TryGetStringField(TEXT("script"), ConditionData.Script);
                Conditions.Add(ConditionData);
            }
        }
    }
    return Conditions;
}

TArray<FArcweaveConnectionsData> UArcweaveSubsystem::ParseAllConnections(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    FString DesiredLocale = FString("");
    bool bFallbackToDefaultLanguage = false;
    GetLanguageSettings(DesiredLocale, bFallbackToDefaultLanguage);

    TArray<FArcweaveConnectionsData> Connections;
    const TSharedPtr<FJsonObject>* CondObject;
    if (MainJsonObject->TryGetObjectField(TEXT("connections"), CondObject))
    {
        
        for (const auto& CompPair : CondObject->Get()->Values)
        {
            FArcweaveConnectionsData ConditionData;
            ConditionData.Id = CompPair.Key;
            const TSharedPtr<FJsonObject> ComponentValueObject = CompPair.Value->AsObject();

            if (ComponentValueObject.IsValid())
            {
                
                if (HasLocales())
                {
                    ConditionData.Label = GetTranslatedContent(ConditionData.Id, TEXT("label"), DesiredLocale, bFallbackToDefaultLanguage);
                }
                else 
                {
                    ComponentValueObject->TryGetStringField(TEXT("label"), ConditionData.Label);
                }

                ComponentValueObject->TryGetStringField(TEXT("type"), ConditionData.Type);
                ComponentValueObject->TryGetStringField(TEXT("theme"), ConditionData.Theme);
                ComponentValueObject->TryGetStringField(TEXT("sourceid"), ConditionData.Sourceid);
                ComponentValueObject->TryGetStringField(TEXT("targetid"), ConditionData.Targetid);
                ComponentValueObject->TryGetStringField(TEXT("sourceType"), ConditionData.SourceType);
                ComponentValueObject->TryGetStringField(TEXT("targetType"), ConditionData.TargetType);
                Connections.Add(ConditionData);
            }
        }
    }
    return Connections;
}

FArcweaveCoverData UArcweaveSubsystem::ParseCoverData(const TSharedPtr<FJsonObject>& CoverValueObject)
{
    FArcweaveCoverData CoverData;
    if (CoverValueObject->HasField(TEXT("cover")))
    {
        TSharedPtr<FJsonObject> CoverObject = CoverValueObject->GetObjectField(TEXT("cover"));

        // Extract cover data
        CoverObject->TryGetStringField(TEXT("id"), CoverData.Id);
        CoverObject->TryGetStringField(TEXT("file"), CoverData.File);
        CoverObject->TryGetStringField(TEXT("type"), CoverData.Type);
    }
    return CoverData;
}

TArray<FArcweaveLocaleData> UArcweaveSubsystem::ParseProjectLocales(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    TArray<FArcweaveLocaleData> Locales;
    const TArray<TSharedPtr<FJsonValue>>* LocalesArray;

    if (MainJsonObject->TryGetArrayField(TEXT("locales"), LocalesArray))
    {
        for (const TSharedPtr<FJsonValue>& LocaleValue : *LocalesArray)
        {
            const TSharedPtr<FJsonObject>* LocaleObject;
            if (LocaleValue->TryGetObject(LocaleObject))
            {
                FArcweaveLocaleData LocaleData;
                (*LocaleObject)->TryGetStringField(TEXT("iso"), LocaleData.Iso);
                (*LocaleObject)->TryGetStringField(TEXT("name"), LocaleData.Name);
                // "base" can be null, so check if it exists and is a string
                if ((*LocaleObject)->HasField(TEXT("base")))
                {
                    (*LocaleObject)->TryGetStringField(TEXT("base"), LocaleData.Base);
                }
                else
                {
                    LocaleData.Base = FString("");
                }
                Locales.Add(LocaleData);
            }
        }
    }
    return Locales;
}

FString UArcweaveSubsystem::GetTranslatedContent(const FString& ContentKey, const FString& FieldName, const FString& CurrentLocale, bool ShouldFallback = true) const
{
    FString OutTranslation;

    FArcweaveContent Content;
    if (!ProjectData.Contents.GetContent(Content, ContentKey))
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("ContentKey '%s' not found in Contents."), *ContentKey);
        return FString();
    }

    if (Content.GetTranslationForKey(OutTranslation, CurrentLocale, FieldName))
    {
        return OutTranslation;
    }

    // If fallback is allowed, try to find a fallback locale
    if (ShouldFallback)
    {
        FString FallbackLocale = GetFallbackLanguageForLocale(CurrentLocale);
        if (!FallbackLocale.IsEmpty() && Content.GetTranslationForKey(OutTranslation, FallbackLocale, FieldName))
        {
            return OutTranslation;
        }
    }

    // If nothing found, return empty string
    UE_LOG(LogArcwarePlugin, Warning, TEXT("No translation found for ContentKey '%s', FieldName '%s', Locale '%s'."), *ContentKey, *FieldName, *CurrentLocale);
    return FString();
}

void UArcweaveSubsystem::GetLanguageSettings(FString& OutDesiredLocale, bool& OutFallbackToDefaultLanguage)
{
    const UArcweaveSettings* ArcweaveSettings = GetMutableDefault<UArcweaveSettings>();

    OutDesiredLocale = TEXT("");
    OutFallbackToDefaultLanguage = false;
    if (IsValid(ArcweaveSettings))
    {
        OutDesiredLocale = !ArcweaveSettings->GetLocale().IsEmpty() ? ArcweaveSettings->GetLocale() : TEXT("en");
        OutFallbackToDefaultLanguage = ArcweaveSettings->GetFallbackToDefaultLocale();
    }
}

void UArcweaveSubsystem::UpdateContentsWithLocale(const FString& DesiredLocale)
{

    if (!HasLocales())
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("No other locale is available - can't update the locale to %s"), *DesiredLocale);
        return;
    }

    UArcweaveSettings* ArcweaveSettings = GetMutableDefault<UArcweaveSettings>();
    bool bFallbackToDefaultLanguage = false;
    if (!IsValid(ArcweaveSettings))
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Unable to change settings locale to %s - settings not available"), *DesiredLocale);
        return;
    }

    ArcweaveSettings->SetLocale(DesiredLocale);
    ArcweaveSettings->SetUseLocale(true);
    bFallbackToDefaultLanguage = ArcweaveSettings->GetFallbackToDefaultLocale();

    for (auto& board : ProjectData.Boards)
    {
        for (FArcweaveElementData& element : board.Elements)
        {
            element.Title = RemoveHtmlTags(GetTranslatedContent(element.Id, TEXT("title"), DesiredLocale, bFallbackToDefaultLanguage));
            element.Content = GetTranslatedContent(element.Id, TEXT("content"), DesiredLocale, bFallbackToDefaultLanguage);

            for (auto& component : element.Components)
            {
                component.Name = GetTranslatedContent(component.Id, TEXT("name"), DesiredLocale, bFallbackToDefaultLanguage);
            }

            for (auto& output : element.Outputs)
            {
                output.Label = GetTranslatedContent(output.Id, TEXT("label"), DesiredLocale, bFallbackToDefaultLanguage);
            }
        }

        for (FArcweaveConnectionsData& connection : board.Connections)
        {
            connection.Label = GetTranslatedContent(connection.Id, TEXT("label"), DesiredLocale, bFallbackToDefaultLanguage);
        }

    }

    if (OnArcweaveLanguageChanged.IsBound())
    {
        OnArcweaveLanguageChanged.Broadcast(DesiredLocale);
    }
}

void UArcweaveSubsystem::ParseResponse(const FString& ResponseString)
{
    TSharedPtr<FJsonObject> RootObject;
    // Convert the response to a JSON object
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);

    if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
    {
        // Failed to parse the response
        UE_LOG(LogArcwarePlugin, Error, TEXT("Failed to parse the HTTP Response!"));
        return;
    }

    RootObject = JsonObject;
    const TSharedPtr<FJsonObject>* OutObject;
    // this should be true when retriving from the web API
    if (JsonObject->TryGetObjectField(TEXT("project"), OutObject))
    {
        RootObject = *OutObject;
    }

    // Extract project name and cover data     
    if (RootObject->TryGetStringField(TEXT("name"), ProjectData.Name))
    {
        // Locales are used later so they need to be on top
        ProjectData.Locales = ParseProjectLocales(RootObject);
        ProjectData.Contents = ParseAllContents(RootObject);
        ProjectData.Cover = ParseCoverData(RootObject);
        ProjectData.CurrentVars = ParseVariables(RootObject);
        ProjectData.Components = ParseAllComponents(RootObject);
        ProjectData.Conditions = ParseAllConditions(RootObject);
        ProjectData.Connections = ParseAllConnections(RootObject);
        ProjectData.Boards = ParseBoard(RootObject);
        ProjectData.CurrentVars = ParseVariables(RootObject);
        ProjectData.Visits = InitVisits(RootObject);
        OnArcweaveResponseReceived.Broadcast(ProjectData);
        //LogStructFieldsRecursive(&ProjectData, FArcweaveProjectData::StaticStruct(),0);
    }
    else
    {
        // Handle error here.
        UE_LOG(LogArcwarePlugin, Error, TEXT("Project name is invalid!"));
    }
}

FArcweaveContents UArcweaveSubsystem::ParseAllContents(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    FArcweaveContents ParsedContents;

    const TSharedPtr<FJsonObject>* ContentsObject;
    if (MainJsonObject->TryGetObjectField(TEXT("contents"), ContentsObject))
    {
        // Iterate through all entries in the "contents" object
        for (const auto& ContentPair : ContentsObject->Get()->Values)
        {
            FString ContentId = ContentPair.Key;
            const TSharedPtr<FJsonObject> ContentData = ContentPair.Value->AsObject();

            if (!ContentData.IsValid())
            {
                UE_LOG(LogArcwarePlugin, Warning, TEXT("UArcweaveSubsystem::ParseAllContents: Invalid ContentData for ContentId '%s'. Skipping this entry."), *ContentId);
                continue;
            }

            FArcweaveContent ArcweaveContent;

            // Parse localized string fields (e.g., label, title, content)
            for (const auto& FieldPair : ContentData->Values)
            {
                FString FieldKey = FieldPair.Key;

                /* For the moment we will ignore status*/
                if (FieldKey.Compare(TEXT("_status")) == 0)
                {
                    continue;
                }
                const TSharedPtr<FJsonObject> LocalizedObject = FieldPair.Value->AsObject();

                if (LocalizedObject.IsValid())
                {
                    // Parse translations for each locale
                    for (const auto& LocalePair : LocalizedObject->Values)
                    {
                        FString Locale = LocalePair.Key;
                        const TSharedPtr<FJsonObject> LocaleData = LocalePair.Value->AsObject();

                        if (LocaleData.IsValid())
                        {
                            FString Translation;
                            if (LocaleData->TryGetStringField(TEXT("text"), Translation))
                            {
                                ArcweaveContent.AddTranslationForKey(Locale, Translation, FieldKey);
                            }
                        }
                    }

                }
            }

            // Add the parsed content to the contents map
            ParsedContents.AddContent(ContentId, ArcweaveContent);
        }
    }

    return ParsedContents;
}

void UArcweaveSubsystem::OnEventCallback(const char* EventName)
{
    FString EventNameFString = FString(EventName);

    if (EventNameFString == "resetVisits")
    {
        // Reset visits in ProjectData
        ResetVisits();
    }

    // Broadcast the event to any listeners
    OnArcscriptEventReceived.Broadcast(EventNameFString);
}

void UArcweaveSubsystem::ResetVisits()
{
    for (auto& VisitPair : ProjectData.Visits)
    {
        VisitPair.Value = 0;
    }
}

FArcscriptTranspilerOutput UArcweaveSubsystem::RunTranspiler(const FString& NodeCode, const FString& OriginElementId,
    const TMap<FString, FArcweaveVariable>& InitialVars, const TMap<FString, int>& Visits, bool bShouldUpdateVariables /* = true*/)
{
    // Create output
    FArcscriptTranspilerOutput Output;

    FarcweaveModule* arcweaveModule = FModuleManager::GetModulePtr<FarcweaveModule>("Arcweave");
    UArcscriptTranspilerWrapper* ArcscriptWrapper = arcweaveModule->getArcscriptWrapper();

    // allocate arcscript wrapper

    if (ArcscriptWrapper)
    {
        UE_LOG(LogArcwarePlugin, Display, TEXT("Code=%s"), *NodeCode);
        UE_LOG(LogArcwarePlugin, Display, TEXT("ElementId=%s"), *OriginElementId);
        Output = ArcscriptWrapper->RunScript(NodeCode, OriginElementId, InitialVars, Visits, std::bind(&UArcweaveSubsystem::OnEventCallback, this, std::placeholders::_1));

        LogTranspilerOutput(Output);

        if (bShouldUpdateVariables)
        {
            UpdateVariables(Output);
        }

    }
    else
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("ArcscriptWrapper not initialized"));
    }

    return Output;
}

void UArcweaveSubsystem::UpdateVariables(const FArcscriptTranspilerOutput& Output)
{
    bool IsVariableChanged = false;
    TArray<FArcweaveVariable> ChangedVariables;
    for (const FArcscriptVariableChange& Change : Output.Changes)
    {
        if (Change.Value.IsValid())
        {
            IsVariableChanged = true;
            FArcweaveVariable Variable;
            Variable.Id = Change.Id;
            Variable.Type = Change.Type;
            Variable.Name = ProjectData.CurrentVars.Contains(Change.Id) ? ProjectData.CurrentVars[Change.Id].Name : "Unknown";

            UE_LOG(LogArcwarePlugin, Display, TEXT("Id='%s'"), *Change.Id);
            UE_LOG(LogArcwarePlugin, Display, TEXT("Type='%s'"), *Change.Type);

            if (Change.Type == "string")
            {
                Variable.Value = Change.Value->AsString();
            }
            else if (Variable.Type == "integer")
            {
                int outInt = 0;
                Change.Value->TryGetNumber(outInt);
                Variable.Value.AppendInt(outInt);
            }
            else if (Variable.Type == "bool")
            {
                Variable.Value = FString::Printf(TEXT("%s"), Change.Value->AsBool() ? TEXT("true") : TEXT("false"));
            }
            else if (Variable.Type == "float")
            {
                float outFloat = 0;
                Change.Value->TryGetNumber(outFloat);
                Variable.Value = FString::SanitizeFloat(outFloat);
            }

            ChangedVariables.Add(Variable);

            //find this variable in project data and update it
            for (auto& VarPair : ProjectData.CurrentVars)
            {
                if (VarPair.Key == Variable.Id)
                {
                    VarPair.Value.Value = Variable.Value;
                    UE_LOG(LogArcwarePlugin, Display, TEXT("Update variable id %s, value %s"), *Variable.Id, *VarPair.Value.Value);
                    break;
                }
            }
        }
    }

    // Broadcast changes
    if (IsVariableChanged)
    {
        OnArcweaveVariableChanged.Broadcast(ChangedVariables);
    }
}

void UArcweaveSubsystem::UpdateVariablesFromConnection(const FArcweaveConnectionsData& Connection)
{

    //find the connection in the project data
    for (const FArcweaveBoardData& Board : ProjectData.Boards)
    {
        for (const FArcweaveConnectionsData& Con : Board.Connections)
        {
            if (Con.Id == Connection.Id)
            {
                RunTranspiler(Con.Label, Con.Id, ProjectData.CurrentVars, ProjectData.Visits, true);
                return;
            }
        }
    }

    UE_LOG(LogArcwarePlugin, Warning, TEXT("Connection with id %s not found in project data"), *Connection.Id);

}


void UArcweaveSubsystem::LogTranspilerOutput(const FArcscriptTranspilerOutput& TranspilerOutput)
{
    UE_LOG(LogArcwarePlugin, Display, TEXT("--- TranspilerOutput ------"));

    // Log individual fields of FArcscriptTranspilerOutput
    UE_LOG(LogArcwarePlugin, Display, TEXT("Output='%s'"), *TranspilerOutput.Output);
    FString TypeToString = UEnum::GetValueAsString(TranspilerOutput.Type);
    UE_LOG(LogArcwarePlugin, Display, TEXT("Type=%s"), *TypeToString);
    UE_LOG(LogArcwarePlugin, Display, TEXT("ConditionResult=%s"), TranspilerOutput.ConditionResult ? TEXT("true") : TEXT("false"));

    // Log FArcscriptVariableChange objects in the Changes array
    for (const FArcscriptVariableChange& Change : TranspilerOutput.Changes)
    {
        UE_LOG(LogArcwarePlugin, Display, TEXT("Change:"));
        UE_LOG(LogArcwarePlugin, Display, TEXT("Id='%s'"), *Change.Id);
        UE_LOG(LogArcwarePlugin, Display, TEXT("Type='%s'"), *Change.Type);

        // Check if Value is valid before logging it
        if (Change.Value.IsValid())
        {
            //log value type based on a type variable
            if (Change.Type == FString("string"))
            {
                UE_LOG(LogArcwarePlugin, Display, TEXT("Value=%s"), *Change.Value->AsString());
            }
            else if (Change.Type == FString("integer"))
            {
                int outInt = 0;
                Change.Value->TryGetNumber(outInt);
                UE_LOG(LogArcwarePlugin, Display, TEXT("Value=%d"), outInt);
            }
            else if (Change.Type == FString("bool"))
            {
                FString result = Change.Value->AsBool() ? TEXT("true") : TEXT("false");
                UE_LOG(LogArcwarePlugin, Display, TEXT("Value=%s"), *result);
            }
            //we store float as double
            // because in UVariableChange there id no float possibility
            // we will consider every float from the Arweave plaform as double from now on
            // but we will write it as float in the platform
            else if (Change.Type == FString("float"))
            {
                double outDouble = 0;
                Change.Value->TryGetNumber(outDouble);
                UE_LOG(LogArcwarePlugin, Display, TEXT("Value=%f"), outDouble);
            }
        }
        else
        {
            UE_LOG(LogArcwarePlugin, Display, TEXT("Value is null"));
        }
    }
    UE_LOG(LogArcwarePlugin, Display, TEXT("--- TranspilerOutput END ------"));
}

void UArcweaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // we must read from engine config here
    //ArcweaveAPISettings = LoadArcweaveSettings();
}

void UArcweaveSubsystem::LogFetchStatus(const bool& Success, const FString& Message)
{
    //is suceces color green, if not red
    FColor Color = Success ? FColor::Green : FColor::Red;
    if (Success)
    {
        UE_LOG(LogArcwarePlugin, Log, TEXT("%s"), *Message);
    }
    else
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("%s"), *Message);
    }
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, Color, Message);
    }
}

void UArcweaveSubsystem::HandleFetch(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("HTTP request failed outright."));
        return;
    }

    int32 StatusCode = Response->GetResponseCode();
    FString ResponseBody = Response->GetContentAsString();

    if (StatusCode == 200)
    {
        ParseResponse(ResponseBody);
    }
    else
    {
        FString ErrorMessage = FString::Printf(TEXT("HTTP Error %d: %s"), StatusCode, *ResponseBody);
        LogFetchStatus(false, ErrorMessage);
    }
}
