#if WITH_DEV_AUTOMATION_TESTS

#include "ArcscriptTranspilerOutput.h"
#include "ArcweaveSubsystem.h"
#include "ArcweaveRuntimeStateTestTypes.h"
#include "GetIsTargetBranchOutput.h"
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
                "elements": ["healer", "help", "pay", "untitled", "long", "empty", "single", "single-labelled", "single-code", "single-branch", "single-reset", "reset-branch", "ending", "plain-choices", "leading-empty", "salt", "fish"],
                "jumpers": ["jumper-1", "jumper-orphan"],
                "branches": ["branch-1", "branch-none", "branch-a", "branch-b", "branch-loop", "branch-reset", "branch-show", "branch-visits", "branch-until-done", "branch-bad",
                    "branch-blank", "branch-ptag", "branch-emptyvar", "branch-chance", "branch-fail-later",
                    "branch-coin", "branch-multi", "branch-reset2", "branch-noout"],
                "connections": [
                    "c-empty", "c-labelled", "c-code-only", "c-untitled", "c-long", "c-empty-element", "c-jumper", "c-branch",
                    "c-branch-yes", "c-branch-no", "c-single", "c-single-labelled", "c-single-code", "c-dead", "c-dead-out", "c-alive",
                    "c-empty-html", "c-nested", "c-a-out", "c-b-yes", "c-b-no", "c-loop", "c-loop-back", "c-single-reset", "c-reset-branch", "c-reset-out",
                    "c-labelled-branch", "c-set-money",
                    "c-plain-1", "c-plain-2", "c-leading-empty", "c-set-show", "c-show-out", "c-reset-check", "c-visits-zero", "c-visits-other",
                    "c-broken", "c-bad-branch", "c-bad-out", "c-until-entry", "c-until-exit", "c-until-back",
                    "c-salt", "c-jumper-orphan", "c-blank", "c-blank-out", "c-blank-else", "c-ptag", "c-ptag-out", "c-ptag-else",
                    "c-emptyvar", "c-emptyvar-out", "c-set-chance", "c-chance-pos", "c-chance-zero", "c-spend", "c-spent", "c-lucky",
                    "c-coin", "c-coin-heads", "c-coin-again", "c-multi", "c-multi-out", "c-reset2", "c-reset2-out", "c-noout",
                    "c-plain-br", "c-fish"
                ]
            },
            "board-2": {
                "name": "Elsewhere",
                "elements": ["far"],
                "branches": ["branch-far"],
                "connections": ["c-far", "c-far-out"]
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
            "far": {"title": "<p>Far away</p>", "content": "", "outputs": ["c-far"]},
            "single": {"title": "Single", "content": "", "outputs": ["c-single"]},
            "single-labelled": {"title": "Single labelled", "content": "", "outputs": ["c-single-labelled"]},
            "single-code": {"title": "Single code", "content": "", "outputs": ["c-single-code"]},
            "single-branch": {"title": "Single branch", "content": "", "outputs": ["c-dead", "c-alive"]},
            "single-reset": {"title": "Single reset", "content": "", "outputs": ["c-single-reset"]},
            "reset-branch": {"title": "Reset branch", "content": "", "outputs": ["c-reset-branch"]},
            "ending": {"title": "Ending", "content": "", "outputs": []},
            "plain-choices": {"title": "Plain choices", "content": "", "outputs": ["c-plain-1", "c-plain-2"]},
            "leading-empty": {"title": "", "content": "<p></p><p>Text after an empty paragraph</p>", "outputs": []},
            "salt": {"title": "", "content": "<p>Salt &amp; pepper<br>and more</p>", "outputs": []},
            "orphan-el": {"title": "Orphan", "content": "<p>Not on any imported board</p>", "outputs": []},
            "fish": {"title": "<p>Fish &amp; chips</p>", "content": "", "outputs": []}
        },
        )JSON")
    TEXT(R"JSON("jumpers": {
            "jumper-1": {"elementId": "far"},
            "jumper-orphan": {"elementId": "orphan-el"}
        },
        "branches": {
            "branch-1": {"conditions": {"ifCondition": "cond-if", "elseIfConditions": [], "elseCondition": "cond-else"}},
            "branch-none": {"conditions": {"ifCondition": "cond-none", "elseIfConditions": []}},
            "branch-a": {"conditions": {"ifCondition": "cond-a", "elseIfConditions": []}},
            "branch-b": {"conditions": {"ifCondition": "cond-b", "elseIfConditions": [], "elseCondition": "cond-b-else"}},
            "branch-loop": {"conditions": {"ifCondition": "cond-loop", "elseIfConditions": []}},
            "branch-reset": {"conditions": {"ifCondition": "cond-reset", "elseIfConditions": []}},
            "branch-show": {"conditions": {"ifCondition": "cond-show", "elseIfConditions": []}},
            "branch-visits": {"conditions": {"ifCondition": "cond-visits-zero", "elseIfConditions": ["cond-blank"], "elseCondition": "cond-visits-other"}},
            "branch-until-done": {"conditions": {"ifCondition": "cond-done", "elseIfConditions": [], "elseCondition": "cond-not-done"}},
            "branch-bad": {"conditions": {"ifCondition": "cond-bad", "elseIfConditions": [], "elseCondition": "cond-bad-else"}},
            "branch-blank": {"conditions": {"ifCondition": "cond-blank-if", "elseIfConditions": ["cond-blank-br", "cond-blank-nbsp", "cond-blank-pm", "cond-blank-two"], "elseCondition": "cond-blank-else"}},
            "branch-coin": {"conditions": {"ifCondition": "cond-heads", "elseIfConditions": [], "elseCondition": "cond-tails"}},
            "branch-multi": {"conditions": {"ifCondition": "cond-multi", "elseIfConditions": []}},
            "branch-reset2": {"conditions": {"ifCondition": "cond-reset2", "elseIfConditions": []}},
            "branch-noout": {"conditions": {"ifCondition": "cond-noout", "elseIfConditions": []}},
            "branch-ptag": {"conditions": {"ifCondition": "cond-ptag", "elseIfConditions": [], "elseCondition": "cond-ptag-else"}},
            "branch-emptyvar": {"conditions": {"ifCondition": "cond-emptyvar", "elseIfConditions": []}},
            "branch-chance": {"conditions": {"ifCondition": "cond-chance", "elseIfConditions": [], "elseCondition": "cond-chance-else"}},
            "branch-fail-later": {"conditions": {"ifCondition": "cond-never", "elseIfConditions": []}},
            "branch-far": {"conditions": {"ifCondition": "cond-far", "elseIfConditions": []}}
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
            "cond-show": {"output": "c-show-out", "script": "true"},
            "cond-visits-zero": {"output": "c-visits-zero", "script": "visits() == 0"},
            "cond-blank": {"output": "c-visits-other", "script": ""},
            "cond-visits-other": {"output": "c-visits-other"},
            "cond-done": {"output": "c-until-exit", "script": "done"},
            "cond-not-done": {"output": "c-until-back"},
            "cond-bad": {"output": "c-bad-out", "script": "undefined_name > 1"},
            "cond-bad-else": {"output": "c-bad-out"},
            "cond-blank-if": {"output": "c-blank-out", "script": ""},
            "cond-blank-br": {"output": "c-blank-out", "script": "<p><br></p>"},
            "cond-blank-nbsp": {"output": "c-blank-out", "script": "<p>&nbsp;</p>"},
            "cond-blank-else": {"output": "c-blank-else"},
            "cond-blank-pm": {"output": "c-blank-out", "script": "<p><br class=\"ProseMirror-trailingBreak\"></p>"},
            "cond-blank-two": {"output": "c-blank-out", "script": "<p></p><p></p>"},
            "cond-heads": {"output": "c-coin-heads", "script": "roll(2) == 1"},
            "cond-tails": {"output": "c-coin-again"},
            "cond-multi": {"output": "c-multi-out", "script": "<p>true</p><p></p>"},
            "cond-reset2": {"output": "c-reset2-out", "script": "resetVisits() or true"},
            "cond-noout": {"output": "", "script": "true"},
            "cond-ptag": {"output": "c-ptag-out", "script": "<p>money == 0</p>"},
            "cond-ptag-else": {"output": "c-ptag-else"},
            "cond-emptyvar": {"output": "c-emptyvar-out", "script": "empty"},
            "cond-chance": {"output": "c-chance-pos", "script": "chance > 0"},
            "cond-chance-else": {"output": "c-chance-zero"},
            "cond-never": {"output": "c-spent", "script": "false"},
            "cond-far": {"output": "c-far-out", "script": "true"}
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
            "c-reset-out": {"label": null, "sourceid": "branch-reset", "targetid": "help", "sourceType": "branches", "targetType": "elements"},
            "c-labelled-branch": {"label": "<p>Decide</p>", "sourceid": "healer", "targetid": "branch-1", "sourceType": "elements", "targetType": "branches"},
            "c-set-money": {"label": "<pre><code>money = 9</code></pre>", "sourceid": "healer", "targetid": "branch-1", "sourceType": "elements", "targetType": "branches"},
            "c-plain-1": {"label": null, "sourceid": "plain-choices", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-plain-2": {"label": null, "sourceid": "plain-choices", "targetid": "pay", "sourceType": "elements", "targetType": "elements"},
            "c-leading-empty": {"label": null, "sourceid": "healer", "targetid": "leading-empty", "sourceType": "elements", "targetType": "elements"},
            "c-set-show": {"label": "<pre><code>money = 9</code></pre>", "sourceid": "healer", "targetid": "branch-show", "sourceType": "elements", "targetType": "branches"},
            "c-show-out": {"label": "<pre><code>if money == 9</code></pre><p>Nine</p><pre><code>else</code></pre><p>Other</p><pre><code>endif</code></pre>", "sourceid": "cond-show", "targetid": "pay", "sourceType": "conditions", "targetType": "elements"},
            "c-reset-check": {"label": "<pre><code>resetVisits()</code></pre>", "sourceid": "healer", "targetid": "branch-visits", "sourceType": "elements", "targetType": "branches"},
            "c-visits-zero": {"label": "<p>Reset worked</p>", "sourceid": "cond-visits-zero", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-visits-other": {"label": "<p>Not reset</p>", "sourceid": "cond-visits-other", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-broken": {"label": "<pre><code>undefined_name = 1</code></pre><p>Broken</p>", "sourceid": "healer", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-bad-branch": {"label": null, "sourceid": "healer", "targetid": "branch-bad", "sourceType": "elements", "targetType": "branches"},
            "c-bad-out": {"label": "<p>Should not show</p>", "sourceid": "cond-bad", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-until-entry": {"label": null, "sourceid": "healer", "targetid": "branch-until-done", "sourceType": "elements", "targetType": "branches"},
            "c-until-exit": {"label": null, "sourceid": "cond-done", "targetid": "pay", "sourceType": "conditions", "targetType": "elements"},
            "c-until-back": {"label": "<pre><code>done = true</code></pre>", "sourceid": "cond-not-done", "targetid": "branch-until-done", "sourceType": "conditions", "targetType": "branches"},)JSON")
    // Split again for the MSVC limit
    TEXT(R"JSON(
            "c-salt": {"label": null, "sourceid": "healer", "targetid": "salt", "sourceType": "elements", "targetType": "elements"},
            "c-jumper-orphan": {"label": null, "sourceid": "healer", "targetid": "jumper-orphan", "sourceType": "elements", "targetType": "jumpers"},
            "c-blank": {"label": null, "sourceid": "healer", "targetid": "branch-blank", "sourceType": "elements", "targetType": "branches"},
            "c-blank-out": {"label": "<p>Blank taken</p>", "sourceid": "cond-blank-if", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-blank-else": {"label": "<p>Blank skipped</p>", "sourceid": "cond-blank-else", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-ptag": {"label": null, "sourceid": "healer", "targetid": "branch-ptag", "sourceType": "elements", "targetType": "branches"},
            "c-ptag-out": {"label": "<p>Paragraph condition</p>", "sourceid": "cond-ptag", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-ptag-else": {"label": "<p>Paragraph not run</p>", "sourceid": "cond-ptag-else", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-emptyvar": {"label": null, "sourceid": "healer", "targetid": "branch-emptyvar", "sourceType": "elements", "targetType": "branches"},
            "c-emptyvar-out": {"label": "<p>Variable named empty</p>", "sourceid": "cond-emptyvar", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-set-chance": {"label": "<pre><code>chance = 0.0000001</code></pre>", "sourceid": "healer", "targetid": "branch-chance", "sourceType": "elements", "targetType": "branches"},
            "c-chance-pos": {"label": "<p>Positive</p>", "sourceid": "cond-chance", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-chance-zero": {"label": "<p>Zero</p>", "sourceid": "cond-chance-else", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-spend": {"label": "<pre><code>money = money - 10</code></pre><pre><code>resetVisits()</code></pre>", "sourceid": "healer", "targetid": "branch-fail-later", "sourceType": "elements", "targetType": "branches"},
            "c-spent": {"label": null, "sourceid": "cond-never", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-lucky": {"label": "<pre><code>lucky = roll(2) == 1</code></pre><pre><code>if lucky</code></pre><p>Lucky</p><pre><code>else</code></pre><p>Unlucky</p><pre><code>endif</code></pre>", "sourceid": "healer", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-far": {"label": null, "sourceid": "far", "targetid": "branch-far", "sourceType": "elements", "targetType": "branches"},
            "c-far-out": {"label": null, "sourceid": "cond-far", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-coin": {"label": null, "sourceid": "healer", "targetid": "branch-coin", "sourceType": "elements", "targetType": "branches"},
            "c-coin-heads": {"label": null, "sourceid": "cond-heads", "targetid": "pay", "sourceType": "conditions", "targetType": "elements"},
            "c-coin-again": {"label": null, "sourceid": "cond-tails", "targetid": "branch-coin", "sourceType": "conditions", "targetType": "branches"},
            "c-multi": {"label": null, "sourceid": "healer", "targetid": "branch-multi", "sourceType": "elements", "targetType": "branches"},
            "c-multi-out": {"label": "<p>First paragraph</p>", "sourceid": "cond-multi", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-reset2": {"label": null, "sourceid": "healer", "targetid": "branch-reset2", "sourceType": "elements", "targetType": "branches"},
            "c-reset2-out": {"label": "<pre><code>if visits() == 0</code></pre><p>Zero</p><pre><code>else</code></pre><p>Some</p><pre><code>endif</code></pre>", "sourceid": "cond-reset2", "targetid": "help", "sourceType": "conditions", "targetType": "elements"},
            "c-noout": {"label": "<p>No output</p>", "sourceid": "healer", "targetid": "branch-noout", "sourceType": "elements", "targetType": "branches"},
            "c-plain-br": {"label": "<p>Salt &amp; pepper<br>and more</p>", "sourceid": "healer", "targetid": "help", "sourceType": "elements", "targetType": "elements"},
            "c-fish": {"label": null, "sourceid": "healer", "targetid": "fish", "sourceType": "elements", "targetType": "elements"}
        },
        "components": {},
        "variables": {
            "money-variable": {"name": "money", "type": "integer", "value": 0, "cType": "global"},
            "done-variable": {"name": "done", "type": "boolean", "value": false, "cType": "global"},
            "empty-variable": {"name": "empty", "type": "boolean", "value": true, "cType": "global"},
            "chance-variable": {"name": "chance", "type": "float", "value": 0.0, "cType": "global"},
            "lucky-variable": {"name": "lucky", "type": "boolean", "value": false, "cType": "global"}
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
    TestEqual(TEXT("The text shows entities as characters and line breaks as spaces"), Label(TEXT("c-salt")), FString(TEXT("Salt & pepper and more")));
    TestTrue(TEXT("A jumper to an element on no imported board is not an option"), Label(TEXT("c-jumper-orphan")).IsEmpty());
    TestEqual(TEXT("A plain label shows entities as characters and line breaks as spaces"), Label(TEXT("c-plain-br")), FString(TEXT("Salt & pepper and more")));
    TestEqual(TEXT("A title shows entities as characters"), Label(TEXT("c-fish")), FString(TEXT("Fish & chips")));
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
    // Exact counts, so that no other failure goes unnoticed. c-loop loops back to its branch; it's resolved for its text
    // and again for HasOptions on the healer once the variables have changed
    AddExpectedMessagePlain(TEXT("leads to a loop of branches"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 2);
    // c-broken's label fails once; cond-bad fails for c-bad-branch's text and for GetIsTargetBranch
    AddExpectedMessagePlain(TEXT("ParseErrorException Unknown variable \"undefined_name\""), ELogVerbosity::Error, EAutomationExpectedMessageFlags::Contains, 3);
    AddExpectedMessagePlain(TEXT("Transpile failed for condition cond-bad"), ELogVerbosity::Error, EAutomationExpectedMessageFlags::Contains, 2);
    AddExpectedMessagePlain(TEXT("failed to run: no option for connection c-broken"), ELogVerbosity::Warning, EAutomationExpectedMessageFlags::Contains, 1);

    UArcweaveRuntimeStateTestListener* Listener = NewObject<UArcweaveRuntimeStateTestListener>();
    Listener->Subsystem = Subsystem;
    Subsystem->OnArcweaveVariableChanged.AddDynamic(Listener, &UArcweaveRuntimeStateTestListener::HandleVariablesChanged);
    Subsystem->OnArcscriptEventReceived.AddDynamic(Listener, &UArcweaveRuntimeStateTestListener::HandleArcscriptEvent);

    TestTrue(TEXT("An element with several labelled outputs has options"), Subsystem->HasOptions(Element(TEXT("healer")), Board));
    TestEqual(TEXT("A label with only code shows the target's title"), Label(TEXT("c-code-only")), FString(TEXT("Pay")));

    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    TestEqual(TEXT("A branch shows the element it leads to"), Label(TEXT("c-branch")), FString(TEXT("Help")));
    Subsystem->SetVariable(TEXT("money-variable"), TEXT("5"));
    TestEqual(TEXT("A branch shows the label after it"), Label(TEXT("c-branch")), FString(TEXT("Pay up")));

    TestEqual(TEXT("A label before a branch is replaced by the label after it"), Label(TEXT("c-labelled-branch")), FString(TEXT("Pay up")));
    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    TestEqual(TEXT("A label before a branch is kept when the path has no later label"), Label(TEXT("c-labelled-branch")), FString(TEXT("Decide")));
    TestTrue(TEXT("A labelled connection whose branch leads nowhere has no text"), Label(TEXT("c-dead")).IsEmpty());
    TestEqual(TEXT("A label's changes reach the branch conditions after it"), Label(TEXT("c-set-money")), FString(TEXT("Pay up")));
    TestEqual(TEXT("A label's changes on the path don't change the project"), Money(), FString(TEXT("0")));
    TestEqual(TEXT("A label's changes reach the labels after it"), Label(TEXT("c-set-show")), FString(TEXT("Nine")));
    TestEqual(TEXT("Showing the later label doesn't change the project"), Money(), FString(TEXT("0")));
    TestTrue(TEXT("An option whose label script fails is not shown"), Label(TEXT("c-broken")).IsEmpty());
    TestTrue(TEXT("An option whose branch condition fails is not shown"), Label(TEXT("c-bad-branch")).IsEmpty());
    TestEqual(TEXT("A branch reached again in another state is not a loop"), Label(TEXT("c-until-entry")), FString(TEXT("Pay")));
    TestEqual(TEXT("The loop's label changes don't change the project"),
        Subsystem->GetArcweaveProjectData().CurrentVars.FindChecked(TEXT("done-variable")).Value, FString(TEXT("false")));
    TestEqual(TEXT("A condition runs its first paragraph"), Label(TEXT("c-multi")), FString(TEXT("First paragraph")));
    TestTrue(TEXT("A satisfied arm without a connection is no option"), Label(TEXT("c-noout")).IsEmpty());
    for (int32 Attempt = 0; Attempt < 10; ++Attempt)
    {
        Subsystem->SetVariable(TEXT("lucky-variable"), TEXT("false"));
        TestEqual(TEXT("A branch that loops back until a random condition holds still leads somewhere"), Label(TEXT("c-coin")), FString(TEXT("Pay")));
    }

    // SetVariable broadcasts too: count from here
    Listener->VariableEvents = 0;
    Listener->ArcscriptEvents = 0;
    TestEqual(TEXT("Blank conditions are skipped, including empty paragraphs"), Label(TEXT("c-blank")), FString(TEXT("Blank skipped")));
    TestEqual(TEXT("A condition in a paragraph runs without it"), Label(TEXT("c-ptag")), FString(TEXT("Paragraph condition")));
    TestEqual(TEXT("A variable named empty can be a condition"), Label(TEXT("c-emptyvar")), FString(TEXT("Variable named empty")));
    TestEqual(TEXT("A small float set by a label keeps its value for the conditions after it"), Label(TEXT("c-set-chance")), FString(TEXT("Positive")));
    const FGetIsTargetBranchOutput BadBranch = Subsystem->GetIsTargetBranch(Board, Subsystem->GetConnectionsData(Board, TEXT("c-bad-branch")));
    TestTrue(TEXT("A connection to a failing branch still leads to a branch"), BadBranch.IsBranch);
    TestEqual(TEXT("A failing condition stops the branch without falling through to else"), BadBranch.BranchConnections.Num(), 0);
    TestEqual(TEXT("A branch on another board is found through the whole project"),
        Subsystem->TranspileConnectionLabel(Subsystem->GetConnectionsData(*Project.Boards.FindByPredicate(
            [](const FArcweaveBoardData& Data) { return Data.BoardId == TEXT("board-2"); }), TEXT("c-far")), Board), FString(TEXT("Help")));
    TestEqual(TEXT("Previews don't broadcast variable changes"), Listener->VariableEvents, 0);
    TestEqual(TEXT("Previews don't broadcast events"), Listener->ArcscriptEvents, 0);

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

    Subsystem->HasOptions(Element(TEXT("reset-branch")), Board);
    TestEqual(TEXT("Branch conditions checked for options do not reset visits"),
        Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 1);

    TestEqual(TEXT("A label's resetVisits() reaches the conditions after it, and a blank condition is skipped"),
        Label(TEXT("c-reset-check")), FString(TEXT("Reset worked")));
    TestEqual(TEXT("Showing it doesn't reset the project's visits"),
        Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 1);
    TestEqual(TEXT("A condition's resetVisits() reaches the labels after it"), Label(TEXT("c-reset2")), FString(TEXT("Zero")));
    TestEqual(TEXT("Showing it doesn't reset the project's visits either"),
        Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 1);
    TestEqual(TEXT("Previews with resetVisits() don't broadcast events"), Listener->ArcscriptEvents, 0);

    // Selecting an option follows the same path as its text, now applying the labels
    const auto Select = [Subsystem, &Board](const TCHAR* ConnectionId, FString& OutTargetId)
    {
        FArcweaveElementData Target;
        const bool bSelected = Subsystem->SelectOption(Subsystem->GetConnectionsData(Board, ConnectionId), Board, Target);
        OutTargetId = Target.Id;
        return bSelected;
    };
    FString TargetId;
    TestTrue(TEXT("Chained branches can be selected"), Select(TEXT("c-nested"), TargetId));
    TestEqual(TEXT("Selection reaches the element the option shows, with the same visits() origin"), TargetId, FString(TEXT("pay")));
    TestTrue(TEXT("A jumper can be selected"), Select(TEXT("c-jumper"), TargetId));
    TestEqual(TEXT("Selecting a jumper leads to its element"), TargetId, FString(TEXT("far")));
    TestFalse(TEXT("An option whose branch leads nowhere can't be selected"), Select(TEXT("c-dead"), TargetId));

    Subsystem->SetVariable(TEXT("money-variable"), TEXT("0"));
    Listener->VariableEvents = 0;
    TestTrue(TEXT("An option that sets a variable before a branch can be selected"), Select(TEXT("c-set-money"), TargetId));
    TestEqual(TEXT("The label's change decides the branch on selection too"), TargetId, FString(TEXT("pay")));
    TestEqual(TEXT("Selection applies the label's change to the project"), Money(), FString(TEXT("9")));

    TestEqual(TEXT("A selection broadcasts the variables it changes"), Listener->VariableEvents, 1);

    Subsystem->IncrementVisits(TEXT("healer"));
    Listener->ArcscriptEvents = 0;
    FString CaptureError;
    TestTrue(TEXT("The state before the selection can be captured"), Subsystem->CaptureState(Listener->StateToRestore, CaptureError));
    Listener->bProbeDuringScript = true;
    TestTrue(TEXT("An option that resets visits before a branch can be selected"), Select(TEXT("c-reset-check"), TargetId));
    Listener->bProbeDuringScript = false;
    TestFalse(TEXT("A listener can't restore a checkpoint while the selection is reported"), Listener->bRestoreDuringScriptSucceeded);
    TestEqual(TEXT("Selection applies resetVisits() to the project"),
        Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 0);
    TestEqual(TEXT("A selection broadcasts its label's events"), Listener->ArcscriptEvents, 1);

    // A path that fails after its labels changed things changes nothing
    Subsystem->IncrementVisits(TEXT("healer"));
    const FString MoneyBefore = Money();
    Listener->VariableEvents = 0;
    Listener->ArcscriptEvents = 0;
    TestFalse(TEXT("An option whose branch fails after its label can't be selected"), Select(TEXT("c-spend"), TargetId));
    TestEqual(TEXT("A failed selection keeps the variables"), Money(), MoneyBefore);
    TestEqual(TEXT("A failed selection keeps the visits"), Subsystem->GetArcweaveProjectData().Visits.FindChecked(TEXT("healer")), 1);
    TestEqual(TEXT("A failed selection broadcasts no variable change"), Listener->VariableEvents, 0);
    TestEqual(TEXT("A failed selection broadcasts no event"), Listener->ArcscriptEvents, 0);

    // The selection applies the option as it was shown, without running its scripts again
    // shown through the board's connection, selected through the project's copy of it
    const FArcweaveConnectionsData* ProjectLucky = Project.Connections.FindByPredicate(
        [](const FArcweaveConnectionsData& Connection) { return Connection.Id == TEXT("c-lucky"); });
    if (TestNotNull(TEXT("The project-level copy of the random connection imports"), ProjectLucky))
    {
        int32 Mismatches = 0;
        int32 Invalid = 0;
        for (int32 Attempt = 0; Attempt < 20; ++Attempt)
        {
            Subsystem->SetVariable(TEXT("lucky-variable"), TEXT("false"));
            const FString Shown = Label(TEXT("c-lucky"));
            FArcweaveElementData Target;
            const bool bSelected = Subsystem->SelectOption(*ProjectLucky, Board, Target);
            const FString Lucky = Subsystem->GetArcweaveProjectData().CurrentVars.FindChecked(TEXT("lucky-variable")).Value;
            Invalid += (Shown != TEXT("Lucky") && Shown != TEXT("Unlucky")) || !bSelected || Target.Id != TEXT("help") ? 1 : 0;
            Mismatches += (Shown == TEXT("Lucky")) != (Lucky == TEXT("true")) ? 1 : 0;
        }
        TestEqual(TEXT("The random option is shown and selected every time"), Invalid, 0);
        TestEqual(TEXT("A random label grants what it showed, whichever copy of the connection is used"), Mismatches, 0);
    }

    // A runner can pass an output of the element it overwrites
    FArcweaveElementData Current = Element(TEXT("plain-choices"));
    TestTrue(TEXT("An element's own output can be selected into it"), Subsystem->SelectOption(Current.Outputs[0], Board, Current));
    TestEqual(TEXT("Selecting into the element replaces it with the target"), Current.Id, FString(TEXT("help")));
#else
    AddWarning(TEXT("Label script checks require Windows or macOS, the plugin's supported interpreter platforms."));
#endif

    return true;
}

#endif
