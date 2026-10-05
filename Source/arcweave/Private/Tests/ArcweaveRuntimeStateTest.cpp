#include "ArcweaveRuntimeStateTestTypes.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "ArcscriptTranspilerOutput.h"
#include "Dom/JsonObject.h"
#include "HttpModule.h"
#include "Interfaces/IPluginManager.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonSerializer.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveRuntimeStateTest,
    "Arcweave.Project.RuntimeState",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveRuntimeStateTest::RunTest(const FString& Parameters)
{
    const auto TestSameState = [this](
        const FString& Label,
        const FArcweaveRuntimeState& Actual,
        const FArcweaveRuntimeState& Expected)
    {
        TestEqual(Label + TEXT(" format"), Actual.FormatVersion, Expected.FormatVersion);
        TestEqual(Label + TEXT(" project"), Actual.ProjectFingerprint, Expected.ProjectFingerprint);
        TestEqual(Label + TEXT(" variable count"), Actual.Variables.Num(), Expected.Variables.Num());
        for (const auto& Pair : Expected.Variables)
        {
            const FArcweaveSavedVariable* Variable = Actual.Variables.Find(Pair.Key);
            if (TestNotNull(Label + TEXT(" variable ") + Pair.Key, Variable))
            {
                TestEqual(Label + TEXT(" type ") + Pair.Key, Variable->Type, Pair.Value.Type);
                TestEqual(Label + TEXT(" value ") + Pair.Key, Variable->Value, Pair.Value.Value);
            }
        }
        TestEqual(Label + TEXT(" visit count"), Actual.Visits.Num(), Expected.Visits.Num());
        for (const auto& Pair : Expected.Visits)
        {
            const int32* Visits = Actual.Visits.Find(Pair.Key);
            if (TestNotNull(Label + TEXT(" visits ") + Pair.Key, Visits))
            {
                TestEqual(Label + TEXT(" visits value ") + Pair.Key, *Visits, Pair.Value);
            }
        }
    };

    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("arcweave"));
    if (!TestTrue(TEXT("Arcweave plugin is available"), Plugin.IsValid()))
    {
        return false;
    }
    FString Json;
    if (!TestTrue(TEXT("Variable fixture loads"), FFileHelper::LoadFileToString(Json, *FPaths::Combine(
        Plugin->GetBaseDir(), TEXT("Source/arcweave/test/componentBoardVariables.json")))))
    {
        return false;
    }

    TSharedPtr<FJsonObject> Root;
    if (!TestTrue(TEXT("Fixture is valid JSON"), FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json), Root)))
    {
        return false;
    }
    Root->GetObjectField(TEXT("elements"))->GetObjectField(TEXT("element-1"))->SetStringField(
        TEXT("content"), TEXT("<pre><code>health += 1</code></pre><pre><code>resetVisits()</code></pre>"));
    Json.Empty();
    FJsonSerializer::Serialize(Root.ToSharedRef(), TJsonWriterFactory<>::Create(&Json));

    UArcweaveSubsystem* Subsystem = NewObject<UArcweaveSubsystem>();
    FString Error;
    FArcweaveRuntimeState Sentinel;
    Sentinel.FormatVersion = 99;
    Sentinel.ProjectFingerprint = TEXT("unchanged output");
    Sentinel.Visits.Add(TEXT("sentinel"), 23);
    FArcweaveRuntimeState Capture = Sentinel;
    TestFalse(TEXT("Capture requires a loaded project"), Subsystem->CaptureState(Capture, Error));
    TestFalse(TEXT("Missing-project capture explains failure"), Error.IsEmpty());
    TestSameState(TEXT("Failed capture preserves its output"), Capture, Sentinel);
    TestFalse(TEXT("Restore requires a loaded project"), Subsystem->RestoreState(Sentinel, Error));
    TestFalse(TEXT("Missing-project restore explains failure"), Error.IsEmpty());

    if (!TestTrue(TEXT("Project imports"), Subsystem->ParseResponse(Json)))
    {
        return false;
    }
    FArcweaveProjectData& Project = Subsystem->ProjectData;
    if (!TestEqual(TEXT("Fixture contains all seven scoped variables"), Project.CurrentVars.Num(), 7)
        || !TestEqual(TEXT("Fixture contains an element visit counter"), Project.Visits.Num(), 1))
    {
        return false;
    }
    const TMap<FString, FArcweaveVariable> AuthoredVariables = Project.CurrentVars;
    Subsystem->SetVariable(TEXT("global-health"), TEXT("111"));
    Subsystem->SetVariable(TEXT("board-health"), TEXT("37"));
    Subsystem->SetVariable(TEXT("board-open"), TEXT("false"));
    Subsystem->SetVariable(TEXT("board-rate"), TEXT("2.75"));
    Subsystem->SetVariable(TEXT("board-title"), TEXT("The \"castle\"\nNorth"));
    Subsystem->SetVariable(TEXT("component-health"), TEXT("42"));
    Subsystem->SetVariable(TEXT("component-label"), TEXT(""));
    Project.Visits.FindChecked(TEXT("element-1")) = 4;

    FArcweaveRuntimeState Saved;
    if (!TestTrue(TEXT("Runtime state captures"), Subsystem->CaptureState(Saved, Error)))
    {
        return false;
    }
    TestTrue(TEXT("Successful capture clears an earlier error"), Error.IsEmpty());
    TestEqual(TEXT("Snapshot uses format version one"), Saved.FormatVersion, 1);
    TestFalse(TEXT("Snapshot identifies its project"), Saved.ProjectFingerprint.IsEmpty());
    TestEqual(TEXT("Capture includes all variable scopes and types"), Saved.Variables.Num(), 7);
    TestEqual(TEXT("Capture does not advance visits"), Project.Visits.FindChecked(TEXT("element-1")), 4);

    UArcweaveRuntimeStateTestSaveGame* SaveGame = Cast<UArcweaveRuntimeStateTestSaveGame>(
        UGameplayStatics::CreateSaveGameObject(UArcweaveRuntimeStateTestSaveGame::StaticClass()));
    SaveGame->State = Saved;
    const FString Slot = TEXT("ArcweaveRuntimeStateTest_") + FGuid::NewGuid().ToString(EGuidFormats::Digits);
    ON_SCOPE_EXIT
    {
        UGameplayStatics::DeleteGameInSlot(Slot, 0);
    };
    if (!TestTrue(TEXT("Unreal writes the snapshot to a save slot"), UGameplayStatics::SaveGameToSlot(SaveGame, Slot, 0)))
    {
        return false;
    }
    UArcweaveRuntimeStateTestSaveGame* Loaded = Cast<UArcweaveRuntimeStateTestSaveGame>(
        UGameplayStatics::LoadGameFromSlot(Slot, 0));
    if (!TestNotNull(TEXT("Unreal reloads the snapshot from disk"), Loaded))
    {
        return false;
    }
    TestSameState(TEXT("SaveGame serialization roundtrip"), Loaded->State, Saved);

    Subsystem->SetVariable(TEXT("global-health"), TEXT("-5"));
    Subsystem->SetVariable(TEXT("board-health"), TEXT("3"));
    Subsystem->SetVariable(TEXT("board-open"), TEXT("true"));
    Subsystem->SetVariable(TEXT("board-rate"), TEXT("0.5"));
    Subsystem->SetVariable(TEXT("board-title"), TEXT("Other"));
    Subsystem->SetVariable(TEXT("component-health"), TEXT("9"));
    Subsystem->SetVariable(TEXT("component-label"), TEXT("Changed"));
    Project.Visits.FindChecked(TEXT("element-1")) = 0;

    UArcweaveRuntimeStateTestListener* Listener = NewObject<UArcweaveRuntimeStateTestListener>();
    Listener->Subsystem = Subsystem;
    Subsystem->OnArcweaveStateRestored.AddDynamic(Listener, &UArcweaveRuntimeStateTestListener::HandleStateRestored);
    Subsystem->OnArcweaveVariableChanged.AddDynamic(Listener, &UArcweaveRuntimeStateTestListener::HandleVariablesChanged);
    Subsystem->OnArcscriptEventReceived.AddDynamic(Listener, &UArcweaveRuntimeStateTestListener::HandleArcscriptEvent);
    Subsystem->OnArcweaveResponseReceived.AddDynamic(Listener, &UArcweaveRuntimeStateTestListener::HandleProjectImported);

    Error = TEXT("previous failure");
    TestTrue(TEXT("Saved state restores"), Subsystem->RestoreState(Loaded->State, Error));
    TestTrue(TEXT("Successful restore clears an earlier error"), Error.IsEmpty());
    TestEqual(TEXT("Restore emits one dedicated notification"), Listener->RestoreEvents, 1);
    TestEqual(TEXT("Restore does not emit variable changes"), Listener->VariableEvents, 0);
    TestEqual(TEXT("Restore does not run authored events"), Listener->ArcscriptEvents, 0);
    TestEqual(TEXT("Restore does not announce another project import"), Listener->ImportEvents, 0);
    TestTrue(TEXT("Restore notification can capture the completed state"), Listener->bCaptureInRestoreCallbackSucceeded);
    TestSameState(TEXT("Restore listener observes all restored values"), Listener->CapturedInCallback, Saved);
    for (const auto& Pair : AuthoredVariables)
    {
        const FArcweaveVariable& Variable = Project.CurrentVars.FindChecked(Pair.Key);
        TestEqual(TEXT("Authored default survives restore: ") + Pair.Key, Variable.DefaultValue, Pair.Value.DefaultValue);
        TestEqual(TEXT("Default flag survives restore: ") + Pair.Key, Variable.bHasDefaultValue, Pair.Value.bHasDefaultValue);
        TestEqual(TEXT("Variable ID survives restore: ") + Pair.Key, Variable.Id, Pair.Value.Id);
        TestEqual(TEXT("Variable name survives restore: ") + Pair.Key, Variable.Name, Pair.Value.Name);
        TestEqual(TEXT("Variable scope survives restore: ") + Pair.Key, Variable.Scope, Pair.Value.Scope);
        TestEqual(TEXT("Variable owner type survives restore: ") + Pair.Key, Variable.cType, Pair.Value.cType);
    }

    const auto ExpectRejected = [this, Subsystem, Listener, &Error, &TestSameState](
        const FString& Label, const FArcweaveRuntimeState& Invalid)
    {
        FArcweaveRuntimeState Before;
        TestTrue(Label + TEXT(" baseline captures"), Subsystem->CaptureState(Before, Error));
        const int32 RestoreEvents = Listener->RestoreEvents;
        TestFalse(Label + TEXT(" is rejected"), Subsystem->RestoreState(Invalid, Error));
        TestFalse(Label + TEXT(" explains rejection"), Error.IsEmpty());
        FArcweaveRuntimeState After;
        TestTrue(Label + TEXT(" resulting state captures"), Subsystem->CaptureState(After, Error));
        TestSameState(Label + TEXT(" leaves live state unchanged"), After, Before);
        TestEqual(Label + TEXT(" emits no restore event"), Listener->RestoreEvents, RestoreEvents);
        TestEqual(Label + TEXT(" emits no variable event"), Listener->VariableEvents, 0);
        TestEqual(Label + TEXT(" emits no script event"), Listener->ArcscriptEvents, 0);
    };
    FArcweaveRuntimeState Candidate = Saved;
    Candidate.Variables.FindChecked(TEXT("global-health")).Value = TEXT("987");
    FArcweaveRuntimeState Invalid = Candidate;
    Invalid.FormatVersion += 1;
    ExpectRejected(TEXT("Unknown snapshot format"), Invalid);
    Invalid = Candidate;
    Invalid.ProjectFingerprint = TEXT("another project revision");
    ExpectRejected(TEXT("Different project fingerprint"), Invalid);
    Invalid = Candidate;
    Invalid.Variables.Remove(TEXT("component-label"));
    ExpectRejected(TEXT("Missing variable"), Invalid);
    Invalid = Candidate;
    Invalid.Variables.Add(TEXT("unknown-variable"), Saved.Variables.FindChecked(TEXT("board-title")));
    ExpectRejected(TEXT("Extra variable"), Invalid);
    Invalid.Variables.Remove(TEXT("board-title"));
    ExpectRejected(TEXT("Different variable IDs with the same count"), Invalid);
    Invalid = Candidate;
    Invalid.Variables.FindChecked(TEXT("board-health")).Type = TEXT("string");
    ExpectRejected(TEXT("Variable type mismatch"), Invalid);
    for (const TCHAR* Value : {TEXT("3x"), TEXT("1.5"), TEXT("2147483648"), TEXT("-2147483649")})
    {
        Invalid = Candidate;
        Invalid.Variables.FindChecked(TEXT("board-health")).Value = Value;
        ExpectRejected(FString(TEXT("Invalid integer ")) + Value, Invalid);
    }
    for (const TCHAR* Value : {TEXT("1"), TEXT("TRUE"), TEXT("")})
    {
        Invalid = Candidate;
        Invalid.Variables.FindChecked(TEXT("board-open")).Value = Value;
        ExpectRejected(FString(TEXT("Invalid boolean ")) + Value, Invalid);
    }
    const TCHAR* InvalidFloatValues[] = {
        TEXT("NaN"), TEXT("inf"), TEXT("1e309"), TEXT("1.2x"), TEXT(""), TEXT(" "),
        TEXT("."), TEXT("e"), TEXT("+"), TEXT("-"), TEXT("1e"), TEXT("1e+"), TEXT("1e-"),
        TEXT("+ 1.5"), TEXT("1 .5"), TEXT("1e 2"), TEXT("1.5f"), TEXT("1.2.3"), TEXT("--1")
    };
    for (const TCHAR* Value : InvalidFloatValues)
    {
        Invalid = Candidate;
        Invalid.Variables.FindChecked(TEXT("board-rate")).Value = Value;
        ExpectRejected(FString(TEXT("Invalid float ")) + Value, Invalid);
    }
    Invalid = Candidate;
    Invalid.Visits.Remove(TEXT("element-1"));
    ExpectRejected(TEXT("Missing visit counter"), Invalid);
    Invalid = Candidate;
    Invalid.Visits.Add(TEXT("unknown-element"), 0);
    ExpectRejected(TEXT("Extra visit counter"), Invalid);
    Invalid.Visits.Remove(TEXT("element-1"));
    ExpectRejected(TEXT("Different visit IDs with the same count"), Invalid);
    Invalid = Candidate;
    Invalid.Visits.FindChecked(TEXT("element-1")) = -1;
    ExpectRejected(TEXT("Negative visit counter"), Invalid);

    const auto ExpectBusy = [this, Subsystem, &Error, &Sentinel, &Candidate, &TestSameState](const TCHAR* Label)
    {
        FArcweaveRuntimeState Output = Sentinel;
        TestFalse(FString(Label) + TEXT(" blocks capture"), Subsystem->CaptureState(Output, Error));
        TestFalse(FString(Label) + TEXT(" capture explains failure"), Error.IsEmpty());
        TestSameState(FString(Label) + TEXT(" preserves capture output"), Output, Sentinel);
        TestFalse(FString(Label) + TEXT(" blocks restore"), Subsystem->RestoreState(Candidate, Error));
        TestFalse(FString(Label) + TEXT(" restore explains failure"), Error.IsEmpty());
    };
    Subsystem->ActiveFetchRequest = FHttpModule::Get().CreateRequest();
    ExpectBusy(TEXT("Pending API import"));
    Subsystem->CancelFetch();
    Subsystem->bIsRunningScript = true;
    ExpectBusy(TEXT("Running script"));
    Subsystem->bIsRunningScript = false;
    TestTrue(TEXT("State remains capturable after busy operations"), Subsystem->CaptureState(Capture, Error));
    TestSameState(TEXT("Rejected busy operations preserve live state"), Capture, Saved);
    TestEqual(TEXT("Busy restore emits no notification"), Listener->RestoreEvents, 1);

    Subsystem->SetVariable(TEXT("global-health"), TEXT("not-an-integer"));
    Capture = Sentinel;
    TestFalse(TEXT("Capture rejects an invalid live value set through the public API"), Subsystem->CaptureState(Capture, Error));
    TestFalse(TEXT("Invalid live value capture explains failure"), Error.IsEmpty());
    TestSameState(TEXT("Invalid live value capture preserves its output"), Capture, Sentinel);
    TestEqual(TEXT("Capture does not change the invalid live value"), Project.CurrentVars.FindChecked(TEXT("global-health")).Value, FString(TEXT("not-an-integer")));
    Subsystem->SetVariable(TEXT("global-health"), Saved.Variables.FindChecked(TEXT("global-health")).Value);

    for (const TCHAR* Value : InvalidFloatValues)
    {
        const FString Label = FString(TEXT("Invalid live float ")) + Value;
        Subsystem->SetVariable(TEXT("board-rate"), Value);
        Capture = Sentinel;
        TestFalse(Label + TEXT(" blocks capture"), Subsystem->CaptureState(Capture, Error));
        TestFalse(Label + TEXT(" capture explains failure"), Error.IsEmpty());
        TestSameState(Label + TEXT(" preserves capture output"), Capture, Sentinel);
        TestEqual(Label + TEXT(" remains unchanged in the live project"),
            Project.CurrentVars.FindChecked(TEXT("board-rate")).Value, FString(Value));
    }
    Subsystem->SetVariable(TEXT("board-rate"), Saved.Variables.FindChecked(TEXT("board-rate")).Value);

    FArcweaveRuntimeState Boundaries = Saved;
    Boundaries.Variables.FindChecked(TEXT("global-health")).Value = TEXT("-2147483648");
    Boundaries.Variables.FindChecked(TEXT("component-health")).Value = TEXT("2147483647");
    Boundaries.Variables.FindChecked(TEXT("board-rate")).Value = TEXT("-123.5");
    TestTrue(TEXT("Int32 boundaries and a finite negative float restore"), Subsystem->RestoreState(Boundaries, Error));
    TestTrue(TEXT("Boundary values capture"), Subsystem->CaptureState(Capture, Error));
    TestSameState(TEXT("Boundary values are preserved"), Capture, Boundaries);
    TestTrue(TEXT("Original runtime values restore after boundary test"), Subsystem->RestoreState(Saved, Error));

    for (const TCHAR* Value : {
        TEXT("0"), TEXT("-0"), TEXT("+2.75"), TEXT(".5"), TEXT("-.5"), TEXT("1."),
        TEXT("1e3"), TEXT("1.25e-3"), TEXT("+1.25E+3"), TEXT(" \t2.75\r\n"),
        TEXT("1.7976931348623157e308")})
    {
        FArcweaveRuntimeState Valid = Saved;
        Valid.Variables.FindChecked(TEXT("board-rate")).Value = Value;
        const FString Label = FString(TEXT("Valid float ")) + Value;
        TestTrue(Label + TEXT(" restores"), Subsystem->RestoreState(Valid, Error));
        TestTrue(Label + TEXT(" captures"), Subsystem->CaptureState(Capture, Error));
        TestSameState(Label + TEXT(" roundtrips without changing its value"), Capture, Valid);
    }
    TestTrue(TEXT("Original runtime values restore after float tests"), Subsystem->RestoreState(Saved, Error));

    // Change object ordering at both the root and a nested attribute, preserving its meaning.
    const TSharedPtr<FJsonObject> Attribute = Root->GetObjectField(TEXT("attributes"))->GetObjectField(TEXT("board-health"));
    TSharedRef<FJsonObject> ReorderedValue = MakeShared<FJsonObject>();
    ReorderedValue->SetNumberField(TEXT("data"), 10);
    ReorderedValue->SetStringField(TEXT("type"), TEXT("integer"));
    Attribute->SetObjectField(TEXT("value"), ReorderedValue);
    TSharedRef<FJsonObject> ReorderedRoot = MakeShared<FJsonObject>();
    TArray<FString> Keys;
    Root->Values.GetKeys(Keys);
    for (int32 Index = Keys.Num() - 1; Index >= 0; --Index)
    {
        ReorderedRoot->SetField(Keys[Index], Root->Values.FindChecked(Keys[Index]));
    }
    FString CompactJson;
    FJsonSerializer::Serialize(ReorderedRoot, TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&CompactJson));
    UArcweaveSubsystem* Reimported = NewObject<UArcweaveSubsystem>();
    TestTrue(TEXT("Reordered compact project imports"), Reimported->ParseResponse(CompactJson));
    TestTrue(TEXT("Reordered project state captures"), Reimported->CaptureState(Capture, Error));
    TestEqual(TEXT("JSON order and whitespace do not change project identity"), Capture.ProjectFingerprint, Saved.ProjectFingerprint);
    TestTrue(TEXT("Snapshot restores into the equivalent reordered export"), Reimported->RestoreState(Saved, Error));
    TestTrue(TEXT("API-wrapped project imports"), Reimported->ParseResponse(TEXT("{\"project\":") + CompactJson + TEXT(",\"requestId\":\"unrelated\"}")));
    TestTrue(TEXT("Wrapped project state captures"), Reimported->CaptureState(Capture, Error));
    TestEqual(TEXT("API wrapper does not change project identity"), Capture.ProjectFingerprint, Saved.ProjectFingerprint);
    TestTrue(TEXT("Snapshot restores into the equivalent API export"), Reimported->RestoreState(Saved, Error));
    Root->GetObjectField(TEXT("elements"))->GetObjectField(TEXT("element-1"))->SetStringField(TEXT("content"), TEXT("A changed story."));
    FString ChangedJson;
    FJsonSerializer::Serialize(Root.ToSharedRef(), TJsonWriterFactory<>::Create(&ChangedJson));
    TestTrue(TEXT("Changed project imports"), Reimported->ParseResponse(ChangedJson));
    TestTrue(TEXT("Changed project state captures"), Reimported->CaptureState(Capture, Error));
    TestTrue(TEXT("Changed authored content changes project identity"), Capture.ProjectFingerprint != Saved.ProjectFingerprint);
    TestFalse(TEXT("Previous snapshot cannot restore into a changed story with identical IDs"), Reimported->RestoreState(Saved, Error));

