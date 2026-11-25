// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcweaveSettings.h"

#include "arcweave.h"
#include "ArcweaveUserSettings.h"
#include "HAL/PlatformProperties.h"
#include "Misc/App.h"
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

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#else
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace
{
const TCHAR* ApiTokenKey = TEXT("APIToken");

// Editor only: a token an older version saved in the project config, used when none is saved for the user
FString LegacyAPIToken;

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

bool WriteMigratedMarker()
{
    return FFileHelper::SaveStringToFile(FString(), *GetMigratedMarkerPath());
}

// Create an empty file only the current user can read, so the token is never readable by others, even briefly
bool CreatePrivateFile(const FString& Path)
{
#if PLATFORM_WINDOWS
    return FFileHelper::SaveStringToFile(FString(), *Path);
#else
    const int Handle = open(TCHAR_TO_UTF8(*Path), O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (Handle < 0)
    {
        return false;
    }
    close(Handle);
    return chmod(TCHAR_TO_UTF8(*Path), S_IRUSR | S_IWUSR) == 0;
#endif
}

// Replace Destination with Source in one step, keeping Destination when it fails
bool ReplaceFile(const FString& Source, const FString& Destination)
{
#if PLATFORM_WINDOWS
    return ::MoveFileExW(*FPaths::ConvertRelativePathToFull(Source), *FPaths::ConvertRelativePathToFull(Destination),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
    return rename(TCHAR_TO_UTF8(*Source), TCHAR_TO_UTF8(*Destination)) == 0;
#endif
}

void ShowSavedToken(const FString& Token)
{
    if (UArcweaveUserSettings* UserSettings = GetMutableDefault<UArcweaveUserSettings>())
    {
        UserSettings->APIToken = Token;
    }
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

    FileManager.MakeDirectory(*FPaths::GetPath(Path), true);
    if (TrimmedToken.IsEmpty())
    {
        if (FPaths::FileExists(Path) && !FileManager.Delete(*Path, false, true, true))
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't remove the saved API token (%s)."), *Path);
            return false;
        }
        // A cleared token stays cleared: don't copy one saved by an earlier version again
        LegacyAPIToken.Reset();
        if (!WriteMigratedMarker())
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't write %s, so a token saved by an earlier version may be copied again on the next start."), *GetMigratedMarkerPath());
        }
        APIToken.Reset();
        ShowSavedToken(FString());
        return true;
    }

    // Write and check a private copy, then replace the saved token with it in one step
    const FString TempPath = FString::Printf(TEXT("%s.%s.tmp"), *Path, *FGuid::NewGuid().ToString(EGuidFormats::Digits));
    FString Written;
    const bool bSaved = CreatePrivateFile(TempPath)
        && FFileHelper::SaveStringToFile(TrimmedToken, *TempPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM)
        && FFileHelper::LoadFileToString(Written, *TempPath) && Written.Equals(TrimmedToken, ESearchCase::CaseSensitive)
        && ReplaceFile(TempPath, Path)
        && GetUserAPIToken().Equals(TrimmedToken, ESearchCase::CaseSensitive);
    FileManager.Delete(*TempPath, false, true, true);

    if (!bSaved)
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't save the API token to %s."), *Path);
        return false;
    }
    APIToken = TrimmedToken;
    ShowSavedToken(TrimmedToken);
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
        if (!bInSection || Trimmed.IsEmpty())
        {
            continue;
        }

        // A commented-out assignment isn't used, but the file still contains its value
        const bool bCommented = Trimmed[0] == TEXT(';');
        if (bCommented)
        {
            while (Trimmed.StartsWith(TEXT(";")))
            {
                Trimmed.RightChopInline(1);
            }
            Trimmed.TrimStartInline();
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

        // Any value written in the file counts, even one that is removed, cleared or commented out
        if (Command != TEXT('!') && !Value.IsEmpty())
        {
            bOutHasNonEmptyValue = true;
        }
        if (bCommented)
        {
            continue;
        }

        bFound = true;
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

    // Read the files themselves: reading the token through the config system could record it, for example in a cook
    const FString DefaultIni = FPaths::ConvertRelativePathToFull(GetDefaultConfigFilename());
    FString IniText;
    FString ProjectToken;
    bool bProjectDisclosesToken = false;
    if (FPaths::FileExists(DefaultIni) && FFileHelper::LoadFileToString(IniText, *DefaultIni))
    {
        FindIniValue(IniText, ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, ProjectToken, bProjectDisclosesToken);
    }

    if (!IsRunningCommandlet())
    {
        // What earlier versions used: the project config, overridden by the user's Saved/Config/<Platform>/Game.ini
        FString LegacyToken = ProjectToken;
        const FString SavedIni = FPaths::ConvertRelativePathToFull(
            FPaths::Combine(FPaths::GeneratedConfigDir(), ANSI_TO_TCHAR(FPlatformProperties::PlatformName()), TEXT("Game.ini")));
        FString SavedToken;
        bool bSavedDisclosesToken = false;
        if (FPaths::FileExists(SavedIni) && FFileHelper::LoadFileToString(IniText, *SavedIni)
            && FindIniValue(IniText, ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, SavedToken, bSavedDisclosesToken))
        {
            LegacyToken = SavedToken;
        }
        LegacyToken.TrimStartAndEndInline();

        // Only when nothing is saved for the user and the token was never cleared or copied before
        if (!LegacyToken.IsEmpty() && !FPaths::FileExists(GetUserAPITokenPath()) && !FPaths::FileExists(GetMigratedMarkerPath()))
        {
            // Copy it once, in an editor someone is using; unattended runs such as automation only use it in memory
            const bool bInteractiveEditor = GIsEditor && !FApp::IsUnattended();
            if (bInteractiveEditor && SetUserAPIToken(LegacyToken))
            {
                if (!WriteMigratedMarker())
                {
                    UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't write %s."), *GetMigratedMarkerPath());
                }
                UE_LOG(LogArcwarePlugin, Log, TEXT("Arcweave: copied the API token saved by an earlier version to %s"), *GetUserAPITokenPath());
            }
            else
            {
                LegacyAPIToken = LegacyToken;
            }
        }
    }

    if (!bProjectDisclosesToken)
    {
        return;
    }

    if (IsRunningCommandlet())
    {
        UE_LOG(LogArcwarePlugin, Error, TEXT("Arcweave: %s contains an API token in the [%s] section, so a packaged game would contain it. Remove the APIToken lines from that section, including commented-out ones; the token is saved per user now. If the file was committed or a build with it was shared, revoke the token in your Arcweave workspace."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION);
    }
    else
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token in the [%s] section. The token is saved per user now (%s), and that file is usually committed to version control and packaged with the game: remove the APIToken lines from that section, including commented-out ones. If the file was committed or a build with it was shared, revoke the token in your Arcweave workspace and create a new one. Cooking with a cook commandlet fails while it is there."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION, *GetUserAPITokenPath());
    }
#endif
}
