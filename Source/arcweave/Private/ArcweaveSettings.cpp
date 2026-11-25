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

namespace
{
const TCHAR* ApiTokenKey = TEXT("APIToken");

// Set once this session removed the token from Config/DefaultGame.ini, whose values stay loaded until a restart
bool bProjectAPITokenRemoved = false;
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
        // Before the default config file is rewritten, so the old token is still there to move
        const bool bTokenLeftInProjectConfig = MigrateProjectAPIToken();
        APIToken = GetUserAPIToken();
        if (bTokenLeftInProjectConfig)
        {
            // Rewriting the section would drop the token, which is no longer a config property, without saving it anywhere
            return;
        }
    }
	TryUpdateDefaultConfigFile(TEXT(""), false);
}

#if WITH_EDITOR
void UArcweaveSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    UObject::PostEditChangeProperty(PropertyChangedEvent);
    if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(UArcweaveSettings, APIToken))
    {
        SetUserAPIToken(APIToken);
    }
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
    if (GConfig != nullptr && !bProjectAPITokenRemoved
        && GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, Token, GGameIni) && !Token.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: using an API token saved in the project config (Config/DefaultGame.ini), which is usually committed to version control and packaged with the game. Remove the APIToken line from that file and enter the token again in Project Settings > Plugins > Arcweave, or set %s."), ApiTokenEnvironmentVariable);
        return Token;
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
                if (OutLastValue != nullptr && (!bHasOperator || Trimmed[0] == TEXT('+')))
                {
                    FString Value = Assignment.RightChop(EqualsIndex + 1).TrimStartAndEnd();
                    if (Value.Len() >= 2 && Value.StartsWith(TEXT("\"")) && Value.EndsWith(TEXT("\"")))
                    {
                        Value = Value.Mid(1, Value.Len() - 2);
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
    const FString DefaultIni = FPaths::ConvertRelativePathToFull(GetDefaultConfigFilename());
    FString IniText;
    if (!FPaths::FileExists(DefaultIni) || !FFileHelper::LoadFileToString(IniText, *DefaultIni))
    {
        return false;
    }

    FString NewText;
    FString ProjectToken;
    if (!RemoveIniKey(IniText, ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, NewText, &ProjectToken))
    {
        return false;
    }

    // Cooking and other commandlets, and -game runs, don't change the project or the user's files
    if (!GIsEditor || IsRunningCommandlet())
    {
        if (!ProjectToken.IsEmpty() && IsRunningCommandlet())
        {
            UE_LOG(LogArcwarePlugin, Error, TEXT("Arcweave: %s contains an API token, so a packaged game would contain it. Open the project in the editor to move it to your user settings, or remove the APIToken line from the [%s] section. If the file was committed, revoke the token in your Arcweave workspace."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION);
        }
        else if (!ProjectToken.IsEmpty())
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token. Open the project in the editor to move it to your user settings."), *DefaultIni);
        }
        return !ProjectToken.IsEmpty();
    }

    const FString UserToken = GetUserAPIToken();
    if (!ProjectToken.IsEmpty() && UserToken.IsEmpty() && !SetUserAPIToken(ProjectToken))
    {
        // Keep the only copy of the token
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token, which is usually committed to version control and packaged with the game. It was left there because it couldn't be saved to %s."), *DefaultIni, *GetUserAPITokenPath());
        return true;
    }

    // Keep the file's encoding
    TArray<uint8> Bytes;
    FFileHelper::LoadFileToArray(Bytes, *DefaultIni);
    FFileHelper::EEncodingOptions Encoding = FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM;
    bool bCanWrite = !IFileManager::Get().IsReadOnly(*DefaultIni);
    if (Bytes.Num() >= 2 && Bytes[0] == 0xFE && Bytes[1] == 0xFF)
    {
        // UTF-16 big endian can't be written back as it was
        bCanWrite = false;
    }
    else if (Bytes.Num() >= 2 && Bytes[0] == 0xFF && Bytes[1] == 0xFE)
    {
        Encoding = FFileHelper::EEncodingOptions::ForceUnicode;
    }
    else if (Bytes.Num() >= 3 && Bytes[0] == 0xEF && Bytes[1] == 0xBB && Bytes[2] == 0xBF)
    {
        Encoding = FFileHelper::EEncodingOptions::ForceUTF8;
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
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token, which is usually committed to version control and packaged with the game. It could not be removed because the file can't be written (check it out if you use source control). Remove the APIToken line from the [%s] section, and if the file was committed, revoke the token in your Arcweave workspace."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION);
        }
        return !ProjectToken.IsEmpty();
    }

    bProjectAPITokenRemoved = true;
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
