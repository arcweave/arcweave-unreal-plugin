// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\ArcweaveSubsystem.h"

#include "Arcweave.h"
#include "ArcweaveSettings.h"
#include "ArcweaveTypes.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"

void UArcweaveSubsystem::FetchDataFromAPI(FString APIToken, FString ProjectHash)
{
    FString ApiUrl = FString::Printf(TEXT("https://arcweave.com/api/%s/unreal"), *ProjectHash);

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

void UArcweaveSubsystem::FetchData(FString APIToken, FString ProjectHash)
{
    FArcweaveAPISettings NewArcweaveAPISettings = LoadArcweaveSettings();
    if (NewArcweaveAPISettings.EnableRecieveMethodFromLocalJSON)
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
            if(GConfig->GetBool(ARCWEAVE_SETTINGS_SECTION, TEXT("EnableReceiveMethodFromLocalJSON"), OutSetttings.EnableRecieveMethodFromLocalJSON, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read EnableRecieveMethodFromLocalJSON: %d"), OutSetttings.EnableRecieveMethodFromLocalJSON);
            }
            
            if(GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, TEXT("APIToken"), OutSetttings.APIToken, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read APIToken: %s"), *OutSetttings.APIToken);
            }

            if(GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, TEXT("Hash"), OutSetttings.Hash, GGameIni))
            {
                UE_LOG(LogTemp, Warning, TEXT("Read Hash: %s"), *OutSetttings.Hash);
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

bool UArcweaveSubsystem::IsScriptVisitsPositive(const FString& ConditionScript)
{
    // Check for "not visits" first to handle the negation case
    if (ConditionScript.Contains(TEXT("not visits"), ESearchCase::IgnoreCase, ESearchDir::FromStart))
    {
        return false;
    }
    else if (ConditionScript.Contains(TEXT("visits"), ESearchCase::IgnoreCase, ESearchDir::FromStart))
    {
        return true; // Found a relevant mention
    }
    
    return false;
}

FArcscriptTranspilerOutput UArcweaveSubsystem::TranspileCondition(FString ConditionId, bool& Success)
{
    UE_LOG(LogArcwarePlugin, Log, TEXT("----- TranspileCondition for id: %s -----"), *ConditionId);
    Success = false;
    FArcscriptTranspilerOutput Output;
    FArcweaveConditionData ConditionData;
    FArcweaveBoardData* NewBoardObj = nullptr;
    if(GetBoardObjectForElement(ConditionId, ConditionData, NewBoardObj) == false)
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
        //here we are checking if the condition is a visit counter
        //this is the format of the visit counter condition
        //"script": "visits(<span class=\"mention-element mention\" data-id=\"045ab2b6-6d77-43f7-a7b4-e275f41667c3\" data-label=\"Giving healing potion\" data-type=\"element\">giving_healing_potion<\/span>)"
        //"script": "not visits(<span class=\"mention-element mention\" data-id=\"d852a577-bd1f-44cf-8187-77a86f97baef\" data-label=\"Get potion\" data-type=\"element\">get_potion<\/span>)"
        //so if there is a string with data-id and the word visits, we will not transpile it
        //we will just check the counter and return the output
        FString ScriptDataId = ExtractDataIdFromConditionScriptString(ConditionData.Script);
        if (ScriptDataId.IsEmpty())
        {
            //run the transpiler
            FString ScriptModified = FString("<pre><code>") + ConditionData.Script + FString("</code></pre>");
            Output = RunTranspiler(ScriptModified, ConditionData.Id, ProjectData.CurrentVars, NewBoardObj->Visits);
            NewBoardObj->Visits[ConditionId] += 1;
        }
        else
        {
            bool IsScriptsVisitsPositive = IsScriptVisitsPositive(ConditionData.Script);
            const int* VisitsCounter = NewBoardObj->Visits.Find(ScriptDataId);
            if (VisitsCounter)
            {
                Output.ConditionResult = *VisitsCounter > 0;
                //we need the reverse result, the condition is not negated
                if (IsScriptsVisitsPositive == false)
                {
                    Output.ConditionResult = !Output.ConditionResult;
                }
                //UE_LOG(LogArcwarePlugin, Log, TEXT("Visits counter for id GET : %s is: %d conditionResult is: %d IsScriptsVisitsPositive %d"), *ScriptDataId, *VisitsCounter, Output.ConditionResult, IsScriptsVisitsPositive);
            }
        }
        Success = true;
    }
    catch (...)
    {
    }
        
    return Output;
}

bool UArcweaveSubsystem::GetBoardForObject(FString ObjectId, FArcweaveElementData& OutElement, FArcweaveBoardData*& OutBoardObj)
{
    for (auto& Board : ProjectData.Boards)
    {
        for (auto& ElementObj : Board.Elements)
        {
            if (ElementObj.Id == ObjectId)
            {
                OutBoardObj = &Board;
                OutElement = ElementObj;
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

FArcweaveElementData UArcweaveSubsystem::TranspileObject(FString ObjectId, bool& Success)
{
    Success = false;
    FArcweaveElementData Element;
    //get the element
    FArcweaveBoardData* NewBoardObj = nullptr;
    if(GetBoardForObject(ObjectId, Element, NewBoardObj) == false)
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
        FArcscriptTranspilerOutput Output = RunTranspiler(Element.Content, Element.Id, ProjectData.CurrentVars, NewBoardObj->Visits);
        NewBoardObj->Visits[ObjectId] += 1;
        //UE_LOG(LogArcwarePlugin, Log, TEXT("Visits counter for id: %s is: %d"), *ObjectId, NewBoardObj->Visits[ObjectId]);
        Element.Content = RemoveHtmlTags(Output.Output);
        Success = true;
    }
    catch (...)
    {
    }
        
    return Element;
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
            CleanedString.RemoveAt(TagStartIndex, TagEndIndex - TagStartIndex + 1, /*bAllowShrinking*/ true);
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

FString UArcweaveSubsystem::ExtractDataIdFromConditionScriptString(const FString& ConditionScript)
{
    // Define the regex pattern to match the data-id value
    FRegexPattern Pattern(TEXT("data-id=\\\"([\\w-]+)\\\""));
    FRegexMatcher Matcher(Pattern, ConditionScript);

    if (Matcher.FindNext())
    {
        // Return the matched data-id value
        return Matcher.GetCaptureGroup(1);
    }

    // If no match is found, return an empty string or an error message
    return FString("");
}

TArray<FArcweaveAssetData> UArcweaveSubsystem::ParseComponentAsset(const TSharedPtr<FJsonObject>& ComponentValueObject)
{
    // Parse "assets" for components as an array of asset data structs
    TArray<FArcweaveAssetData> ComponentAssets;
    const TSharedPtr<FJsonObject>* ComponentAssetsObject;
    if (ComponentValueObject->TryGetObjectField("assets", ComponentAssetsObject))
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
    if (ParentValueObject->TryGetStringArrayField("attributes", AttributesStringArray))
    {
        for (const auto& AttributeAssetId : AttributesStringArray)
        {
            FArcweaveAttributeData AttributeAsset;
            // Iterate through the array of attributes and find with this id
            const TSharedPtr<FJsonObject>* AttributesObject;
            if (MainJsonObject->TryGetObjectField("attributes", AttributesObject))
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
                            AttributeAssetValueObject->TryGetStringField("cId", AttributeAsset.cId);
                            AttributeAssetValueObject->TryGetStringField("name", AttributeAsset.Name);
                            AttributeAssetValueObject->TryGetStringField("cType", AttributeAsset.cType);

                            // Parse "value" as FArcweaveAttributeValueData
                            const TSharedPtr<FJsonObject>* AttributeValueObject;
                            if (AttributeAssetValueObject->TryGetObjectField("value", AttributeValueObject))
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
    ValueObject->TryGetStringField("data", AttributeValue.Data);
    ValueObject->TryGetStringField("type", AttributeValue.Type);
    ValueObject->TryGetBoolField("plain", AttributeValue.Plain);
}

TArray<FArcweaveBoardData> UArcweaveSubsystem::ParseBoard(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    TArray<FArcweaveBoardData> Boards;
    const TSharedPtr<FJsonObject>* BoardsObject;
    if (MainJsonObject->TryGetObjectField("boards", BoardsObject))
    {
        for (const auto& BoardPair : BoardsObject->Get()->Values)
        {
            const TSharedPtr<FJsonObject> BoardValueObject = BoardPair.Value->AsObject();
            FArcweaveBoardData Board;
            Board.BoardId = BoardPair.Key;

            FString BoardName;
            if (BoardValueObject->TryGetStringField("name", BoardName))
            {
                Board.Name = BoardName;
            }
            
           Board.Visits = InitVisist(BoardValueObject, Board);
           Board.Elements = ParseElements(MainJsonObject, BoardValueObject, Board);
           Board.Connections = ParseConnections(FString("connections"), MainJsonObject, BoardValueObject);
           Board.Branches = ParseBranches(MainJsonObject, BoardValueObject,Board);
           Board.Jumpers = ParseJumpers(MainJsonObject, BoardValueObject, Board);
           Boards.Add(Board);
        }
    }
    return Boards;
}

TMap<FString, FArcweaveVariable> UArcweaveSubsystem::ParseVariables(const TSharedPtr<FJsonObject>& MainJsonObject)
{
    TMap<FString, FArcweaveVariable> InitialVars;
    const TSharedPtr<FJsonObject>* VariablesObject;
    if (MainJsonObject->TryGetObjectField("variables", VariablesObject))
    {
        for (const auto& VariablePair : VariablesObject->Get()->Values)
        {
            const TSharedPtr<FJsonObject> VarObject = VariablePair.Value->AsObject();
            bool isRoot = false;
            if (!(VarObject->TryGetBoolField("root", isRoot) && isRoot)) {
                FArcweaveVariable Variable;
                Variable.Id = VariablePair.Key;
                VarObject->TryGetStringField("name", Variable.Name);
                VarObject->TryGetStringField("type", Variable.Type);
                if (Variable.Type == "string") {
                    Variable.Value = VarObject->GetStringField("value");
                }
                else if (Variable.Type == "integer") {
                    Variable.Value.AppendInt(VarObject->GetIntegerField("value"));
                }
                else if (Variable.Type == "boolean") {
                    Variable.Value = FString::Printf(TEXT("%s"), VarObject->GetBoolField("value") ? TEXT("true") : TEXT("false"));
                }
                else if (Variable.Type == "float")
                {
                    Variable.Value = FString::SanitizeFloat(VarObject->GetNumberField("value"));
                }
                InitialVars.Add(Variable.Id, Variable);
            }
        }
    }
    return InitialVars;
}

TArray<FArcweaveConnectionsData> UArcweaveSubsystem::ParseConnections(const FString& FieldName, const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ParentValueObject)
{
      // Parse "connections" as an array of connection data structs
    TArray<FArcweaveConnectionsData> Connections;
    TArray<FString> ConnectionsArrayStrings;
    if (ParentValueObject->TryGetStringArrayField(FieldName, ConnectionsArrayStrings))
    {
        for (const FString& ConnectionId : ConnectionsArrayStrings)
        {
            // Extract connections
            const TSharedPtr<FJsonObject>* ConnectionsObject;
            if (MainJsonObject->TryGetObjectField("connections", ConnectionsObject))
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
                            FString DirtyLabel = FString("");
                            ConObject->TryGetStringField("label", DirtyLabel);
                            Connection.Label = RemoveHtmlTags(DirtyLabel);                            
                            ConObject->TryGetStringField("type", Connection.Type);
                            ConObject->TryGetStringField("theme", Connection.Theme);
                            ConObject->TryGetStringField("sourceid", Connection.Sourceid);
                            ConObject->TryGetStringField("targetid", Connection.Targetid);
                            ConObject->TryGetStringField("sourceType", Connection.SourceType);
                            ConObject->TryGetStringField("targetType", Connection.TargetType);
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

TArray<FArcweaveElementData> UArcweaveSubsystem::ParseElements(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj)
{
    TArray<FArcweaveElementData> Elements;
     // Parse "elements" as an array of element data structs
    TArray<FString> ElementArrayStrings;
    if (BoardValueObject->TryGetStringArrayField("elements", ElementArrayStrings))
    {
        for (const FString& ElementId : ElementArrayStrings)
        {
            OutBoardObj.Visits.Add(ElementId, 0);
        }
        //then search for the element pairs
        for (const FString& ElementId : ElementArrayStrings)
        {
            FArcweaveElementData Element = ExtractElementData(MainJsonObject, ElementId);
            Elements.Add(Element);
        }        
    }
    return Elements;
}

TArray<FArcweaveBranchData> UArcweaveSubsystem::ParseBranches(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj)
{
    TArray<FArcweaveBranchData> Branches;
    TArray<FString> BranchesArrayStrings;
    if (BoardValueObject->TryGetStringArrayField("branches", BranchesArrayStrings))
    {
        for (const FString& BranchId : BranchesArrayStrings)
        {
            OutBoardObj.Visits.Add(BranchId, 0);
        }
        //then search for the element pairs
        for (const FString& BranchId : BranchesArrayStrings)
        {
            // Extract branches
            const TSharedPtr<FJsonObject>* BranchObject;
            if (MainJsonObject->TryGetObjectField("branches", BranchObject))
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
                        const TSharedPtr<FJsonObject>& ConditionsObject = BranchDataObject->GetObjectField("conditions");

                        // Extract "ifCondition"
                        Branch.IfCondition = ParseConditionData(MainJsonObject, ConditionsObject, FString("ifCondition"), OutBoardObj);
                        Branch.ElseCondition = ParseConditionData(MainJsonObject, ConditionsObject, FString("elseCondition"), OutBoardObj);
                        
                        // Extract "elseIfConditions" array
                        const TArray<TSharedPtr<FJsonValue>>* ElseIfConditionsArray;
                        if (ConditionsObject->TryGetArrayField("elseIfConditions", ElseIfConditionsArray))
                        {
                            for (const TSharedPtr<FJsonValue>& ElseIfValue : *ElseIfConditionsArray)
                            {
                                FArcweaveConditionData ElseIfConditionSingle = ParseConditionData(MainJsonObject, ConditionsObject, FString("elseIfCondition"), OutBoardObj);
                                Branch.ElseIfConditions.Add(ElseIfConditionSingle);
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

TArray<FArcweaveJumpersData> UArcweaveSubsystem::ParseJumpers(const TSharedPtr<FJsonObject>& MainJsonObject,
    const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj)
{
     TArray<FArcweaveJumpersData> Jumpers;
    TArray<FString> JumpersArrayStrings;
    if (BoardValueObject->TryGetStringArrayField("jumpers", JumpersArrayStrings))
    {
        for (const FString& JumperId : JumpersArrayStrings)
        {
            OutBoardObj.Visits.Add(JumperId, 0);
        }
        //then search for the elements for jumpers
        for (const FString& JumperId : JumpersArrayStrings)
        {
            // Extract jumpers
            const TSharedPtr<FJsonObject>* JumperObject;
            if (MainJsonObject->TryGetObjectField("jumpers", JumperObject))
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
                            JumperDataObject->TryGetStringField("elementId", ElementId);
                            FArcweaveElementData Element = ExtractElementData(MainJsonObject, ElementId);
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

FArcweaveElementData UArcweaveSubsystem::ExtractElementData(const TSharedPtr<FJsonObject>& MainJsonObject, const FString& ElementId)
{
    FArcweaveElementData Element;
    const TSharedPtr<FJsonObject>* ElementsObject;
    if (MainJsonObject->TryGetObjectField("elements", ElementsObject))
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
                    ElementValueObject->TryGetStringField("theme", Element.Theme);
                    FString DirtyTitle = FString("");
                    ElementValueObject->TryGetStringField("title", DirtyTitle);
                    Element.Title = RemoveHtmlTags(DirtyTitle);
                    FString DirtyContent = FString("");
                    ElementValueObject->TryGetStringField("content", Element.Content);
                    //FArcscriptTranspilerOutput Output = RunTranspiler(DirtyContent, Element.Id, ProjectData.InitialVars, BoardObj.Visits);
                    Element.Outputs = ParseConnections(FString("outputs"), MainJsonObject, ElementValueObject);
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
    if(ConditionsObject->TryGetStringField(ConditionName, IfConditionOutputId))
    {
        const TSharedPtr<FJsonObject>* ConditionsObjectField;
        if (MainJsonObject->TryGetObjectField("conditions", ConditionsObjectField))
        {
            // Iterate through the "branches" object
            for (const auto& ConditionPair : ConditionsObjectField->Get()->Values)
            {
                if (ConditionPair.Key == IfConditionOutputId)
                {
                    const TSharedPtr<FJsonObject>& ConditionDataObject = ConditionPair.Value->AsObject();
                    ConditionData.Id = ConditionPair.Key;
                    OutBoardObj.Visits.Add(ConditionData.Id, 0);
                    //output
                    FString Output = FString("");
                    if (ConditionDataObject->TryGetStringField("output", Output))
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
                    if (ConditionDataObject->TryGetStringField("script", Script))
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


TMap<FString, int> UArcweaveSubsystem::InitVisist(const TSharedPtr<FJsonObject>& BoardValueObject, FArcweaveBoardData& OutBoardObj)
{
    //add the visits to the board data
    TMap<FString, int> AllVisits;
    TArray<FString> ElementArrayStrings;
    if (BoardValueObject->TryGetStringArrayField("elements", ElementArrayStrings))
    {
        for (const FString& ElementId : ElementArrayStrings)
        {
           AllVisits.Add(ElementId, 0);
        }
    }
    return AllVisits;
}

TArray<FArcweaveComponentData> UArcweaveSubsystem::ParseComponents(const TSharedPtr<FJsonObject>& MainJsonObject, const TSharedPtr<FJsonObject>& ElementValueObject)
{
    // Parse "components" as an array of component data structs
    TArray<FArcweaveComponentData> Components;
    TArray<FString> ComponentsStringArray;
    if (ElementValueObject->TryGetStringArrayField("components", ComponentsStringArray))
    {
        for (const auto& ComponentId : ComponentsStringArray)
        {
            // Iterate through the array of components and find with this id
            const TSharedPtr<FJsonObject>* CompObject;
            if (MainJsonObject->TryGetObjectField("components", CompObject))
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
                            // Extract the "name" and "root"
                            ComponentValueObject->TryGetStringField("name", ElComponent.Name);
                            ComponentValueObject->TryGetBoolField("root", ElComponent.Root);
                            ComponentValueObject->TryGetStringArrayField("children", ElComponent.Children);
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
    if (MainJsonObject->TryGetObjectField("components", CompObject))
    {
        for (const auto& CompPair : CompObject->Get()->Values)
        {
            FArcweaveComponentData ElComponent;
            ElComponent.Id = CompPair.Key;
            const TSharedPtr<FJsonObject> ComponentValueObject = CompPair.Value->AsObject();

            if (ComponentValueObject.IsValid())
            {
                // Extract the "name" and "root"
                ComponentValueObject->TryGetStringField("name", ElComponent.Name);
                ComponentValueObject->TryGetBoolField("root", ElComponent.Root);
                ComponentValueObject->TryGetStringArrayField("children", ElComponent.Children);
                ElComponent.Assets = ParseComponentAsset(ComponentValueObject);
                ElComponent.Attributes = ParseObjectAttributes(MainJsonObject, ComponentValueObject);

                Components.Add(ElComponent);
            }
        }
    }                          
    return Components;
}

FArcweaveCoverData UArcweaveSubsystem::ParseCoverData(const TSharedPtr<FJsonObject>& CoverValueObject)
{
    FArcweaveCoverData CoverData;
    if (CoverValueObject->HasField("cover"))
    {
        TSharedPtr<FJsonObject> CoverObject = CoverValueObject->GetObjectField("cover");

        // Extract cover data
        CoverObject->TryGetStringField("id", CoverData.Id);
        CoverObject->TryGetStringField("file", CoverData.File);
        CoverObject->TryGetStringField("type", CoverData.Type);
    }        
    return CoverData;
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
    if (JsonObject->TryGetObjectField("project", OutObject))
    {
        RootObject = *OutObject;
    }

    // Extract project name and cover data     
    if (RootObject->TryGetStringField("name", ProjectData.Name))
    {
        ProjectData.Cover = ParseCoverData(RootObject);        
        ProjectData.CurrentVars = ParseVariables(RootObject);
        ProjectData.Components = ParseAllComponents(RootObject);
        ProjectData.Boards = ParseBoard(RootObject);
        OnArcweaveResponseReceived.Broadcast(ProjectData);
        //LogStructFieldsRecursive(&ProjectData, FArcweaveProjectData::StaticStruct(),0);
    }
    else
    {
        // Handle error here.
        UE_LOG(LogArcwarePlugin, Error, TEXT("Project name is invalid!"));
    }
}

FArcscriptTranspilerOutput UArcweaveSubsystem::RunTranspiler(FString Code, FString ElementId,
    TMap<FString, FArcweaveVariable> InitialVars, TMap<FString, int> Visits)
{
    FArcscriptTranspilerOutput Output;
    bool IsVariableChanged = false;

    FarcweaveModule* arcweaveModule = FModuleManager::GetModulePtr<FarcweaveModule>("Arcweave");
    UArcscriptTranspilerWrapper* ArcscriptWrapper = arcweaveModule->getArcscriptWrapper();
    if (ArcscriptWrapper)
    {
        UE_LOG(LogArcwarePlugin, Display, TEXT("Code=%s"), *Code);
        UE_LOG(LogArcwarePlugin, Display, TEXT("ElementId=%s"), *ElementId);
        Output = ArcscriptWrapper->RunScript(Code, ElementId, InitialVars, Visits);
        LogTranspilerOutput(Output);
        // brodacast event if there where any changes
        TArray<FArcweaveVariable> ChangedVariables;
        for (const FArcscriptVariableChange& Change : Output.Changes)
        {
            if (Change.Value.IsValid())
            {
                IsVariableChanged = true;
                FArcweaveVariable Variable;
                Variable.Id = Change.Id;
                Variable.Type = Change.Type;
                UE_LOG(LogArcwarePlugin, Display, TEXT("Id='%s'"), *Change.Id);
                UE_LOG(LogArcwarePlugin, Display, TEXT("Type='%s'"), *Change.Type);
                if (Change.Type == "string") {
                    Variable.Value = Change.Value->AsString();
                }
                else if (Variable.Type == "integer") {
                    int outInt = 0;
                    Change.Value->TryGetNumber(outInt);
                    Variable.Value.AppendInt(outInt);
                }
                else if (Variable.Type == "bool") {
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
        if (IsVariableChanged)
        {
            OnArcweaveVariableChanged.Broadcast(ChangedVariables);            
        }
    }
    else {
        UE_LOG(LogArcwarePlugin, Error, TEXT("ArcscriptWrapper not initialized"));
    }
    
    return Output;
}

void UArcweaveSubsystem::LogTranspilerOutput(const FArcscriptTranspilerOutput& TranspilerOutput)
{
    UE_LOG(LogArcwarePlugin, Display, TEXT("--- TranspilerOutput ------"));

    // Log individual fields of FArcscriptTranspilerOutput
    UE_LOG(LogArcwarePlugin, Display, TEXT("Output='%s'"), *TranspilerOutput.Output);
    FString TypeToString =  UEnum::GetValueAsString(TranspilerOutput.Type);
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
            if(Change.Type == FString("string"))
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
            else if (Change.Type == FString("double"))
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
    if (bWasSuccessful && Response.IsValid())
    {
        FString ResponseString = Response->GetContentAsString();
        ParseResponse(ResponseString);
    }
    else
    {
        // Handle error here.
        UE_LOG(LogArcwarePlugin, Error, TEXT("HTTP Request failed!"));
        LogFetchStatus(false, Response->GetContentAsString());
    }
}
