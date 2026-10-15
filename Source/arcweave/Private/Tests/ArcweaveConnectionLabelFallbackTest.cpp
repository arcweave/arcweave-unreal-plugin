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
                "elements": ["healer", "help", "pay", "untitled", "long", "empty", "single", "single-labelled", "single-code", "single-branch", "single-reset", "ending"],
                "jumpers": ["jumper-1"],
                "branches": ["branch-1", "branch-none", "branch-a", "branch-b", "branch-loop"],
                "connections": [
                    "c-empty", "c-labelled", "c-code-only", "c-untitled", "c-long", "c-empty-element", "c-jumper", "c-branch",
                    "c-branch-yes", "c-branch-no", "c-single", "c-single-labelled", "c-single-code", "c-dead", "c-dead-out", "c-alive",
                    "c-empty-html", "c-nested", "c-a-out", "c-b-yes", "c-b-no", "c-loop", "c-loop-back", "c-single-reset"
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
                "outputs": ["c-empty", "c-labelled", "c-code-only", "c-untitled", "c-long", "c-empty-element", "c-jumper", "c-branch", "c-empty-html", "c-nested", "c-loop"]
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
            "single-reset": {"title": "Single reset", "content": "", "outputs": ["c-single-reset"]},
            "ending": {"title": "Ending", "content": "", "outputs": []}
        },
        "jumpers": {
            "jumper-1": {"elementId": "far"}
        },
        "branches": {
            "branch-1": {"conditions": {"ifCondition": "cond-if", "elseIfConditions": [], "elseCondition": "cond-else"}},
            "branch-none": {"conditions": {"ifCondition": "cond-none", "elseIfConditions": []}},
            "branch-a": {"conditions": {"ifCondition": "cond-a", "elseIfConditions": []}},
            "branch-b": {"conditions": {"ifCondition": "cond-b", "elseIfConditions": [], "elseCondition": "cond-b-else"}},
            "branch-loop": {"conditions": {"ifCondition": "cond-loop", "elseIfConditions": []}}
        },
        "conditions": {
            "cond-if": {"output": "c-branch-yes", "script": "money > 3"},
            "cond-else": {"output": "c-branch-no"},
            "cond-none": {"output": "c-dead-out", "script": "false"},
            "cond-a": {"output": "c-a-out", "script": "true"},
            "cond-b": {"output": "c-b-yes", "script": "visits() == 1"},
            "cond-b-else": {"output": "c-b-no"},
            "cond-loop": {"output": "c-loop-back", "script": "true"}
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
            "c-alive": {"label": null, "sourceid": "single-branch", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-empty-html": {"label": "<p></p>", "sourceid": "healer", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-nested": {"label": null, "sourceid": "healer", "targetid": "branch-a", "sourceType": "elements", "targetType": "branches"},
            "c-a-out": {"label": null, "sourceid": "branch-a", "targetid": "branch-b", "sourceType": "branches", "targetType": "branches"},
            "c-b-yes": {"label": null, "sourceid": "branch-b", "targetid": "pay", "sourceType": "branches", "targetType": "elements"},
            "c-b-no": {"label": null, "sourceid": "branch-b", "targetid": "help", "sourceType": "branches", "targetType": "elements"},
            "c-loop": {"label": null, "sourceid": "healer", "targetid": "branch-loop", "sourceType": "elements", "targetType": "branches"},
            "c-loop-back": {"label": null, "sourceid": "branch-loop", "targetid": "branch-loop", "sourceType": "branches", "targetType": "branches"},
            "c-single-reset": {"label": "<pre><code>resetVisits()</code></pre>", "sourceid": "single-reset", "targetid": "help", "sourceType": "elements", "targetType": "elements"}
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

    const FArcweaveConnectionsData* RawEmptyHtml = Project.Connections.FindByPredicate(
        [](const FArcweaveConnectionsData& Connection) { return Connection.Id == TEXT("c-empty-html"); });
    if (TestNotNull(TEXT("The project-level connection imports"), RawEmptyHtml))
    {
        TestEqual(TEXT("A project-level label with only empty HTML shows the target's title"),
            Subsystem->TranspileConnectionLabel(*RawEmptyHtml, Board), FString(TEXT("Help")));
    }

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

    Subsystem->IncrementVisits(TEXT("healer"));
    TestEqual(TEXT("Conditions after a branch use the element the option starts from"), Label(TEXT("c-nested")), FString(TEXT("Pay")));

    // HasOptions on the healer also follows this loop, so the warning appears more than once
    AddExpectedMessagePlain(TEXT("leads to a loop of branches"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 0);
    TestTrue(TEXT("A loop of branches leads nowhere"), Label(TEXT("c-loop")).IsEmpty());

    TestFalse(TEXT("A single output that resets visits is not an option"), Subsystem->HasOptions(Element(TEXT("single-reset")), Board));
    TestEqual(TEXT("Checking for options does not reset visits"),
        Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 1);
#endif

    return true;
}

#endif
