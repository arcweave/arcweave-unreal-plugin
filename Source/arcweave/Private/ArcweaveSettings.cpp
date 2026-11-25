// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcweaveSettings.h"

#include "arcweave.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformMisc.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/CoreMisc.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/Parse.h"

#if WITH_EDITOR
#include "UObject/UnrealType.h"
#endif

namespace
{
const TCHAR* ApiTokenKey = TEXT("APIToken");

// A token that an older version saved in Config/DefaultGame.ini and that couldn't be moved (editor only)
FString ProjectAPITokenLeft;

// Set by PostEditChangeProperty, so the settings editor doesn't rewrite the project config for a token edit
bool bAPITokenJustEdited = false;
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
        MigrateProjectAPIToken();
        APIToken = GetUserAPIToken();
    }
}

#if WITH_EDITOR
void UArcweaveSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UObject::PostEditChangeProperty(PropertyChangedEvent);
    if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UArcweaveSettings, APIToken))
    {
        bAPITokenJustEdited = true;
        SetUserAPIToken(APIToken);
    }
}

bool UArcweaveSettings::ConsumeAPITokenEdit()
{
    const bool bWasTokenEdit = bAPITokenJustEdited;
    bAPITokenJustEdited = false;
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

    FString Token = GetUserAPIToken();
    if (!Token.IsEmpty())
    {
        return Token;
    }

#if WITH_EDITOR
    // Only when the token couldn't be moved out of the project config. Packaged games never use it
    if (!ProjectAPITokenLeft.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: using an API token saved in the project config (Config/DefaultGame.ini), which is usually committed to version control and packaged with the game. Remove the APIToken line from that file and enter the token again in Project Settings > Plugins > Arcweave, or set %s."), ApiTokenEnvironmentVariable);
        return ProjectAPITokenLeft;
    }
#endif
    return FString();
}

FString UArcweaveSettings::GetUserAPITokenPath()
{
    return FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("Arcweave"), TEXT("APIToken.txt")));
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
    APIToken = TrimmedToken;
    const FString Path = GetUserAPITokenPath();
    IFileManager& FileManager = IFileManager::Get();

    if (TrimmedToken.IsEmpty())
    {
        if (FPaths::FileExists(Path) && !FileManager.Delete(*Path, false, true, true))
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't remove the saved API token (%s)."), *Path);
            return false;
        }
        return true;
    }

    FileManager.MakeDirectory(*FPaths::GetPath(Path), true);
    FString Saved;
    if (!FFileHelper::SaveStringToFile(TrimmedToken, *Path, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM)
        || !FFileHelper::LoadFileToString(Saved, *Path) || Saved.TrimStartAndEnd() != TrimmedToken)
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: couldn't save the API token to %s."), *Path);
        return false;
    }
    return true;
}

bool UArcweaveSettings::RemoveIniKey(const FString& IniText, const FString& Section, const FString& Key, FString& OutText, FString* OutLastValue)
{
    OutText.Reset(IniText.Len());
    bool bInSection = false;
    bool bRemoved = false;
    const int32 Length = IniText.Len();
    int32 LineStart = 0;
    while (LineStart < Length)
    {
        int32 LineEnd = LineStart;
        while (LineEnd < Length && IniText[LineEnd] != TEXT('\n'))
        {
            ++LineEnd;
        }
        const int32 NextLine = LineEnd < Length ? LineEnd + 1 : LineEnd;
        const FString Line = IniText.Mid(LineStart, NextLine - LineStart);
        const FString Trimmed = Line.TrimStartAndEnd();
        LineStart = NextLine;

        bool bRemoveLine = false;
        int32 SectionEnd = INDEX_NONE;
        if (Trimmed.StartsWith(TEXT("[")) && Trimmed.FindChar(TEXT(']'), SectionEnd))
        {
            // Like Unreal's parser, ignore anything after the closing bracket, such as a comment
            bInSection = Trimmed.Mid(1, SectionEnd - 1).TrimStartAndEnd().Equals(Section, ESearchCase::IgnoreCase);
        }
        else if (bInSection && !Trimmed.IsEmpty())
        {
            // Array operators: +Key=, -Key=, .Key=, !Key=
            const bool bHasOperator = FCString::Strchr(TEXT("+-.!"), Trimmed[0]) != nullptr;
            const FString Assignment = bHasOperator ? Trimmed.RightChop(1) : Trimmed;
            int32 EqualsIndex = INDEX_NONE;
            if (Assignment.FindChar(TEXT('='), EqualsIndex)
                && Assignment.Left(EqualsIndex).TrimStartAndEnd().Equals(Key, ESearchCase::IgnoreCase))
            {
                bRemoveLine = true;
                if (OutLastValue != nullptr && Trimmed[0] == TEXT('!'))
                {
                    // Clears the key
                    OutLastValue->Reset();
                }
                else if (OutLastValue != nullptr && Trimmed[0] != TEXT('-'))
                {
                    FString Value = Assignment.RightChop(EqualsIndex + 1).TrimStartAndEnd();
                    if (Value.StartsWith(TEXT("\"")))
                    {
                        // Unquote and unescape like Unreal's parser
                        FString Unquoted;
                        const TCHAR* Cursor = *Value;
                        if (FParse::QuotedString(Cursor, Unquoted))
                        {
                            Value = Unquoted;
                        }
                    }
                    *OutLastValue = Value;
                }
            }
        }

        if (bRemoveLine)
        {
            bRemoved = true;
        }
        else
        {
            OutText += Line;
        }
    }
    return bRemoved;
}

