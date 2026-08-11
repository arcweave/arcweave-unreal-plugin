#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSubsystem.h"

#include "Interfaces/IPluginManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveComponentBoardVariablesTest,
    "Arcweave.Project.ComponentAndBoardVariables",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveComponentBoardVariablesTest::RunTest(const FString& Parameters)
{
    const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("arcweave"));
    if (!TestTrue(TEXT("Arcweave plugin is available"), Plugin.IsValid()))
    {
        return false;
    }

    const FString FixturePath = FPaths::Combine(
        Plugin->GetBaseDir(),
        TEXT("Source/arcweave/test/componentBoardVariables.json"));
    FString Json;
    if (!TestTrue(TEXT("Component/board variable fixture loads"), FFileHelper::LoadFileToString(Json, *FixturePath)))
    {
        return false;
    }

    UArcweaveSubsystem* Subsystem = NewObject<UArcweaveSubsystem>();
    Subsystem->ParseResponse(Json);
    FArcweaveProjectData& Project = Subsystem->ProjectData;

    TestEqual(TEXT("Only eligible leaf values become variables"), Project.CurrentVars.Num(), 7);
    TestFalse(TEXT("Variable root is excluded"), Project.CurrentVars.Contains(TEXT("variables-root")));
    TestFalse(TEXT("Non-root variable folder is excluded"), Project.CurrentVars.Contains(TEXT("empty-folder")));
    TestFalse(TEXT("Rich text attribute is excluded"), Project.CurrentVars.Contains(TEXT("board-rich")));
    TestFalse(TEXT("Attribute without custom ID is excluded"), Project.CurrentVars.Contains(TEXT("board-ordinary")));

    TestEqual(TEXT("One board imports"), Project.Boards.Num(), 1);
    TestEqual(TEXT("One component imports"), Project.Components.Num(), 1);
    if (Project.Boards.Num() != 1 || Project.Components.Num() != 1)
    {
        return false;
    }

    TestEqual(TEXT("Board custom ID imports"), Project.Boards[0].CustomId, FString(TEXT("castle")));
    TestEqual(TEXT("Board attributes import"), Project.Boards[0].Attributes.Num(), 6);
    TestEqual(TEXT("Component custom ID imports"), Project.Components[0].CustomId, FString(TEXT("hero")));
    TestEqual(TEXT("Component attributes import"), Project.Components[0].Attributes.Num(), 2);

    const auto TestVariable = [this, &Project](
        const TCHAR* Id,
        const TCHAR* Name,
        const TCHAR* Value,
        const TCHAR* Scope)
    {
        const FArcweaveVariable* Variable = Project.CurrentVars.Find(Id);
        if (!TestNotNull(FString::Printf(TEXT("Variable %s imports"), Id), Variable))
        {
            return;
        }

        TestEqual(FString::Printf(TEXT("Variable %s name"), Id), Variable->Name, FString(Name));
        TestEqual(FString::Printf(TEXT("Variable %s current value"), Id), Variable->Value, FString(Value));
        TestEqual(FString::Printf(TEXT("Variable %s default value"), Id), Variable->DefaultValue, FString(Value));
        TestTrue(FString::Printf(TEXT("Variable %s has a default"), Id), Variable->bHasDefaultValue);
        TestEqual(FString::Printf(TEXT("Variable %s scope"), Id), Variable->Scope, FString(Scope));
    };

    TestVariable(TEXT("global-health"), TEXT("health"), TEXT("100"), TEXT(""));
    TestVariable(TEXT("board-health"), TEXT("health"), TEXT("10"), TEXT("castle"));
    TestVariable(TEXT("board-open"), TEXT("is_open"), TEXT("true"), TEXT("castle"));
    TestVariable(TEXT("board-rate"), TEXT("rate"), TEXT("1.5"), TEXT("castle"));
    TestVariable(TEXT("board-title"), TEXT("title"), TEXT(""), TEXT("castle"));
    TestVariable(TEXT("component-health"), TEXT("health"), TEXT("20"), TEXT("hero"));
    TestVariable(TEXT("component-label"), TEXT("label"), TEXT(""), TEXT("hero"));

#if PLATFORM_WINDOWS || PLATFORM_MAC
    Subsystem->RunTranspiler(
        TEXT("<pre><code>health = 101</code></pre>")
        TEXT("<pre><code>castle.health = 11</code></pre>")
        TEXT("<pre><code>hero.health = 21</code></pre>"),
        TEXT("element-1"),
        Project.CurrentVars,
        Project.Visits);

    TestEqual(TEXT("Global assignment uses the global ID"), Project.CurrentVars[TEXT("global-health")].Value, FString(TEXT("101")));
    TestEqual(TEXT("Board assignment uses the attribute ID"), Project.CurrentVars[TEXT("board-health")].Value, FString(TEXT("11")));
    TestEqual(TEXT("Component assignment uses the attribute ID"), Project.CurrentVars[TEXT("component-health")].Value, FString(TEXT("21")));

    Subsystem->RunTranspiler(
        TEXT("<pre><code>reset(castle.health)</code></pre>"),
        TEXT("element-1"),
        Project.CurrentVars,
        Project.Visits);
    TestEqual(TEXT("Reset restores the authored board default"), Project.CurrentVars[TEXT("board-health")].Value, FString(TEXT("10")));

    Subsystem->RunTranspiler(
        TEXT("<pre><code>resetAll(hero.health)</code></pre>"),
        TEXT("element-1"),
        Project.CurrentVars,
        Project.Visits);
    TestEqual(TEXT("ResetAll restores the authored global default"), Project.CurrentVars[TEXT("global-health")].Value, FString(TEXT("100")));
    TestEqual(TEXT("ResetAll keeps the excluded component current value"), Project.CurrentVars[TEXT("component-health")].Value, FString(TEXT("21")));
#else
    AddWarning(TEXT("Interpreter execution is only supported by this plugin on Windows and macOS."));
#endif

    return true;
}

#endif
