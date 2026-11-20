#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSettings.h"
#include "ArcweaveSubsystem.h"
#include "Misc/AutomationTest.h"

namespace
{
    // Restores the language settings (project defaults) that the test changes
    struct FScopedLanguageSettings
    {
        FScopedLanguageSettings()
        {
            UArcweaveSettings* Settings = GetMutableDefault<UArcweaveSettings>();
            bUseLocale = Settings->GetUseLocale();
            bFallback = Settings->GetFallbackToDefaultLocale();
            // GetLocale() returns "en" while the locale is not used, so read it with the setting enabled
            Settings->SetUseLocale(true);
            Locale = Settings->GetLocale();
            Settings->SetUseLocale(bUseLocale);
        }

        ~FScopedLanguageSettings()
        {
            Set(bUseLocale, Locale, bFallback);
        }

        static void Set(bool bInUseLocale, const FString& InLocale, bool bInFallback)
        {
            UArcweaveSettings* Settings = GetMutableDefault<UArcweaveSettings>();
            Settings->SetLocale(InLocale);
            Settings->SetUseLocale(bInUseLocale);
            Settings->SetFallbackToDefaultLocale(bInFallback);
        }

        bool bUseLocale = false;
        bool bFallback = true;
        FString Locale;
    };

    // Locales: en (default), fr and it (base en), dt and xx (base each other: a loop)
    const TCHAR* GLocalesFixture = TEXT(R"JSON({
        "name": "Locales test",
        "startingElement": "start",
        "locales": [
            {"iso": "en", "name": "English", "base": null},
            {"iso": "fr", "name": "French", "base": "en"},
            {"iso": "it", "name": "Italian", "base": "en"},
            {"iso": "dt", "name": "Loop A", "base": "xx"},
            {"iso": "xx", "name": "Loop B", "base": "dt"}
        ],
        "boards": {
            "board-1": {
                "name": "Main",
                "elements": ["start", "target", "partial", "nulltext"],
                "connections": ["c-plain", "c-code"],
                "jumpers": ["j1"]
            }
        },
        "jumpers": {"j1": {"elementId": "target"}},
        "elements": {
            "start": {"outputs": ["c-plain", "c-code"], "components": ["comp-1"]},
            "target": {"outputs": []},
            "partial": {"outputs": []},
            "nulltext": {"outputs": []}
        },
        "connections": {
            "c-plain": {"type": "Bezier", "sourceid": "start", "targetid": "target", "sourceType": "elements", "targetType": "elements"},
            "c-code": {"type": "Bezier", "sourceid": "start", "targetid": "target", "sourceType": "elements", "targetType": "elements"}
        },
        "components": {"comp-1": {"children": []}},
        "variables": {},
        "contents": {
            "start": {
                "title": {"en": {"text": "<p>Start</p>"}, "fr": {"text": "<p>Debut</p>"}, "it": {"text": "<p>Inizio</p>"}},
                "content": {"en": {"text": "<p>Hello</p>"}, "fr": {"text": "<p>Bonjour</p>"}, "it": {"text": "<p>Ciao</p>"}}
            },
            "target": {
                "title": {"en": {"text": "<p>Target</p>"}, "fr": {"text": "<p>Cible</p>"}, "it": {"text": "<p>Bersaglio</p>"}},
                "content": {"en": {"text": "<p>Target text</p>"}, "fr": {"text": "<p>Texte cible</p>"}, "it": {"text": "<p>Testo bersaglio</p>"}}
            },
            "partial": {
                "title": {"en": {"text": "Partial"}, "it": {"text": "Parziale"}},
                "content": {"it": {"text": "Solo italiano"}}
            },
            "nulltext": {
                "title": {"en": {"text": "Null en"}, "fr": {"text": null}}
            },
            "c-plain": {
                "label": {"en": {"text": "<p>Go</p>"}, "fr": {"text": "<p>Aller</p>"}, "it": {"text": "<p>Vai</p>"}}
            },
            "c-code": {
                "label": {
                    "en": {"text": "<pre><code>x = 1</code></pre><p>Run</p>"},
                    "fr": {"text": "<pre><code>x = 1</code></pre><p>Courir</p>"},
                    "it": {"text": "<pre><code>x = 1</code></pre><p>Corri</p>"}
                }
            },
            "comp-1": {
                "name": {"en": {"text": "Hero"}, "fr": {"text": "Heros"}, "it": {"text": "Eroe"}}
            }
        }
    })JSON");

    const FArcweaveElementData* FindElement(const TArray<FArcweaveElementData>& Elements, const TCHAR* Id)
    {
        return Elements.FindByPredicate([Id](const FArcweaveElementData& Element) { return Element.Id == Id; });
    }

    const FArcweaveConnectionsData* FindConnection(const TArray<FArcweaveConnectionsData>& Connections, const TCHAR* Id)
    {
        return Connections.FindByPredicate([Id](const FArcweaveConnectionsData& Connection) { return Connection.Id == Id; });
    }
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveLocalesTest,
    "Arcweave.Project.Locales",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveLocalesTest::RunTest(const FString& Parameters)
{
    const FString Json = GLocalesFixture;
    FScopedLanguageSettings SettingsGuard;
    UArcweaveSubsystem* Subsystem = NewObject<UArcweaveSubsystem>();

    // --- Import: the project locale comes from the settings, the default one when it is not used or unknown ---
    FScopedLanguageSettings::Set(false, TEXT("fr"), true);
    if (!TestTrue(TEXT("The multi-locale project imports"), Subsystem->ParseResponse(Json)))
    {
        return false;
    }
    TestTrue(TEXT("A project with several locales and contents has locales"), Subsystem->HasLocales());
    {
        const FArcweaveProjectData Project = Subsystem->GetArcweaveProjectData();
        const FArcweaveElementData* Start = Project.Boards.Num() == 1 ? FindElement(Project.Boards[0].Elements, TEXT("start")) : nullptr;
        if (!TestNotNull(TEXT("The start element imports"), Start))
        {
            return false;
        }
        TestEqual(TEXT("Without 'use locale' the default project locale is used"), Start->Title, FString(TEXT("Start")));
    }

    FScopedLanguageSettings::Set(true, TEXT("fr"), true);
    Subsystem->ParseResponse(Json);
    {
        const FArcweaveProjectData Project = Subsystem->GetArcweaveProjectData();
        const FArcweaveElementData* Start = FindElement(Project.Boards[0].Elements, TEXT("start"));
        TestEqual(TEXT("The locale of the settings is used on import, HTML stripped from the title"), Start->Title, FString(TEXT("Debut")));
        TestEqual(TEXT("The content is translated on import"), Start->Content, FString(TEXT("<p>Bonjour</p>")));
        TestEqual(TEXT("Labels are translated on import"), Start->Outputs[0].Label, FString(TEXT("Aller")));
        TestEqual(TEXT("Component names are translated on import"), Project.ComponentsMap.FindChecked(TEXT("comp-1")).Name, FString(TEXT("Heros")));
    }

    FScopedLanguageSettings::Set(true, TEXT("de"), true);
    Subsystem->ParseResponse(Json);
    TestEqual(TEXT("A locale that the project doesn't have falls back to the default project locale"),
        FindElement(Subsystem->GetArcweaveProjectData().Boards[0].Elements, TEXT("start"))->Title, FString(TEXT("Start")));

    // --- Switching language at runtime ---
    FScopedLanguageSettings::Set(true, TEXT("fr"), true);
    Subsystem->ParseResponse(Json);

    TestTrue(TEXT("Switching to an available locale succeeds"), Subsystem->UpdateContentsWithLocale(TEXT("it")));
    {
        const FArcweaveProjectData Project = Subsystem->GetArcweaveProjectData();
        const FArcweaveBoardData& Board = Project.Boards[0];

        const FArcweaveElementData* Start = FindElement(Board.Elements, TEXT("start"));
        TestEqual(TEXT("Element titles are switched and stripped of HTML"), Start->Title, FString(TEXT("Inizio")));
        TestEqual(TEXT("Element contents are switched"), Start->Content, FString(TEXT("<p>Ciao</p>")));
        TestEqual(TEXT("Element outputs are switched and stripped of HTML"), Start->Outputs[0].Label, FString(TEXT("Vai")));
        TestTrue(TEXT("Outputs with arcscript code keep it for the transpiler"), Start->Outputs[1].Label.StartsWith(TEXT("<pre")));
        TestTrue(TEXT("Outputs with arcscript code are switched"), Start->Outputs[1].Label.Contains(TEXT("Corri")));

        const FArcweaveConnectionsData* BoardConnection = FindConnection(Board.Connections, TEXT("c-plain"));
        if (TestNotNull(TEXT("The board connection exists"), BoardConnection))
        {
            TestEqual(TEXT("Board connections are switched"), BoardConnection->Label, FString(TEXT("Vai")));
        }
        const FArcweaveConnectionsData* ProjectConnection = FindConnection(Project.Connections, TEXT("c-plain"));
        if (TestNotNull(TEXT("The project connection exists"), ProjectConnection))
        {
            TestTrue(TEXT("Project connections are switched"), ProjectConnection->Label.Contains(TEXT("Vai")));
        }

        if (TestEqual(TEXT("The board has its jumper"), Board.Jumpers.Num(), 1))
        {
            TestEqual(TEXT("The element copy of a jumper is switched (title)"), Board.Jumpers[0].ElementData.Title, FString(TEXT("Bersaglio")));
            TestEqual(TEXT("The element copy of a jumper is switched (content)"), Board.Jumpers[0].ElementData.Content, FString(TEXT("<p>Testo bersaglio</p>")));
        }
        TestEqual(TEXT("Component names are switched"), Project.ComponentsMap.FindChecked(TEXT("comp-1")).Name, FString(TEXT("Eroe")));
    }

    UArcweaveSettings* Settings = GetMutableDefault<UArcweaveSettings>();
    TestTrue(TEXT("The settings keep using the locale"), Settings->GetUseLocale());
    TestEqual(TEXT("Changing the language at runtime doesn't change the settings"), Settings->GetLocale(), FString(TEXT("fr")));

    // --- An invalid locale changes nothing ---
    for (const TCHAR* Invalid : {TEXT("de"), TEXT(""), TEXT("pt-BR")})
    {
        TestFalse(FString::Printf(TEXT("Switching to the unknown locale '%s' fails"), Invalid), Subsystem->UpdateContentsWithLocale(Invalid));
    }
    TestEqual(TEXT("The texts are unchanged after an invalid locale"),
        FindElement(Subsystem->GetArcweaveProjectData().Boards[0].Elements, TEXT("start"))->Title, FString(TEXT("Inizio")));
    TestEqual(TEXT("The settings are unchanged after an invalid locale"), Settings->GetLocale(), FString(TEXT("fr")));

    // --- A new import starts again from the language of the settings ---
    Subsystem->ParseResponse(Json);
    TestEqual(TEXT("A new import doesn't keep the language chosen at runtime"),
        FindElement(Subsystem->GetArcweaveProjectData().Boards[0].Elements, TEXT("start"))->Title, FString(TEXT("Debut")));

    // --- A single locale project can't change language ---
    {
        UArcweaveSubsystem* Plain = NewObject<UArcweaveSubsystem>();
        const FString SingleLocale = TEXT(R"JSON({
            "name": "Single", "boards": {"b": {"name": "Main", "elements": ["e"]}},
            "elements": {"e": {"title": "Only", "content": "Text"}}, "components": {}, "variables": {}
        })JSON");
        Plain->ParseResponse(SingleLocale);
        TestFalse(TEXT("A project without locales has nothing to switch to"), Plain->HasLocales());
        TestFalse(TEXT("Switching language fails without locales"), Plain->UpdateContentsWithLocale(TEXT("fr")));
        TestEqual(TEXT("Its texts still come from the elements"), FindElement(Plain->GetArcweaveProjectData().Boards[0].Elements, TEXT("e"))->Title, FString(TEXT("Only")));
    }

    // --- Fallback: only the chain of base locales is walked (fr -> en) ---
    FScopedLanguageSettings::Set(true, TEXT("fr"), true);
    Subsystem->ParseResponse(Json);
    {
        const FArcweaveProjectData Project = Subsystem->GetArcweaveProjectData();
        const TArray<FArcweaveElementData>& Elements = Project.Boards[0].Elements;
        const FArcweaveElementData* Partial = FindElement(Elements, TEXT("partial"));
        TestEqual(TEXT("A missing translation falls back to the base locale"), Partial->Title, FString(TEXT("Partial")));
        TestEqual(TEXT("A translation that only exists in an unrelated locale is not used"), Partial->Content, FString());
        TestEqual(TEXT("A null text counts as missing and falls back to the base locale"),
            FindElement(Elements, TEXT("nulltext"))->Title, FString(TEXT("Null en")));
    }

    TestTrue(TEXT("The locale that has the translation can be selected"), Subsystem->UpdateContentsWithLocale(TEXT("it")));
    TestEqual(TEXT("The locale with the translation shows it"),
        FindElement(Subsystem->GetArcweaveProjectData().Boards[0].Elements, TEXT("partial"))->Content, FString(TEXT("Solo italiano")));

    FScopedLanguageSettings::Set(true, TEXT("fr"), false);
    Subsystem->ParseResponse(Json);
    TestEqual(TEXT("Without fallback a missing translation stays empty"),
        FindElement(Subsystem->GetArcweaveProjectData().Boards[0].Elements, TEXT("partial"))->Title, FString());

    // Loop of base locales (dt -> xx -> dt): it must end and the field stays empty
    FScopedLanguageSettings::Set(true, TEXT("fr"), true);
    Subsystem->ParseResponse(Json);
    TestTrue(TEXT("A locale with a loop of bases can be selected"), Subsystem->UpdateContentsWithLocale(TEXT("dt")));
    TestEqual(TEXT("A loop of base locales ends with an empty translation"),
        FindElement(Subsystem->GetArcweaveProjectData().Boards[0].Elements, TEXT("start"))->Title, FString());

    return true;
}

#endif
