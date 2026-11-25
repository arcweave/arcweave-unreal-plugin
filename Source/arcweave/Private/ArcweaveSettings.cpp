// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcweaveSettings.h"

#include "arcweave.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformMisc.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/CoreMisc.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Misc/Paths.h"
#include "Misc/Parse.h"

#if WITH_EDITOR
#include "UObject/UnrealType.h"
#endif

#if PLATFORM_MAC
#include <sys/stat.h>
#endif

namespace
{
const TCHAR* ApiTokenKey = TEXT("APIToken");

// Editor only: a token an older version saved in the project config, used when none is saved for the user
FString LegacyAPIToken;

// Set by PostEditChangeProperty, so the settings editor doesn't rewrite the project config for a token edit
bool bLastEditWasAPIToken = false;

// Tests point the user file elsewhere, so they never touch a real token
FString UserAPITokenPathOverride;

FString GetMigratedMarkerPath()
{
    return FPaths::Combine(FPaths::GetPath(UArcweaveSettings::GetUserAPITokenPath()), TEXT("APITokenMigrated"));
}

bool CanWriteUserFiles()
{
    return !FParse::Param(FCommandLine::Get(), TEXT("nowrite"));
}
}

const TCHAR* UArcweaveSettings::ApiTokenEnvironmentVariable = TEXT("ARCWEAVE_API_KEY");

UArcweaveSettings::UArcweaveSettings()
{
}

void UArcweaveSettings::PostInitProperties()
{
	UObject::PostInitProperties();
    if (HasAnyFlags(RF_ClassDefaultObject))
    {
        CheckProjectAPIToken();
        APIToken = GetUserAPIToken();
    }
}

#if WITH_EDITOR
void UArcweaveSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UObject::PostEditChangeProperty(PropertyChangedEvent);
    bLastEditWasAPIToken = PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UArcweaveSettings, APIToken);
    if (bLastEditWasAPIToken && !SetUserAPIToken(APIToken))
    {
        // Show what is actually saved
        APIToken = GetUserAPIToken();
    }
}

bool UArcweaveSettings::ConsumeAPITokenEdit()
{
    const bool bWasTokenEdit = bLastEditWasAPIToken;
    bLastEditWasAPIToken = false;
    return bWasTokenEdit;
}
#endif

FString UArcweaveSettings::GetLocale() const
{
    return Locale;
}

FString UArcweaveSettings::ResolveAPIToken()
{
    const FString EnvironmentToken = FPlatformMisc::GetEnvironmentVariable(ApiTokenEnvironmentVariable).TrimStartAndEnd();
    if (!EnvironmentToken.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Verbose, TEXT("Using the API token from %s"), ApiTokenEnvironmentVariable);
        return EnvironmentToken;
    }

    const FString Token = GetUserAPIToken();
    if (!Token.IsEmpty())
    {
        return Token;
    }

#if WITH_EDITOR
    // Only when the token in the project config couldn't be copied. Packaged games never use it
    if (!LegacyAPIToken.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: using the API token saved in the project config (Config/DefaultGame.ini) by an earlier version, because it couldn't be saved to %s."), *GetUserAPITokenPath());
        return LegacyAPIToken;
    }
#endif
    return FString();
}

FString UArcweaveSettings::GetUserAPITokenPath()
{
    if (!UserAPITokenPathOverride.IsEmpty())
    {
        return UserAPITokenPathOverride;
    }
    return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Arcweave"), TEXT("APIToken.txt")));
}

void UArcweaveSettings::SetUserAPITokenPathForTests(const FString& Path)
{
    UserAPITokenPathOverride = Path;
}

FString UArcweaveSettings::GetUserAPIToken()
{
    FString Token;
    const FString Path = GetUserAPITokenPath();
    if (FPaths::FileExists(Path))
    {
        FFileHelper::LoadFileToString(Token, *Path);
    }
    return Token.TrimStartAndEnd();
}

bool UArcweaveSettings::SetUserAPIToken(const FString& Token)
{
    const FString TrimmedToken = Token.TrimStartAndEnd();
    const FString Path = GetUserAPITokenPath();
    IFileManager& FileManager = IFileManager::Get();

    if (!CanWriteUserFiles())
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: the API token wasn't saved, because file writes are disabled (-nowrite)."));
        return false;
    }

    if (TrimmedToken.IsEmpty())
    {
        if (FPaths::FileExists(Path) && !FileManager.Delete(*Path, false, true, true))
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't remove the saved API token (%s)."), *Path);
            return false;
        }
        APIToken.Reset();
        return true;
    }

    // Write and check a copy first, so a failed write can't damage the saved token
    FileManager.MakeDirectory(*FPaths::GetPath(Path), true);
    const FString TempPath = FString::Printf(TEXT("%s.%s.tmp"), *Path, *FGuid::NewGuid().ToString(EGuidFormats::Digits));
    FString Written;
    bool bSaved = FFileHelper::SaveStringToFile(TrimmedToken, *TempPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM)
        && FFileHelper::LoadFileToString(Written, *TempPath) && Written.Equals(TrimmedToken, ESearchCase::CaseSensitive);
#if PLATFORM_MAC
    if (bSaved)
    {
        chmod(TCHAR_TO_UTF8(*TempPath), S_IRUSR | S_IWUSR);
    }
