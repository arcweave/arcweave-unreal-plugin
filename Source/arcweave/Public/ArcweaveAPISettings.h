#pragma once

// Engine includes
#include "CoreMinimal.h"

#include "ArcweaveAPISettings.generated.h"

//struct holding all the settings for the plugin
USTRUCT(BlueprintType)
struct FArcweaveAPISettings
{
	GENERATED_BODY()

    /*
     * API token that you can find in your Arcweave account settings.
     */
    UPROPERTY(Config, EditAnywhere, Category = ArcweaveSettings)
    bool EnableReceiveMethodFromLocalJSON = false;

	/*
	 * API key of your Arcweave workspace: ARCWEAVE_API_KEY when it is set, else the token saved for this user in
	 * Saved/Arcweave/APIToken.txt. It is never saved in Config/DefaultGame.ini.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Arcweave| Settings")
	FString APIToken = FString("");

	/*
	 * Project hash that we want to retrieve the information for. You can find it by looking at the URL of your project.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Arcweave| Settings")
	FString Hash = FString("");

    UPROPERTY(
        BlueprintReadWrite,
        Category = "Arcweave| Settings",
        meta = (
            EditCondition = "EnableReceiveMethodFromLocalJSON",
            ToolTip = "Insert the folder path containing the .json file"
            )
    )
    FString JsonDirectoryPath = FString("Content/ArcweaveExport/");


#pragma region Language

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave| Settings", meta = (ToolTip = "Allow using a custom language for the application if available (e.g. en, it, fr ...)"))
    bool bUseLocale = false;


    UPROPERTY(
        BlueprintReadWrite,
        Category = "Arcweave| Settings",
        meta = (
            EditCondition = "bUseLocale",
            ToolTip = "Default language used for the application if available (e.g. en, it, fr ...)"
            )
    )
    FString Locale = FString("en");

    UPROPERTY(BlueprintReadWrite,
        Category = "Arcweave| Settings",
        meta = (
            EditCondition = "bUseLocale",
            ToolTip = "When a text has no translation in the chosen language, use the text of the language it translates from, down to the main language. For a language the project doesn't have, an All languages JSON import uses the main language with a warning, while the Web API returns empty texts or an error."
            )
    )
    bool bFallbackToDefaultLocale = true;

#pragma endregion

    FArcweaveAPISettings()
        : EnableReceiveMethodFromLocalJSON(false)
        , APIToken(FString(""))
        , Hash(FString(""))
        , bUseLocale(false)
        , Locale(FString("en"))
        , bFallbackToDefaultLocale(true)
    {}
};