bool UArcweaveSettings::MigrateProjectAPIToken()
{
#if WITH_EDITOR
    ProjectAPITokenLeft.Reset();
    const FString DefaultIni = FPaths::ConvertRelativePathToFull(GetDefaultConfigFilename());
    TArray<uint8> Bytes;
    FString IniText;
    if (!FPaths::FileExists(DefaultIni) || !FFileHelper::LoadFileToArray(Bytes, *DefaultIni))
    {
        return false;
    }
    FFileHelper::BufferToString(IniText, Bytes.GetData(), Bytes.Num());

    FString NewText;
    FString ProjectToken;
    const bool bHasProjectKey = RemoveIniKey(IniText, ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, NewText, &ProjectToken);
    const FString UserToken = GetUserAPIToken();
    const bool bCanChangeFiles = GIsEditor && !IsRunningCommandlet() && !FParse::Param(FCommandLine::Get(), TEXT("nowrite"));

    // Earlier versions' SaveArcweaveSettings saved the token in the user's Saved/Config/<Platform>/Game.ini, which isn't
    // committed or packaged: copy it, and leave that file to the engine
    FString SavedToken;
    if (bCanChangeFiles && UserToken.IsEmpty() && ProjectToken.IsEmpty() && GConfig != nullptr
        && GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, SavedToken, GGameIni) && !SavedToken.TrimStartAndEnd().IsEmpty()
        && SetUserAPIToken(SavedToken))
    {
        UE_LOG(LogArcwarePlugin, Log, TEXT("Arcweave: copied the API token saved by an earlier version to %s"), *GetUserAPITokenPath());
    }

    if (!bHasProjectKey)
    {
        return false;
    }

    // Cooking and other commandlets, and -game runs, don't change the project or the user's files
    if (!bCanChangeFiles)
    {
        if (!ProjectToken.IsEmpty() && IsRunningCommandlet())
        {
            UE_LOG(LogArcwarePlugin, Error, TEXT("Arcweave: %s contains an API token, so a packaged game would contain it. Open the project in the editor to move it to your user settings, or remove the APIToken line from the [%s] section. If the file was committed, revoke the token in your Arcweave workspace."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION);
        }
        else if (!ProjectToken.IsEmpty())
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token. Open the project in the editor to move it to your user settings."), *DefaultIni);
        }
        ProjectAPITokenLeft = ProjectToken;
        return !ProjectToken.IsEmpty();
    }

    // Keep the file's encoding. UTF-16 big endian can't be written back as it was
    FFileHelper::EEncodingOptions Encoding = FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM;
    bool bCanWrite = !IFileManager::Get().IsReadOnly(*DefaultIni);
    if (Bytes.Num() >= 2 && !(Bytes.Num() & 1) && Bytes[0] == 0xFE && Bytes[1] == 0xFF)
    {
        bCanWrite = false;
    }
    else if (Bytes.Num() >= 2 && !(Bytes.Num() & 1) && Bytes[0] == 0xFF && Bytes[1] == 0xFE)
    {
        Encoding = FFileHelper::EEncodingOptions::ForceUnicode;
    }
    else if (Bytes.Num() >= 3 && Bytes[0] == 0xEF && Bytes[1] == 0xBB && Bytes[2] == 0xBF)
    {
        Encoding = FFileHelper::EEncodingOptions::ForceUTF8;
    }

    // Save the token for the user first, so the project copy is only removed once there is another one
    if (bCanWrite && !ProjectToken.IsEmpty() && UserToken.IsEmpty() && GetUserAPIToken().IsEmpty() && !SetUserAPIToken(ProjectToken))
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token, which is usually committed to version control and packaged with the game. It was left there because it couldn't be saved to %s."), *DefaultIni, *GetUserAPITokenPath());
        ProjectAPITokenLeft = ProjectToken;
        return true;
    }

    // Write a copy and replace the file with it, so a failed write can't truncate the project config
    const FString TempIni = DefaultIni + TEXT(".arcweave-tmp");
    bool bWritten = bCanWrite && FFileHelper::SaveStringToFile(NewText, *TempIni, Encoding);
    if (bWritten)
    {
        FString Written;
        bWritten = FFileHelper::LoadFileToString(Written, *TempIni) && Written == NewText
            && IFileManager::Get().Move(*DefaultIni, *TempIni, true, false);
    }
    IFileManager::Get().Delete(*TempIni, false, false, true);

    if (!bWritten)
    {
        if (!ProjectToken.IsEmpty())
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token, which is usually committed to version control and packaged with the game, and cooking fails while it is there. It could not be removed because the file can't be written (check it out if you use source control). Remove the APIToken line from the [%s] section, and if the file was committed, revoke the token in your Arcweave workspace."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION);
            if (GetUserAPIToken().IsEmpty())
            {
                ProjectAPITokenLeft = ProjectToken;
            }
        }
        return !ProjectToken.IsEmpty();
    }

    if (ProjectToken.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Log, TEXT("Arcweave: removed the empty APIToken setting from %s"), *DefaultIni);
    }
    else if (UserToken.IsEmpty() || UserToken == ProjectToken)
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: moved the API token from %s to your user settings (%s). If the project config was committed, the token is in your version control history: revoke it in your Arcweave workspace and create a new one."), *DefaultIni, *GetUserAPITokenPath());
    }
    else
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: removed an API token from %s and kept the different token in your user settings (%s). If the project config was committed, the removed token is in your version control history: revoke it in your Arcweave workspace."), *DefaultIni, *GetUserAPITokenPath());
    }
    return false;
#else
    return false;
#endif
}