#endif
    if (bSaved && !FileManager.Move(*Path, *TempPath, true, true))
    {
        // Move can remove the old file before failing, so write the checked token directly
        bSaved = FFileHelper::SaveStringToFile(TrimmedToken, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
    }
    FileManager.Delete(*TempPath, false, true, true);
    bSaved = bSaved && GetUserAPIToken().Equals(TrimmedToken, ESearchCase::CaseSensitive);

    if (!bSaved)
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't save the API token to %s."), *Path);
        return false;
    }
    APIToken = TrimmedToken;
    return true;
}

bool UArcweaveSettings::FindIniValue(const FString& IniText, const FString& Section, const FString& Key, FString& OutValue, bool& bOutHasNonEmptyValue)
{
    OutValue.Reset();
    bOutHasNonEmptyValue = false;
    bool bFound = false;
    bool bInSection = false;
    TArray<FString> Lines;
    IniText.ParseIntoArrayLines(Lines, false);
    for (const FString& Line : Lines)
    {
        FString Trimmed = Line.TrimStartAndEnd();
        if (Trimmed.StartsWith(TEXT("[")))
        {
            // Unreal ignores a // comment after a section name
            int32 CommentIndex = Trimmed.Find(TEXT("//"));
            const FString Header = CommentIndex != INDEX_NONE ? Trimmed.Left(CommentIndex).TrimEnd() : Trimmed;
            if (Header.EndsWith(TEXT("]")))
            {
                bInSection = Header.Mid(1, Header.Len() - 2).Equals(Section, ESearchCase::IgnoreCase);
                continue;
            }
        }
        if (!bInSection || Trimmed.IsEmpty() || Trimmed[0] == TEXT(';'))
        {
            continue;
        }

        int32 EqualsIndex = INDEX_NONE;
        if (!Trimmed.FindChar(TEXT('='), EqualsIndex))
        {
            continue;
        }
        FString Name = Trimmed.Left(EqualsIndex).TrimStartAndEnd();
        Name.RemoveFromStart(TEXT("~"));
        TCHAR Command = TEXT('\0');
        if (!Name.IsEmpty() && FCString::Strchr(TEXT("+-.!@*^"), Name[0]) != nullptr)
        {
            Command = Name[0];
            Name.RightChopInline(1);
        }
        if (!Name.TrimStartAndEnd().Equals(Key, ESearchCase::IgnoreCase))
        {
            continue;
        }

        bFound = true;
        FString Value = Trimmed.RightChop(EqualsIndex + 1).TrimStartAndEnd();
        if (Value.StartsWith(TEXT("\"")))
        {
            FString Unquoted;
            const TCHAR* Cursor = *Value;
            if (FParse::QuotedString(Cursor, Unquoted))
            {
                Value = Unquoted;
            }
        }
        else
        {
            const int32 CommentIndex = Value.Find(TEXT("//"));
            if (CommentIndex != INDEX_NONE)
            {
                Value = Value.Left(CommentIndex).TrimEnd();
            }
        }

        // Any written value counts, even one a later line clears: the file would still contain it
        if (Command != TEXT('!') && Command != TEXT('-') && !Value.IsEmpty())
        {
            bOutHasNonEmptyValue = true;
        }
        if (Command == TEXT('!'))
        {
            OutValue.Reset();
        }
        else if (Command != TEXT('-'))
        {
            OutValue = Value;
        }
    }
    return bFound;
}

void UArcweaveSettings::CheckProjectAPIToken()
{
#if WITH_EDITOR
    LegacyAPIToken.Reset();
    const FString DefaultIni = FPaths::ConvertRelativePathToFull(GetDefaultConfigFilename());
    FString IniText;
    FString ProjectToken;
    bool bProjectHasToken = false;
    if (FPaths::FileExists(DefaultIni) && FFileHelper::LoadFileToString(IniText, *DefaultIni))
    {
        FindIniValue(IniText, ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, ProjectToken, bProjectHasToken);
    }

    // What earlier versions used: the project config with the user's saved settings (Saved/Config/<Platform>/Game.ini) on top
    FString LegacyToken;
    if (GConfig != nullptr)
    {
        GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, LegacyToken, GGameIni);
        LegacyToken.TrimStartAndEndInline();
    }

    const bool bInteractiveEditor = GIsEditor && !IsRunningCommandlet();
    if (bInteractiveEditor && !LegacyToken.IsEmpty() && GetUserAPIToken().IsEmpty() && !FPaths::FileExists(GetMigratedMarkerPath()))
    {
        // Copy it once, so clearing the token later doesn't bring it back
        if (SetUserAPIToken(LegacyToken))
        {
            FFileHelper::SaveStringToFile(FString(), *GetMigratedMarkerPath());
            UE_LOG(LogArcwarePlugin, Log, TEXT("Arcweave: copied the API token saved by an earlier version to %s"), *GetUserAPITokenPath());
        }
        else
        {
            LegacyAPIToken = LegacyToken;
        }
    }

    if (!bProjectHasToken)
    {
        return;
    }

    if (IsRunningCommandlet())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Arcweave: %s contains an API token in the [%s] section, so a packaged game would contain it. Remove the APIToken lines from that section; the token is saved per user now. If the file was committed, revoke the token in your Arcweave workspace."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION);
    }
    else
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token in the [%s] section. The token is saved per user now (%s), and that file is usually committed to version control and packaged with the game: remove the APIToken lines from that section, and if the file was committed, revoke the token in your Arcweave workspace and create a new one. Cooking fails while it is there."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION, *GetUserAPITokenPath());
    }
#endif
}
