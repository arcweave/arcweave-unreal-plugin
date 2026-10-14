#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSubsystem.h"
#include "Misc/AutomationTest.h"

// Plain-text labels must not reach the Arcscript parser (issue #33); any logged
// ParseErrorException fails this test.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveConnectionLabelTest,
    "Arcweave.Project.ConnectionLabels",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveConnectionLabelTest::RunTest(const FString& Parameters)
{
    const FString Json = TEXT(R"JSON({
        "name": "Connection label test",
        "startingElement": "healer",
        "boards": {
            "board-1": {
                "name": "Main",
                "elements": ["healer", "help", "pay"],
                "connections": ["plain-connection", "code-connection", "attributed-connection"]
            }
        },
        "elements": {
            "healer": {
                "title": "Healer",
                "content": "<p>Greetings traveller, may I help you?</p>",
                "outputs": ["plain-connection", "code-connection", "attributed-connection"]
            },
            "help": {"title": "Help", "content": "<p>Of course.</p>", "outputs": []},
            "pay": {"title": "Pay", "content": "<p>Thank you.</p>", "outputs": []}
        },
        "connections": {
            "plain-connection": {
                "type": "Bezier",
                "label": "<p>Ask for help</p>",
                "sourceid": "healer",
                "targetid": "help",
                "sourceType": "elements",
                "targetType": "elements"
            },
            "code-connection": {
                "type": "Bezier",
                "label": "<pre><code>money = 5</code></pre><p>Pay the healer</p>",
                "sourceid": "healer",
                "targetid": "pay",
                "sourceType": "elements",
                "targetType": "elements"
            },
            "attributed-connection": {
                "type": "Bezier",
                "label": "<pre attr='hep'><code rem='jjk'>money = 7</code></pre><p>Tip the healer</p>",
                "sourceid": "healer",
                "targetid": "pay",
                "sourceType": "elements",
                "targetType": "elements"
            }
        },
        "components": {},
        "variables": {
            "money-variable": {"name": "money", "type": "integer", "value": 0, "cType": "global"}
        }
    })JSON");

    UArcweaveSubsystem* Subsystem = NewObject<UArcweaveSubsystem>();
    if (!TestTrue(TEXT("The project imports"), Subsystem->ParseResponse(Json)))
    {
        return false;
    }

    const FArcweaveProjectData Project = Subsystem->GetArcweaveProjectData();
    if (!TestEqual(TEXT("One board imports"), Project.Boards.Num(), 1))
    {
        return false;
    }
    const FArcweaveBoardData& Board = Project.Boards[0];
    const FArcweaveConnectionsData Plain = Subsystem->GetConnectionsData(Board, TEXT("plain-connection"));
    const FArcweaveConnectionsData Code = Subsystem->GetConnectionsData(Board, TEXT("code-connection"));
    const FArcweaveConnectionsData Attributed = Subsystem->GetConnectionsData(Board, TEXT("attributed-connection"));
    TestEqual(TEXT("A label without code is stored as plain text"), Plain.Label, FString(TEXT("Ask for help")));
    TestTrue(TEXT("A code block with tag attributes is kept for the transpiler"), Attributed.Label.StartsWith(TEXT("<pre attr=")));

    const auto Money = [Subsystem]()
    {
        return Subsystem->GetArcweaveProjectData().CurrentVars.FindChecked(TEXT("money-variable")).Value;
    };

    TestEqual(TEXT("A plain board label resolves to itself"), Subsystem->TranspileConnectionLabel(Plain, Board), FString(TEXT("Ask for help")));

    const FArcweaveConnectionsData* RawPlain = Project.Connections.FindByPredicate(
        [](const FArcweaveConnectionsData& Connection) { return Connection.Id == TEXT("plain-connection"); });
    if (TestNotNull(TEXT("The project-level connection imports"), RawPlain))
    {
        TestEqual(TEXT("A project-level HTML label without code is stripped"), Subsystem->TranspileConnectionLabel(*RawPlain, Board), FString(TEXT("Ask for help")));
    }

    bool bSuccess = false;
    const FArcscriptTranspilerOutput Direct = Subsystem->TranspileConnection(
        Plain.Id, TEXT("<p>Ask for help</p>"), Plain.Sourceid, bSuccess, false, Board);
    TestTrue(TEXT("A plain label succeeds without the transpiler"), bSuccess);
    TestEqual(TEXT("Unstripped plain labels are returned unchanged"), Direct.Output, FString(TEXT("<p>Ask for help</p>")));

    Subsystem->UpdateVariablesFromConnection(Plain);
    TestEqual(TEXT("A plain label does not change variables"), Money(), FString(TEXT("0")));

#if PLATFORM_WINDOWS || PLATFORM_MAC
    TestEqual(TEXT("A label with code still runs through the transpiler"), Subsystem->TranspileConnectionLabel(Code, Board), FString(TEXT("Pay the healer")));

    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    Subsystem->UpdateVariablesFromConnection(Code);
    TestEqual(TEXT("A label with code still updates variables"), Money(), FString(TEXT("5")));

    TestEqual(TEXT("A code block with tag attributes runs through the transpiler"), Subsystem->TranspileConnectionLabel(Attributed, Board), FString(TEXT("Tip the healer")));
    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    Subsystem->UpdateVariablesFromConnection(Attributed);
    TestEqual(TEXT("A code block with tag attributes updates variables"), Money(), FString(TEXT("7")));
#endif

    return true;
}

#endif
