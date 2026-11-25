#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSettings.h"
#include "arcweave.h"
#include "HAL/PlatformMisc.h"
#include "Misc/AutomationTest.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"

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
        TEXT("[/script/ARCWEAVE.ArcweaveSettings] ; comment\r\n")
        TEXT("EnableReceiveMethodFromLocalJSON=False\r\n")
        TEXT("  apitoken = \"secret-token\"\r\n")
        TEXT("Hash=project-hash\r\n")
        TEXT("\r\n")
        TEXT("[/Script/UnrealEd.ProjectPackagingSettings] // comment\r\n")
        TEXT("+DirectoriesToAlwaysStageAsUFS=(Path=\"ArcweaveExport\")\r\n")
        TEXT("APIToken=another-plugin\r\n");

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
            TEXT("[/script/ARCWEAVE.ArcweaveSettings] ; comment\r\n")
            TEXT("EnableReceiveMethodFromLocalJSON=False\r\n")
            TEXT("Hash=project-hash\r\n")
            TEXT("\r\n")
            TEXT("[/Script/UnrealEd.ProjectPackagingSettings] // comment\r\n")
            TEXT("+DirectoriesToAlwaysStageAsUFS=(Path=\"ArcweaveExport\")\r\n")
            TEXT("APIToken=another-plugin\r\n")));

    // Array operators and an empty value at the end of the file without a line break
    const FString ArrayIni = FString::Printf(
        TEXT("[%s]\n!APIToken=ClearArray\n+APIToken=first\n.APIToken=second\nHash=h\nAPIToken="), *Section);
    Value.Reset();
    TestTrue(TEXT("Array assignments are found"), UArcweaveSettings::RemoveIniKey(ArrayIni, Section, TEXT("APIToken"), Result, &Value));
    TestEqual(TEXT("Every assignment is removed"), Result, FString::Printf(TEXT("[%s]\nHash=h\n"), *Section));
    TestEqual(TEXT("The value of the last plain assignment is returned"), Value, FString());

    // Added with ., escaped quotes, comments, and a clear with !
    const FString OperatorIni = FString::Printf(
        TEXT("[%s]\n; APIToken=commented\n.APIToken=\"a\\\"b\"\n"), *Section);
    Value.Reset();
    TestTrue(TEXT("A . assignment is found"), UArcweaveSettings::RemoveIniKey(OperatorIni, Section, TEXT("APIToken"), Result, &Value));
    TestEqual(TEXT("The quoted value is unescaped"), Value, FString(TEXT("a\"b")));
    TestEqual(TEXT("Comments are kept"), Result, FString::Printf(TEXT("[%s]\n; APIToken=commented\n"), *Section));

    const FString ClearedIni = FString::Printf(TEXT("[%s]\nAPIToken=old\n!APIToken=ClearArray\n"), *Section);
    Value.Reset();
    TestTrue(TEXT("A cleared key is found"), UArcweaveSettings::RemoveIniKey(ClearedIni, Section, TEXT("APIToken"), Result, &Value));
    TestTrue(TEXT("A cleared key has no value"), Value.IsEmpty());

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
    UArcweaveSettings* Settings = GetMutableDefault<UArcweaveSettings>();
    if (!TestNotNull(TEXT("Settings"), Settings))
    {
        return false;
    }

    // Tokens are compared with booleans, so a failing test never prints a real token
    const TCHAR* EnvironmentVariable = UArcweaveSettings::ApiTokenEnvironmentVariable;
    const FString PreviousEnvironment = FPlatformMisc::GetEnvironmentVariable(EnvironmentVariable);
    const FString PreviousUserToken = UArcweaveSettings::GetUserAPIToken();

    ON_SCOPE_EXIT
    {
        FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, *PreviousEnvironment);
        Settings->SetUserAPIToken(PreviousUserToken);
    };

    FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, TEXT("   "));
    TestTrue(TEXT("The user token is saved"), Settings->SetUserAPIToken(TEXT(" user-token ")));
    TestTrue(TEXT("The user token is read back trimmed"), UArcweaveSettings::GetUserAPIToken() == TEXT("user-token"));
    TestTrue(TEXT("The user token is used when the environment variable is blank"), UArcweaveSettings::ResolveAPIToken() == TEXT("user-token"));
    TestTrue(TEXT("The token file is under Saved"), UArcweaveSettings::GetUserAPITokenPath().StartsWith(FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir())));

    FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, TEXT(" env-token "));
    TestTrue(TEXT("The environment variable wins"), UArcweaveSettings::ResolveAPIToken() == TEXT("env-token"));

    TestTrue(TEXT("An empty token removes the file"), Settings->SetUserAPIToken(FString()));
    TestFalse(TEXT("The file is gone"), FPaths::FileExists(UArcweaveSettings::GetUserAPITokenPath()));
    TestTrue(TEXT("No user token is left"), UArcweaveSettings::GetUserAPIToken().IsEmpty());

    return true;
}

#endif
