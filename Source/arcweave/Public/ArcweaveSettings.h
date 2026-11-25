// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Engine includes
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, DefaultConfig)
class ARCWEAVE_API UArcweaveSettings : public UObject
{
    GENERATED_BODY()

public:
    UArcweaveSettings();

    /*
     * Enable to receive the data from local JSON file instead of API.
     * The JSON file and resource files should be located in the JsonDirectoryPath folder.
     */
    UPROPERTY(Config, EditAnywhere, Category = "ArcweaveSettings")
    bool EnableReceiveMethodFromLocalJSON = false;

    UPROPERTY(
        Config,
        EditAnywhere,
        meta = (
            EditCondition = "EnableReceiveMethodFromLocalJSON",
            ToolTip = "Insert the folder path relative to the project folder containing the .json file"
            ),
        Category = ArcweaveSettings
    )
    FString JsonDirectoryPath = FString("Content/ArcweaveExport/");

    /*
     * API key of your Arcweave workspace. It is saved for your user only, in Saved/Arcweave/APIToken.txt, and never in
     * Config/DefaultGame.ini. The ARCWEAVE_API_KEY environment variable overrides it.
     */
    UPROPERTY(
        Transient,
        EditAnywhere,
        meta = (
            EditCondition = "!EnableReceiveMethodFromLocalJSON",
            PasswordField = true,
            ToolTip = "API key of your Arcweave workspace. Saved for your user only, in Saved/Arcweave/APIToken.txt, never in Config/DefaultGame.ini. The ARCWEAVE_API_KEY environment variable overrides it."
            ),
        Category = "ArcweaveSettings"
    )
    FString APIToken = FString("");

    /*
     * Project hash that we want to retrieve the information for. You can find it by looking at the URL of your project.
     */
    UPROPERTY(Config, EditAnywhere, meta = (EditCondition = "!EnableReceiveMethodFromLocalJSON"), Category = "ArcweaveSettings")
    FString Hash = FString("");

    //override post init properties to check if the settings are valid
    virtual void PostInitProperties() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

    /** True once after the API token was edited in the settings, which then don't need saving to the project config. */
    static bool ConsumeAPITokenEdit();
#endif

#pragma region API token

    /** Name of the environment variable that overrides the saved API token. */
    static const TCHAR* ApiTokenEnvironmentVariable;

    /**
     * The API token to use: the ARCWEAVE_API_KEY environment variable when it is set, else the token saved for this user.
     * In the editor only, a token that an older plugin version saved in the project config is used last, when it couldn't
     * be copied to the user file. Packaged games never read the token from the project config.
     */
    static FString ResolveAPIToken();

    /**
     * Save the token for this user only, in Saved/Arcweave/APIToken.txt. An empty token removes the file.
     * Returns false, keeping the saved token, when the file couldn't be written and read back with the same token.
     */
    bool SetUserAPIToken(const FString& Token);

    /** The token saved for this user, without the environment variable or the project config. */
    static FString GetUserAPIToken();

    /** Full path of the file the token is saved in for this user. */
    static FString GetUserAPITokenPath();

    /** Tests only: save the user token in another file. An empty path restores the default. */
    static void SetUserAPITokenPathForTests(const FString& Path);

    /**
     * Find Key in Section of an ini file's text, following Unreal's syntax. OutValue is its value after all assignments,
     * unquoted. bOutHasNonEmptyValue is true when any line assigns a non-empty value, even one a later line clears.
     */
    static bool FindIniValue(const FString& IniText, const FString& Section, const FString& Key, FString& OutValue, bool& bOutHasNonEmptyValue);

private:
    /**
     * Copy a token that an older plugin version saved in the project config to the user file, once (interactive editor
     * only), and warn while Config/DefaultGame.ini still contains one. Commandlets such as cooking log an error instead,
     * since the token would be packaged. Project files are never changed.
     */
    void CheckProjectAPIToken();

public:

#pragma endregion

#pragma region Language

public:
    bool GetUseLocale() const { return bUseLocale; }

    void SetUseLocale(bool bValue) { bUseLocale = bValue; }

    FString GetLocale() const;

    void SetLocale(const FString& CustomLocale) { Locale = CustomLocale; }

    bool GetFallbackToDefaultLocale() const { return bFallbackToDefaultLocale; }

    void SetFallbackToDefaultLocale(bool bValue) { bFallbackToDefaultLocale = bValue; }

private:
    UPROPERTY(
        Config,
        EditAnywhere,
        meta = (ToolTip = "Allow using a custom language for the application if available (e.g. en, it, fr ...)"),
        Category = ArcweaveSettings
        )
    bool bUseLocale = false;

    UPROPERTY(
        Config,
        EditAnywhere,
        meta = (
            EditCondition = "bUseLocale",
            ToolTip = "Default language used for the application if available (e.g. en, it, fr ...)"
            ),
        Category = ArcweaveSettings
    )
    FString Locale = FString("en");

    UPROPERTY(
        Config,
        EditAnywhere,
        meta = (
            EditCondition = "bUseLocale",
            ToolTip = "If the specified language is not available, fallback to the standard language (the one defined for the current locale as base in the app)"
            ),
        Category = ArcweaveSettings
    )
    bool bFallbackToDefaultLocale = true;

#pragma endregion

};
