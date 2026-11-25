// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcweaveSettings.h"

#include "arcweave.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformMisc.h"
#include "HAL/PlatformProperties.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

namespace
{
const TCHAR* ApiTokenKey = TEXT("APIToken");

// Where GameUserSettings is saved, for messages: GGameUserSettingsIni is only a config name in recent engine versions
FString GetUserSettingsPath()
{
    return FPaths::ConvertRelativePathToFull(
        FPaths::Combine(FPaths::GeneratedConfigDir(), ANSI_TO_TCHAR(FPlatformProperties::PlatformName()), TEXT("GameUserSettings.ini")));
}

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
        MigrateProjectAPIToken();
        APIToken = GetUserAPIToken();
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

    if (GConfig != nullptr && !bProjectAPITokenRemoved
        && GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, Token, GGameIni) && !Token.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: using an API token saved in the project config (Config/DefaultGame.ini), which is usually committed to version control and packaged with the game. Open the project in the editor to move it to your user settings, or remove it and set %s."), ApiTokenEnvironmentVariable);
        return Token;
    }
    return FString();
}

FString UArcweaveSettings::GetUserAPIToken()
{
    FString Token;
    if (GConfig != nullptr)
    {
        GConfig->GetString(ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, Token, GGameUserSettingsIni);
    }
    return Token;
}

void UArcweaveSettings::SetUserAPIToken(const FString& Token)
{
    APIToken = Token;
    if (GConfig == nullptr)
    {
        return;
    }

    if (Token.IsEmpty())
    {
        GConfig->RemoveKey(ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, GGameUserSettingsIni);
    }
    else
    {
        GConfig->SetString(ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, *Token, GGameUserSettingsIni);
    }
    GConfig->Flush(false, GGameUserSettingsIni);
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
        if (Trimmed.StartsWith(TEXT("[")) && Trimmed.EndsWith(TEXT("]")))
        {
            bInSection = Trimmed.Mid(1, Trimmed.Len() - 2).TrimStartAndEnd().Equals(Section, ESearchCase::IgnoreCase);
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

void UArcweaveSettings::MigrateProjectAPIToken()
{
#if WITH_EDITOR
    if (GConfig == nullptr)
    {
        return;
    }

    const FString DefaultIni = GetDefaultConfigFilename();
    FString IniText;
    if (!FPaths::FileExists(DefaultIni) || !FFileHelper::LoadFileToString(IniText, *DefaultIni))
    {
        return;
    }

    FString NewText;
    FString ProjectToken;
    if (!RemoveIniKey(IniText, ARCWEAVE_SETTINGS_SECTION, ApiTokenKey, NewText, &ProjectToken))
    {
        return;
    }

    const FString UserToken = GetUserAPIToken();
    if (!ProjectToken.IsEmpty() && UserToken.IsEmpty())
    {
        SetUserAPIToken(ProjectToken);
    }

    // Keep the file's encoding
    TArray<uint8> Bytes;
    FFileHelper::LoadFileToArray(Bytes, *DefaultIni);
    FFileHelper::EEncodingOptions Encoding = FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM;
    if (Bytes.Num() >= 2 && ((Bytes[0] == 0xFF && Bytes[1] == 0xFE) || (Bytes[0] == 0xFE && Bytes[1] == 0xFF)))
    {
        Encoding = FFileHelper::EEncodingOptions::ForceUnicode;
    }
    else if (Bytes.Num() >= 3 && Bytes[0] == 0xEF && Bytes[1] == 0xBB && Bytes[2] == 0xBF)
    {
        Encoding = FFileHelper::EEncodingOptions::ForceUTF8;
    }

    if (IFileManager::Get().IsReadOnly(*DefaultIni) || !FFileHelper::SaveStringToFile(NewText, *DefaultIni, Encoding))
    {
        if (!ProjectToken.IsEmpty())
        {
            UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: %s contains an API token, and that file is usually committed to version control and packaged with the game. It could not be removed because the file can't be written (check it out if you use source control). Remove the APIToken line from the [%s] section."), *DefaultIni, ARCWEAVE_SETTINGS_SECTION);
        }
        return;
    }

    bProjectAPITokenRemoved = true;
    if (ProjectToken.IsEmpty())
    {
        UE_LOG(LogArcwarePlugin, Log, TEXT("Arcweave: removed the empty APIToken setting from %s"), *DefaultIni);
    }
    else if (UserToken.IsEmpty() || UserToken == ProjectToken)
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: moved the API token from %s to your user settings (%s). If the project config was committed, the token is in your version control history: revoke it in your Arcweave workspace and create a new one."), *DefaultIni, *GetUserSettingsPath());
    }
    else
    {
        UE_LOG(LogArcwarePlugin, Warning, TEXT("Arcweave: removed an API token from %s and kept the different token in your user settings (%s). If the project config was committed, the removed token is in your version control history: revoke it in your Arcweave workspace."), *DefaultIni, *GetUserSettingsPath());
    }
#endif
}