#if PLATFORM_WINDOWS || PLATFORM_MAC
    Listener->StateToRestore = Saved;
    Listener->CaptureAttempt = Sentinel;
    Listener->bProbeDuringScript = true;
    bool bSuccess = false;
    const int32 RestoreEventsBeforeScript = Listener->RestoreEvents;
    Subsystem->TranspileObject(TEXT("element-1"), bSuccess);
    Listener->bProbeDuringScript = false;
    TestTrue(TEXT("Authored node executes through the interpreter"), bSuccess);
    TestEqual(TEXT("Normal node execution emits its authored event"), Listener->ArcscriptEvents, 1);
    TestEqual(TEXT("Normal node execution updates variables"), Project.CurrentVars.FindChecked(TEXT("global-health")).Value, FString(TEXT("112")));
    TestEqual(TEXT("Normal node execution applies its authored resetVisits event"), Project.Visits.FindChecked(TEXT("element-1")), 0);
    TestFalse(TEXT("Capture is rejected from a real script callback"), Listener->bCaptureDuringScriptSucceeded);
    TestFalse(TEXT("Restore is rejected from a real script callback"), Listener->bRestoreDuringScriptSucceeded);
    TestFalse(TEXT("Callback capture explains rejection"), Listener->CaptureError.IsEmpty());
    TestFalse(TEXT("Callback restore explains rejection"), Listener->RestoreError.IsEmpty());
    TestSameState(TEXT("Callback capture leaves output untouched"), Listener->CaptureAttempt, Sentinel);
    TestEqual(TEXT("Callback restore emitted no restore notification"), Listener->RestoreEvents, RestoreEventsBeforeScript);
    const int32 VariableEventsBeforeRestore = Listener->VariableEvents;
    TestTrue(TEXT("State restores after script execution completes"), Subsystem->RestoreState(Saved, Error));
    TestEqual(TEXT("Restore does not rerun the node event"), Listener->ArcscriptEvents, 1);
    TestEqual(TEXT("Restore does not repeat variable-change callbacks"), Listener->VariableEvents, VariableEventsBeforeRestore);
    TestTrue(TEXT("Post-script restored state captures"), Subsystem->CaptureState(Capture, Error));
    TestSameState(TEXT("Restore rewinds variables and visits without executing the node"), Capture, Saved);

    const FArcscriptTranspilerOutput Condition = Subsystem->RunTranspiler(
        TEXT("<pre><code>health == 111 and castle.health == 37 and hero.health == 42 and ")
        TEXT("castle.is_open == false and castle.rate == 2.75 and visits() == 4</code></pre>"),
        TEXT("element-1"), Project.CurrentVars, Project.Visits);
    TestTrue(TEXT("Interpreter conditions see restored global, board, component and visit state"), Condition.ConditionResult);
    Subsystem->RunTranspiler(TEXT("<pre><code>reset(castle.health)</code></pre>"),
        TEXT("element-1"), Project.CurrentVars, Project.Visits);
    TestEqual(TEXT("Reset after restore uses the authored default"), Project.CurrentVars.FindChecked(TEXT("board-health")).Value, FString(TEXT("10")));
    Subsystem->RunTranspiler(TEXT("<pre><code>resetAll(hero.health)</code></pre>"),
        TEXT("element-1"), Project.CurrentVars, Project.Visits);
    TestEqual(TEXT("ResetAll after restore resets globals to authored defaults"), Project.CurrentVars.FindChecked(TEXT("global-health")).Value, FString(TEXT("100")));
    TestEqual(TEXT("ResetAll after restore keeps its excluded component value"), Project.CurrentVars.FindChecked(TEXT("component-health")).Value, FString(TEXT("42")));
    TestEqual(TEXT("ResetAll after restore resets booleans to authored defaults"), Project.CurrentVars.FindChecked(TEXT("board-open")).Value, FString(TEXT("true")));
#else
    AddWarning(TEXT("Interpreter roundtrip checks require Windows or macOS, the plugin's supported interpreter platforms."));
#endif

    return true;
}

#endif
