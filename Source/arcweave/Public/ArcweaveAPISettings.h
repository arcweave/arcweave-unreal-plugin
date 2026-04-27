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
	 * API token that you can find in your Arcweave account settings.
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
    FString JsonFilePath = FString("Content/ArcweaveExport/");


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
    FString Locale = FString("");

    UPROPERTY(BlueprintReadWrite,
        Category = "Arcweave| Settings",
        meta = (
            EditCondition = "!EnableReceiveMethodFromLocalJSON && bUseLocale",
            ToolTip = "If the specified language is not available, fallback to the standard language (usually en-us). This option is available only from web api"
            )
    )
    bool bFallbackToDefaultLocale = true;

#pragma endregion

    FArcweaveAPISettings()
        : EnableReceiveMethodFromLocalJSON(false)
        , APIToken(FString(""))
        , Hash(FString(""))
        , bUseLocale(false)
        , Locale(FString(""))
        , bFallbackToDefaultLocale(true)
    {}
};