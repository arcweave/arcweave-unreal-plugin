#if WITH_DEV_AUTOMATION_TESTS

#include "ArcweaveSettings.h"
#include "arcweave.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformMisc.h"
#include "Misc/AutomationTest.h"
#include "Misc/Guid.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
    FArcweaveApiTokenIniTest,
    "Arcweave.Settings.ApiTokenIni",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FArcweaveApiTokenIniTest::RunTest(const FString& Parameters)
{
    const FString Section = ARCWEAVE_SETTINGS_SECTION;
    FString Value;
    bool bHasValue = false;

    const FString Ini =
        TEXT("[/Script/EngineSettings.GeneralProjectSettings]\r\n")
        TEXT("APIToken=other-section\r\n")
        TEXT("[/script/ARCWEAVE.ArcweaveSettings] // comment\r\n")
        TEXT("; APIToken=commented\r\n")
        TEXT("  apitoken = \"a\\\"b\"\r\n")
        TEXT("Hash=project-hash\r\n")
        TEXT("[/Script/UnrealEd.ProjectPackagingSettings]\r\n")
        TEXT("APIToken=another-plugin\r\n");
    TestTrue(TEXT("The token is found"), UArcweaveSettings::FindIniValue(Ini, Section, TEXT("APIToken"), Value, bHasValue));
    TestEqual(TEXT("The value is unquoted and unescaped"), Value, FString(TEXT("a\"b")));
    TestTrue(TEXT("It has a value"), bHasValue);

    // A cleared value still counts as written, since the file contains it
    const FString Cleared = FString::Printf(TEXT("[%s]\nAPIToken=old\n!APIToken=ClearArray\n.APIToken=\nHash=h"), *Section);
    TestTrue(TEXT("A cleared token is found"), UArcweaveSettings::FindIniValue(Cleared, Section, TEXT("APIToken"), Value, bHasValue));
    TestTrue(TEXT("Its value is empty"), Value.IsEmpty());
    TestTrue(TEXT("The file still contains a token"), bHasValue);

    const FString Commented = FString::Printf(TEXT("[%s]\n+APIToken=key // note\n"), *Section);
    TestTrue(TEXT("A + assignment is found"), UArcweaveSettings::FindIniValue(Commented, Section, TEXT("APIToken"), Value, bHasValue));
    TestEqual(TEXT("A // comment is not part of the value"), Value, FString(TEXT("key")));

    const FString Empty = FString::Printf(TEXT("[%s]\nAPIToken=\nAPITokenOld=x\n"), *Section);
    TestTrue(TEXT("An empty token is found"), UArcweaveSettings::FindIniValue(Empty, Section, TEXT("APIToken"), Value, bHasValue));
    TestFalse(TEXT("An empty token has no value"), bHasValue);

    // A header with a ; comment isn't a section header for Unreal, so the previous section continues
    const FString NotHeader = TEXT("[Other]\n[/Script/arcweave.ArcweaveSettings] ; comment\nAPIToken=x\n");
    TestFalse(TEXT("A ; comment makes the line no header"), UArcweaveSettings::FindIniValue(NotHeader, Section, TEXT("APIToken"), Value, bHasValue));
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

    // A temporary token file and environment value; tokens are compared with booleans, so a failure never prints one
    const TCHAR* EnvironmentVariable = UArcweaveSettings::ApiTokenEnvironmentVariable;
    const FString PreviousEnvironment = FPlatformMisc::GetEnvironmentVariable(EnvironmentVariable);
    const FString PreviousShownToken = Settings->APIToken;
    const FString TestDirectory = FPaths::Combine(FPaths::AutomationTransientDir(), TEXT("ArcweaveToken"), FGuid::NewGuid().ToString());
    UArcweaveSettings::SetUserAPITokenPathForTests(FPaths::Combine(TestDirectory, TEXT("APIToken.txt")));
    ON_SCOPE_EXIT
    {
        UArcweaveSettings::SetUserAPITokenPathForTests(FString());
        FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, *PreviousEnvironment);
        Settings->APIToken = PreviousShownToken;
        IFileManager::Get().DeleteDirectory(*TestDirectory, false, true);
    };

    FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, TEXT("   "));
    TestTrue(TEXT("No token is saved yet"), UArcweaveSettings::GetUserAPIToken().IsEmpty());
    TestTrue(TEXT("The user token is saved"), Settings->SetUserAPIToken(TEXT(" User-Token ")));
    TestTrue(TEXT("The user token is read back trimmed, with its case"), UArcweaveSettings::GetUserAPIToken().Equals(TEXT("User-Token"), ESearchCase::CaseSensitive));
    TestTrue(TEXT("The user token is used when the environment variable is blank"), UArcweaveSettings::ResolveAPIToken().Equals(TEXT("User-Token"), ESearchCase::CaseSensitive));
    TestTrue(TEXT("A new token replaces it"), Settings->SetUserAPIToken(TEXT("user-token")));
    TestTrue(TEXT("Only the new token is saved"), UArcweaveSettings::GetUserAPIToken().Equals(TEXT("user-token"), ESearchCase::CaseSensitive));

    TArray<FString> Files;
    IFileManager::Get().FindFiles(Files, *FPaths::Combine(TestDirectory, TEXT("*")), true, false);
    TestEqual(TEXT("No temporary files are left"), Files.Num(), 1);

    FPlatformMisc::SetEnvironmentVar(EnvironmentVariable, TEXT(" env-token "));
    TestTrue(TEXT("The environment variable wins"), UArcweaveSettings::ResolveAPIToken().Equals(TEXT("env-token"), ESearchCase::CaseSensitive));

    TestTrue(TEXT("An empty token removes the file"), Settings->SetUserAPIToken(FString()));
    TestFalse(TEXT("The file is gone"), FPaths::FileExists(UArcweaveSettings::GetUserAPITokenPath()));
    TestTrue(TEXT("No user token is left"), UArcweaveSettings::GetUserAPIToken().IsEmpty());
    return true;
}

#endif
