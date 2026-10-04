#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSubsystem.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveStartingElementTest,
    "Arcweave.Project.StartingElement",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveStartingElementTest::RunTest(const FString& Parameters)
{
    const FString Json = TEXT(R"JSON({
        "name": "Starting element test",
        "startingElement": "entry-b",
        "boards": {
            "board-1": {"name": "Main", "elements": ["entry-a", "entry-b"]}
        },
        "elements": {
            "entry-a": {"title": "Other", "content": "<p>Other element.</p>"},
            "entry-b": {
                "title": "Start",
                "content": "<pre><code>started = true</code></pre><p>Selected start.</p>"
            }
        },
        "components": {},
        "variables": {
            "started-variable": {"name": "started", "type": "boolean", "value": false, "cType": "global"}
        }
    })JSON");

    UArcweaveSubsystem* Subsystem = NewObject<UArcweaveSubsystem>();
    TestTrue(TEXT("A new project has no starting element"), Subsystem->GetArcweaveProjectData().StartingElementId.IsEmpty());
    if (!TestTrue(TEXT("A plain export imports"), Subsystem->ParseResponse(Json)))
    {
        return false;
    }

    const FArcweaveProjectData Project = Subsystem->GetArcweaveProjectData();
    TestEqual(TEXT("The authored starting element is exposed through project data"), Project.StartingElementId, FString(TEXT("entry-b")));
    TestEqual(TEXT("Import does not visit the starting element"), Project.Visits.FindChecked(TEXT("entry-b")), 0);
    TestEqual(TEXT("Import does not execute starting-element code"), Project.CurrentVars.FindChecked(TEXT("started-variable")).Value, FString(TEXT("false")));

#if PLATFORM_WINDOWS || PLATFORM_MAC
    bool bSuccess = false;
    const FArcweaveElementData Element = Subsystem->TranspileObject(Project.StartingElementId, bSuccess);
    TestTrue(TEXT("The imported ID can be passed directly to TranspileObject"), bSuccess);
    TestEqual(TEXT("Execution selects the authored start, not the first board element"), Element.Id, Project.StartingElementId);
    TestEqual(TEXT("The selected element produces its content"), Element.Content, FString(TEXT("Selected start.")));
    const FArcweaveProjectData Executed = Subsystem->GetArcweaveProjectData();
    TestEqual(TEXT("Explicit execution runs the starting-element code"), Executed.CurrentVars.FindChecked(TEXT("started-variable")).Value, FString(TEXT("true")));
    TestEqual(TEXT("Explicit execution increments its visit count"), Executed.Visits.FindChecked(TEXT("entry-b")), 1);
    TestEqual(TEXT("The other element remains unvisited"), Executed.Visits.FindChecked(TEXT("entry-a")), 0);
#endif

    const FString OtherStart = Json.Replace(TEXT("\"startingElement\": \"entry-b\""), TEXT("\"startingElement\": \"entry-a\""));
    const FString Wrapped = TEXT("{\"startingElement\":\"outer-value\",\"project\":") + OtherStart + TEXT("}");
    if (!TestTrue(TEXT("An API project envelope imports"), Subsystem->ParseResponse(Wrapped)))
    {
        return false;
    }
    TestEqual(TEXT("Reimport reads the new start from inside the project envelope"), Subsystem->GetArcweaveProjectData().StartingElementId, FString(TEXT("entry-a")));

    const FString UnsetExports[] = {
        Json.Replace(TEXT("\"startingElement\": \"entry-b\","), TEXT("")),
        Json.Replace(TEXT("\"startingElement\": \"entry-b\""), TEXT("\"startingElement\": null")),
        Json.Replace(TEXT("\"startingElement\": \"entry-b\""), TEXT("\"startingElement\": \"\""))
    };
    for (bool bWrapped : {false, true})
    {
        for (const FString& Unset : UnsetExports)
        {
            if (!TestTrue(TEXT("Restore a known starting element before reimport"), Subsystem->ParseResponse(Json)))
            {
                return false;
            }
            const FString Import = bWrapped ? TEXT("{\"project\":") + Unset + TEXT("}") : Unset;
            if (!TestTrue(TEXT("An export without a starting element still imports"), Subsystem->ParseResponse(Import)))
            {
                return false;
            }
            TestTrue(TEXT("Missing, null, and empty starts clear the previous value"), Subsystem->GetArcweaveProjectData().StartingElementId.IsEmpty());
        }
    }

    if (!TestTrue(TEXT("Reload the original starting element"), Subsystem->ParseResponse(Json)))
    {
        return false;
    }
    TestFalse(TEXT("An incomplete export is rejected"), Subsystem->ParseResponse(TEXT("{\"name\":\"Incomplete\",\"startingElement\":\"entry-a\"}")));
    TestEqual(TEXT("A rejected import preserves the loaded starting element"), Subsystem->GetArcweaveProjectData().StartingElementId, FString(TEXT("entry-b")));
    return true;
}

#endif
