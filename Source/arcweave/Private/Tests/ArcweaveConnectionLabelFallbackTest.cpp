#if WITH_DEV_AUTOMATION_TESTS

#include "ArcscriptTranspilerOutput.h"
#include "ArcweaveSubsystem.h"
#include "Misc/AutomationTest.h"

// Connections without label text show the element they lead to, as in play mode.
// An empty label is valid, so any logged error fails this test.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveConnectionLabelFallbackTest,
    "Arcweave.Project.ConnectionLabelFallback",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveConnectionLabelFallbackTest::RunTest(const FString& Parameters)
{
    const FString Json = TEXT(R"JSON({
        "name": "Connection label fallback test",
        "startingElement": "healer",
        "boards": {
            "board-1": {
                "name": "Main",
                "elements": ["healer", "help", "pay", "untitled", "long", "empty", "single", "single-labelled", "single-code", "single-branch", "ending"],
                "jumpers": ["jumper-1"],
                "branches": ["branch-1", "branch-none"],
                "connections": [
                    "c-empty", "c-labelled", "c-code-only", "c-untitled", "c-long", "c-empty-element", "c-jumper", "c-branch",
                    "c-branch-yes", "c-branch-no", "c-single", "c-single-labelled", "c-single-code", "c-dead", "c-dead-out", "c-alive"
                ]
            },
            "board-2": {
                "name": "Elsewhere",
                "elements": ["far"],
                "connections": []
            }
        },
        "elements": {
            "healer": {
                "title": "<p>Healer</p>",
                "content": "<p>Greetings traveller.</p>",
                "outputs": ["c-empty", "c-labelled", "c-code-only", "c-untitled", "c-long", "c-empty-element", "c-jumper", "c-branch"]
            },
            "help": {"title": "<p>Help</p>", "content": "<p>Of course.</p>", "outputs": []},
            "pay": {"title": "<p>Pay</p>", "content": "<p>Thank you.</p>", "outputs": []},
            "untitled": {
                "title": "",
                "content": "<pre><code>money = 1</code></pre><p></p><p>The healer <strong>nods</strong>.</p><p>Second paragraph</p>",
                "outputs": []
            },
            "long": {
                "title": "",
                "content": "<p>The healer tells a long story about the old war, the lost city and the river that ran dry.</p>",
                "outputs": []
            },
            "empty": {"title": "", "content": "", "outputs": []},
            "far": {"title": "<p>Far away</p>", "content": "", "outputs": []},
            "single": {"title": "Single", "content": "", "outputs": ["c-single"]},
            "single-labelled": {"title": "Single labelled", "content": "", "outputs": ["c-single-labelled"]},
            "single-code": {"title": "Single code", "content": "", "outputs": ["c-single-code"]},
            "single-branch": {"title": "Single branch", "content": "", "outputs": ["c-dead", "c-alive"]},
            "ending": {"title": "Ending", "content": "", "outputs": []}
        },
        "jumpers": {
            "jumper-1": {"elementId": "far"}
        },
        "branches": {
            "branch-1": {"conditions": {"ifCondition": "cond-if", "elseIfConditions": [], "elseCondition": "cond-else"}},
            "branch-none": {"conditions": {"ifCondition": "cond-none", "elseIfConditions": []}}
        },
        "conditions": {
            "cond-if": {"output": "c-branch-yes", "script": "money > 3"},
            "cond-else": {"output": "c-branch-no"},
            "cond-none": {"output": "c-dead-out", "script": "false"}
        },
        "connections": {
            "c-empty": {"label": null, "sourceid": "healer", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-labelled": {"label": "<p>Ask for help</p>", "sourceid": "healer", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-code-only": {"label": "<pre><code>money = 5</code></pre>", "sourceid": "healer", "targetid": "pay", "sourceType": "elements", "targetType": "elements"},
            "c-untitled": {"label": null, "sourceid": "healer", "targetid": "untitled", "sourceType": "elements", "targetType": "elements"},
            "c-long": {"label": null, "sourceid": "healer", "targetid": "long", "sourceType": "elements", "targetType": "elements"},
            "c-empty-element": {"label": null, "sourceid": "healer", "targetid": "empty", "sourceType": "elements", "targetType": "elements"},
            "c-jumper": {"label": null, "sourceid": "healer", "targetid": "jumper-1", "sourceType": "elements", "targetType": "jumpers"},
            "c-branch": {"label": null, "sourceid": "healer", "targetid": "branch-1", "sourceType": "elements", "targetType": "branches"},
            "c-branch-yes": {"label": "<p>Pay up</p>", "sourceid": "branch-1", "targetid": "pay", "sourceType": "branches", "targetType": "elements"},
            "c-branch-no": {"label": null, "sourceid": "branch-1", "targetid": "help", "sourceType": "branches", "targetType": "elements"},
            "c-single": {"label": null, "sourceid": "single", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-single-labelled": {"label": "<p>Continue</p>", "sourceid": "single-labelled", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-single-code": {"label": "<pre><code>money = 7</code></pre>", "sourceid": "single-code", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-dead": {"label": "<p>Never shown</p>", "sourceid": "single-branch", "targetid": "branch-none", "sourceType": "elements", "targetType": "branches"},
            "c-dead-out": {"label": null, "sourceid": "branch-none", "targetid": "help", "sourceType": "branches", "targetType": "elements"},
            "c-alive": {"label": null, "sourceid": "single-branch", "targetid": "help", "sourceType": "elements", "targetType": "elements"}
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
    const FArcweaveBoardData* MainBoard = Project.Boards.FindByPredicate(
        [](const FArcweaveBoardData& Data) { return Data.BoardId == TEXT("board-1"); });
    if (!TestNotNull(TEXT("The main board imports"), MainBoard))
    {
        return false;
    }
    const FArcweaveBoardData& Board = *MainBoard;
    const auto Label = [Subsystem, &Board](const TCHAR* ConnectionId)
    {
        return Subsystem->TranspileConnectionLabel(Subsystem->GetConnectionsData(Board, ConnectionId), Board);
    };
    const auto Element = [&Board](const TCHAR* ElementId)
    {
        return *Board.Elements.FindByPredicate([ElementId](const FArcweaveElementData& Data) { return Data.Id == ElementId; });
    };
    const auto Money = [Subsystem]()
    {
        return Subsystem->GetArcweaveProjectData().CurrentVars.FindChecked(TEXT("money-variable")).Value;
    };

    const FArcweaveConnectionsData Empty = Subsystem->GetConnectionsData(Board, TEXT("c-empty"));
    bool bSuccess = false;
    const FArcscriptTranspilerOutput Direct = Subsystem->TranspileConnection(Empty.Id, Empty.Label, Empty.Sourceid, bSuccess, true, Board);
    TestTrue(TEXT("An empty label is not a transpile failure"), bSuccess);
    TestTrue(TEXT("An empty label transpiles to nothing"), Direct.Output.IsEmpty());

    TestEqual(TEXT("A label is shown as before"), Label(TEXT("c-labelled")), FString(TEXT("Ask for help")));
    TestEqual(TEXT("An empty label shows the target's title"), Label(TEXT("c-empty")), FString(TEXT("Help")));
    TestEqual(TEXT("Without a title, the first paragraph with text is shown"), Label(TEXT("c-untitled")), FString(TEXT("The healer nods.")));
    TestEqual(TEXT("Long content is cut to 70 characters"), Label(TEXT("c-long")),
        FString(TEXT("The healer tells a long story about the old war, the lost city and the...")));
    TestEqual(TEXT("An element without title or content is marked empty"), Label(TEXT("c-empty-element")), FString(TEXT("[ Empty element ]")));
    TestEqual(TEXT("A jumper shows the element it jumps to"), Label(TEXT("c-jumper")), FString(TEXT("Far away")));

    TestTrue(TEXT("Several outputs are options"), Subsystem->HasOptions(Element(TEXT("healer")), Board));
    TestFalse(TEXT("A single output without a label is not an option"), Subsystem->HasOptions(Element(TEXT("single")), Board));
    TestTrue(TEXT("A single labelled output is an option"), Subsystem->HasOptions(Element(TEXT("single-labelled")), Board));
    TestFalse(TEXT("An element without outputs has no options"), Subsystem->HasOptions(Element(TEXT("ending")), Board));

#if PLATFORM_WINDOWS || PLATFORM_MAC
    TestEqual(TEXT("A label with only code shows the target's title"), Label(TEXT("c-code-only")), FString(TEXT("Pay")));

    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    TestEqual(TEXT("A branch shows the element it leads to"), Label(TEXT("c-branch")), FString(TEXT("Help")));
    Subsystem->SetVariable(TEXT("money-variable"), TEXT("5"));
    TestEqual(TEXT("A branch shows the label after it"), Label(TEXT("c-branch")), FString(TEXT("Pay up")));

    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    TestFalse(TEXT("A single output with only code is not an option"), Subsystem->HasOptions(Element(TEXT("single-code")), Board));
    TestEqual(TEXT("Checking for options does not change variables"), Money(), FString(TEXT("0")));
    TestFalse(TEXT("An output whose branch leads nowhere is not an option"), Subsystem->HasOptions(Element(TEXT("single-branch")), Board));
#endif

    return true;
}

#endif
