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
                "elements": ["healer", "help", "pay", "untitled", "long", "empty", "leading-empty", "plain-choices", "code-only", "tea", "fish", "strong", "single", "single-labelled", "single-code", "single-branch", "single-reset", "reset-branch", "ending"],
                "jumpers": ["jumper-1"],
                "branches": ["branch-1", "branch-none", "branch-a", "branch-b", "branch-loop", "branch-reset",
                    "branch-wrapped", "branch-bad", "branch-blank", "branch-noif", "branch-emptyvar", "branch-noout"],
                "connections": [
                    "c-empty", "c-labelled", "c-code-only", "c-untitled", "c-long", "c-empty-element", "c-jumper", "c-branch",
                    "c-branch-yes", "c-branch-no", "c-single", "c-single-labelled", "c-single-code", "c-dead", "c-dead-out", "c-alive",
                    "c-empty-html", "c-nested", "c-a-out", "c-b-yes", "c-b-no", "c-loop", "c-loop-back", "c-single-reset", "c-reset-branch", "c-reset-out", "c-leading-empty", "c-plain-1", "c-plain-2",
                    "c-code-only-el", "c-tea", "c-fish", "c-strong", "c-dead2", "c-wrapped", "c-wrapped-yes", "c-wrapped-no",
                    "c-broken", "c-bad-branch", "c-bad-out", "c-blank", "c-blank-out", "c-blank-else", "c-noif", "c-noif-else",
                    "c-emptyvar", "c-emptyvar-out", "c-noout"
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
                "content": "<pre><code>money = 1</code></pre><p>The healer <strong>nods</strong>.</p><p>Second paragraph</p>",
                "outputs": []
            },
            "long": {
                "title": "",
                "content": "<p>The healer tells a long story about the old war, the lost city and the river that ran dry.</p>",
                "outputs": []
            },
            "empty": {"title": "", "content": "", "outputs": []},
            "leading-empty": {"title": "", "content": "<p></p><p>Text after an empty paragraph</p>", "outputs": []},
            "plain-choices": {"title": "Plain choices", "content": "", "outputs": ["c-plain-1", "c-plain-2"]},
            "code-only": {"title": "", "content": "<pre> <code>money = 1</code> </pre>", "outputs": []},
            "tea": {"title": "", "content": "<p>Tea &amp; biscuits</p>", "outputs": []},
            "fish": {"title": "<p>Fish &amp; chips</p>", "content": "", "outputs": []},
            "strong": {"title": "", "content": "<p><strong>abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcde</strong></p>", "outputs": []},
            "far": {"title": "<p>Far away</p>", "content": "", "outputs": []},
            "single": {"title": "Single", "content": "", "outputs": ["c-single"]},
            "single-labelled": {"title": "Single labelled", "content": "", "outputs": ["c-single-labelled"]},
            "single-code": {"title": "Single code", "content": "", "outputs": ["c-single-code"]},
            "single-branch": {"title": "Single branch", "content": "", "outputs": ["c-dead", "c-alive"]},
            "single-reset": {"title": "Single reset", "content": "", "outputs": ["c-single-reset"]},
            "reset-branch": {"title": "Reset branch", "content": "", "outputs": ["c-reset-branch"]},
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
            "branch-loop": {"conditions": {"ifCondition": "cond-loop", "elseIfConditions": []}},
            "branch-reset": {"conditions": {"ifCondition": "cond-reset", "elseIfConditions": []}},
            "branch-wrapped": {"conditions": {"ifCondition": "cond-wrapped", "elseIfConditions": [], "elseCondition": "cond-wrapped-else"}},
            "branch-bad": {"conditions": {"ifCondition": "cond-bad", "elseIfConditions": [], "elseCondition": "cond-bad-else"}},
            "branch-blank": {"conditions": {"ifCondition": "cond-blank-if", "elseIfConditions": ["cond-blank-p", "cond-blank-pm"], "elseCondition": "cond-blank-else"}},
            "branch-noif": {"conditions": {"elseIfConditions": [], "elseCondition": "cond-noif-else"}},
            "branch-emptyvar": {"conditions": {"ifCondition": "cond-emptyvar", "elseIfConditions": []}},
            "branch-noout": {"conditions": {"ifCondition": "cond-noout", "elseIfConditions": []}}
        },
        "conditions": {
            "cond-if": {"output": "c-branch-yes", "script": "money > 3"},
            "cond-else": {"output": "c-branch-no"},
            "cond-none": {"output": "c-dead-out", "script": "false"},
            "cond-a": {"output": "c-a-out", "script": "true"},
            "cond-b": {"output": "c-b-yes", "script": "visits() == 1"},
            "cond-b-else": {"output": "c-b-no"},
            "cond-loop": {"output": "c-loop-back", "script": "true"},
            "cond-reset": {"output": "c-reset-out", "script": "resetVisits() or true"},
            "cond-wrapped": {"output": "c-wrapped-yes", "script": "<p>money &gt; 3</p>"},
            "cond-wrapped-else": {"output": "c-wrapped-no"},
            "cond-bad": {"output": "c-bad-out", "script": "undefined_name > 1"},
            "cond-bad-else": {"output": "c-bad-out"},
            "cond-blank-if": {"output": "c-blank-out", "script": null},
            "cond-blank-p": {"output": "c-blank-out", "script": "<p></p>"},
            "cond-blank-pm": {"output": "c-blank-out", "script": "<p><br class=\"ProseMirror-trailingBreak\"></p>"},
            "cond-blank-else": {"output": "c-blank-else"},
            "cond-noif-else": {"output": "c-noif-else"},
            "cond-emptyvar": {"output": "c-emptyvar-out", "script": "empty"},
            "cond-noout": {"output": "", "script": "true"}
        },)JSON")
    // Split in two: MSVC limits a single string literal to about 16 KB
    TEXT(R"JSON(
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
            "c-single-reset": {"label": "<pre><code>resetVisits()</code></pre>", "sourceid": "single-reset", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-reset-branch": {"label": null, "sourceid": "reset-branch", "targetid": "branch-reset", "sourceType": "elements", "targetType": "branches"},
            "c-reset-out": {"label": "<p>After reset</p>", "sourceid": "branch-reset", "targetid": "help", "sourceType": "branches", "targetType": "elements"},
            "c-leading-empty": {"label": null, "sourceid": "healer", "targetid": "leading-empty", "sourceType": "elements", "targetType": "elements"},
            "c-plain-1": {"label": null, "sourceid": "plain-choices", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-plain-2": {"label": null, "sourceid": "plain-choices", "targetid": "pay", "sourceType": "elements", "targetType": "elements"},)JSON")
    TEXT(R"JSON(
            "c-code-only-el": {"label": null, "sourceid": "healer", "targetid": "code-only", "sourceType": "elements", "targetType": "elements"},
            "c-tea": {"label": null, "sourceid": "healer", "targetid": "tea", "sourceType": "elements", "targetType": "elements"},
            "c-fish": {"label": null, "sourceid": "healer", "targetid": "fish", "sourceType": "elements", "targetType": "elements"},
            "c-strong": {"label": null, "sourceid": "healer", "targetid": "strong", "sourceType": "elements", "targetType": "elements"},
            "c-dead2": {"label": null, "sourceid": "healer", "targetid": "branch-none", "sourceType": "elements", "targetType": "branches"},
            "c-wrapped": {"label": null, "sourceid": "healer", "targetid": "branch-wrapped", "sourceType": "elements", "targetType": "branches"},
            "c-wrapped-yes": {"label": null, "sourceid": "cond-wrapped", "targetid": "pay", "sourceType": "conditions", "targetType": "elements"},
            "c-wrapped-no": {"label": null, "sourceid": "cond-wrapped-else", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-broken": {"label": "<pre><code>undefined_name = 1</code></pre><p>Broken</p>", "sourceid": "healer", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-bad-branch": {"label": null, "sourceid": "healer", "targetid": "branch-bad", "sourceType": "elements", "targetType": "branches"},
            "c-bad-out": {"label": "<p>Should not show</p>", "sourceid": "cond-bad", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-blank": {"label": null, "sourceid": "healer", "targetid": "branch-blank", "sourceType": "elements", "targetType": "branches"},
            "c-blank-out": {"label": "<p>Blank taken</p>", "sourceid": "cond-blank-if", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-blank-else": {"label": "<p>Blank skipped</p>", "sourceid": "cond-blank-else", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-noif": {"label": null, "sourceid": "healer", "targetid": "branch-noif", "sourceType": "elements", "targetType": "branches"},
            "c-noif-else": {"label": "<p>No if</p>", "sourceid": "cond-noif-else", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-emptyvar": {"label": null, "sourceid": "healer", "targetid": "branch-emptyvar", "sourceType": "elements", "targetType": "branches"},
            "c-emptyvar-out": {"label": "<p>Variable named empty</p>", "sourceid": "cond-emptyvar", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-noout": {"label": "<p>No output</p>", "sourceid": "healer", "targetid": "branch-noout", "sourceType": "elements", "targetType": "branches"}
        },
        "components": {},
        "variables": {
            "money-variable": {"name": "money", "type": "integer", "value": 0, "cType": "global"},
            "empty-variable": {"name": "empty", "type": "boolean", "value": true, "cType": "global"}
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
    TestEqual(TEXT("Without a title, the first paragraph is shown without code"), Label(TEXT("c-untitled")), FString(TEXT("The healer nods.")));
    TestEqual(TEXT("Like play mode, an empty first paragraph leaves the element empty"), Label(TEXT("c-leading-empty")), FString(TEXT("[ Empty element ]")));
    TestEqual(TEXT("Code is removed even with spaces between its tags"), Label(TEXT("c-code-only-el")), FString(TEXT("[ Empty element ]")));
    TestEqual(TEXT("Content shows entities as characters"), Label(TEXT("c-tea")), FString(TEXT("Tea & biscuits")));
    TestEqual(TEXT("A title shows entities as characters"), Label(TEXT("c-fish")), FString(TEXT("Fish & chips")));
    TestEqual(TEXT("Like play mode, content is cut before its tags are removed"), Label(TEXT("c-strong")),
        FString(TEXT("abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijab...")));
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

    TestTrue(TEXT("Several outputs are options"), Subsystem->HasOptions(Element(TEXT("plain-choices")), Board));
    TestFalse(TEXT("A single output without a label is not an option"), Subsystem->HasOptions(Element(TEXT("single")), Board));
    TestTrue(TEXT("A single labelled output is an option"), Subsystem->HasOptions(Element(TEXT("single-labelled")), Board));
    TestFalse(TEXT("An element without outputs has no options"), Subsystem->HasOptions(Element(TEXT("ending")), Board));

#if PLATFORM_WINDOWS || PLATFORM_MAC
    // c-loop leads to a branch that loops back to itself: once for its text, once for HasOptions on the healer
    AddExpectedMessagePlain(TEXT("leads to a loop of branches"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 2);
    // c-broken's label fails, and cond-bad fails for c-bad-branch's text
    AddExpectedMessagePlain(TEXT("ParseErrorException Unknown variable \"undefined_name\""), ELogVerbosity::Error, EAutomationExpectedMessageFlags::Contains, 2);
    AddExpectedMessagePlain(TEXT("Transpile failed for condition cond-bad"), ELogVerbosity::Error, EAutomationExpectedMessageFlags::Contains, 1);
    TestTrue(TEXT("An element with several outputs has options"), Subsystem->HasOptions(Element(TEXT("healer")), Board));
    TestTrue(TEXT("A labelled option whose branch leads nowhere is not shown"), Label(TEXT("c-dead")).IsEmpty());
    TestTrue(TEXT("An unlabelled option whose branch leads nowhere is not shown"), Label(TEXT("c-dead2")).IsEmpty());
    TestTrue(TEXT("An option whose label script fails is not shown"), Label(TEXT("c-broken")).IsEmpty());
    TestTrue(TEXT("An option whose branch condition fails is not shown, rather than taking else"), Label(TEXT("c-bad-branch")).IsEmpty());
    TestEqual(TEXT("Blank conditions are skipped"), Label(TEXT("c-blank")), FString(TEXT("Blank skipped")));
    TestEqual(TEXT("A branch without an if condition takes its else"), Label(TEXT("c-noif")), FString(TEXT("No if")));
    TestEqual(TEXT("A variable named empty can be a condition"), Label(TEXT("c-emptyvar")), FString(TEXT("Variable named empty")));
    TestTrue(TEXT("A satisfied arm without a connection is no option"), Label(TEXT("c-noout")).IsEmpty());
    Subsystem->SetVariable(TEXT("money-variable"), TEXT("5"));
    TestEqual(TEXT("A condition in a paragraph takes the if arm when it holds"), Label(TEXT("c-wrapped")), FString(TEXT("Pay")));
    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    TestEqual(TEXT("A condition in a paragraph takes the else arm when it doesn't"), Label(TEXT("c-wrapped")), FString(TEXT("Help")));
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

    TestTrue(TEXT("A loop of branches leads nowhere"), Label(TEXT("c-loop")).IsEmpty());

    TestFalse(TEXT("A single output that resets visits is not an option"), Subsystem->HasOptions(Element(TEXT("single-reset")), Board));
    TestEqual(TEXT("Checking for options does not reset visits"),
        Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 1);

    TestTrue(TEXT("A single unlabelled output leading through a branch to a label is an option"), Subsystem->HasOptions(Element(TEXT("reset-branch")), Board));
    TestEqual(TEXT("Branch conditions checked for options do not reset visits"),
        Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 1);
#else
    AddWarning(TEXT("Label script checks require Windows or macOS, the plugin's supported interpreter platforms."));
#endif

    return true;
}

#endif
