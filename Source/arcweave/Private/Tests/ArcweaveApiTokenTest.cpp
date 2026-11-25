#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSettings.h"
#include "arcweave.h"
#include "HAL/PlatformMisc.h"
#include "Misc/AutomationTest.h"
#include "Misc/ConfigCacheIni.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveApiTokenIniTest,
    "Arcweave.Settings.ApiTokenIni",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveApiTokenIniTest::RunTest(const FString& Parameters)
{
    const FString Section = ARCWEAVE_SETTINGS_SECTION;
    const FString Ini =
        TEXT("[/Script/EngineSettings.GeneralProjectSettings]\r\n")
        TEXT("ProjectID=ABC\r\n")
        TEXT("APIToken=other-section\r\n")
        TEXT("\r\n")
        TEXT("[/script/ARCWEAVE.ArcweaveSettings]\r\n")
        TEXT("EnableReceiveMethodFromLocalJSON=False\r\n")
        TEXT("  apitoken = \"secret-token\"\r\n")
        TEXT("Hash=project-hash\r\n")
        TEXT("\r\n")
        TEXT("[/Script/UnrealEd.ProjectPackagingSettings]\r\n")
        TEXT("+DirectoriesToAlwaysStageAsUFS=(Path=\"ArcweaveExport\")\r\n");

    FString Result;
    FString Value;
    TestTrue(TEXT("The token is found"), UArcweaveSettings::RemoveIniKey(Ini, Section, TEXT("APIToken"), Result, &Value));
    TestEqual(TEXT("The value is unquoted"), Value, FString(TEXT("secret-token")));
    TestEqual(
        TEXT("Only the token line is removed, line endings are kept"),
        Result,
        FString(
            TEXT("[/Script/EngineSettings.GeneralProjectSettings]\r\n")
            TEXT("ProjectID=ABC\r\n")
            TEXT("APIToken=other-section\r\n")
            TEXT("\r\n")
            TEXT("[/script/ARCWEAVE.ArcweaveSettings]\r\n")
            TEXT("EnableReceiveMethodFromLocalJSON=False\r\n")
            TEXT("Hash=project-hash\r\n")
            TEXT("\r\n")
            TEXT("[/Script/UnrealEd.ProjectPackagingSettings]\r\n")
            TEXT("+DirectoriesToAlwaysStageAsUFS=(Path=\"ArcweaveExport\")\r\n")));

    // Array operators and an empty value at the end of the file without a line break
    const FString ArrayIni = FString::Printf(
        TEXT("[%s]\n!APIToken=ClearArray\n+APIToken=first\n.APIToken=second\nHash=h\nAPIToken="), *Section);
    Value.Reset();
    TestTrue(TEXT("Array assignments are found"), UArcweaveSettings::RemoveIniKey(ArrayIni, Section, TEXT("APIToken"), Result, &Value));
    TestEqual(TEXT("Every assignment is removed"), Result, FString::Printf(TEXT("[%s]\nHash=h\n"), *Section));
    TestEqual(TEXT("The value of the last plain assignment is returned"), Value, FString());

    // Nothing to remove
    const FString WithoutToken = FString::Printf(TEXT("[%s]\nHash=h\nAPITokenOld=x\n"), *Section);
    TestFalse(TEXT("A similar key is kept"), UArcweaveSettings::RemoveIniKey(WithoutToken, Section, TEXT("APIToken"), Result));
    TestEqual(TEXT("The text is unchanged"), Result, WithoutToken);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveApiTokenResolveTest,
    "Arcweave.Settings.ApiTokenResolve",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveApiTokenResolveTest::RunTest(const FString& Parameters)
{
    if (!TestNotNull(TEXT("Config"), GConfig))
    {
        return false;
    }

    const TCHAR* EnvironmentVariable = UArcweaveSettings::ApiTokenEnvironmentVariable;
    const FString PreviousEnvironment = FPlatformMisc::GetEnvironmentVariable(EnvironmentVariable);
    FString PreviousUserToken;
    const bool bHadUserToken = GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, TEXT("APIToken"), PreviousUserToken, GGameUserSettingsIni);

    // In memory only, so the test doesn't write the user's settings file
    GConfig->SetString(ARCWEAVE_SETTINGS_SECTION, TEXT("APIToken"), TEXT("user-token"), GGameUserSettingsIni);
    FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, TEXT(""));
    TestEqual(TEXT("The user token is used"), UArcweaveSettings::ResolveAPIToken(), FString(TEXT("user-token")));
    TestEqual(TEXT("The user token is read"), UArcweaveSettings::GetUserAPIToken(), FString(TEXT("user-token")));

    FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, TEXT(" env-token "));
    TestEqual(TEXT("The environment variable wins"), UArcweaveSettings::ResolveAPIToken(), FString(TEXT("env-token")));

    FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, *PreviousEnvironment);
    if (bHadUserToken)
    {
        GConfig->SetString(ARCWEAVE_SETTINGS_SECTION, TEXT("APIToken"), *PreviousUserToken, GGameUserSettingsIni);
    }
    else
    {
        GConfig->RemoveKey(ARCWEAVE_SETTINGS_SECTION, TEXT("APIToken"), GGameUserSettingsIni);
    }
    return true;
}

#endif
