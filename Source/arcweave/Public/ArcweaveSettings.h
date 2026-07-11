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
     * The JSON file and resource files should be located in the Content/ArcweaveExport folder.
     */
    UPROPERTY(Config, EditAnywhere, Category = "ArcweaveSettings")
    bool EnableReceiveMethodFromLocalJSON = false;

    /*
     * API token that you can find in your Arcweave account settings.
     */
    UPROPERTY(Config, EditAnywhere, meta = (EditCondition = "!EnableReceiveMethodFromLocalJSON"), Category = "ArcweaveSettings")
    FString APIToken = FString("");

    /*
     * Project hash that we want to retrieve the information for. You can find it by looking at the URL of your project.
     */
    UPROPERTY(Config, EditAnywhere, meta = (EditCondition = "!EnableReceiveMethodFromLocalJSON"), Category = "ArcweaveSettings")
    FString Hash = FString("");

    //override post init properties to check if the settings are valid
    virtual void PostInitProperties() override;


#pragma region Language

public:
    bool GetUseLocale() const { return bUseLocale; }

    void SetUseLocale(bool bValue) { bUseLocale = bValue; }

    FString GetLocale() const;

    void SetLocale(const FString& CustomLocale) { Locale = CustomLocale; }

    bool GetFallbackToDefaultLocale() const { return bFallbackToDefaultLocale; }

    void SetFallbackToDefaultLocale(bool bValue) { bFallbackToDefaultLocale = bValue; }

private:
    UPROPERTY(Config,
        EditAnywhere,
        Category = "ArcweaveSettings| Languages",
        meta = (
            ToolTip = "Allow using a custom language for the application if available (e.g. en, it, fr ...)"
            )
    )
    bool bUseLocale = false;


    UPROPERTY(Config,
        EditAnywhere,
        Category = "ArcweaveSettings| Languages",
        meta = (
            EditCondition = "bUseLocale",
            ToolTip = "Default language used for the application if available (e.g. en, it, fr ...)"
            )
    )
    FString Locale = FString("fr");

    UPROPERTY(Config,
        EditAnywhere,
        Category = "ArcweaveSettings| Languages",
        meta = (
            EditCondition = "bUseLocale",
            ToolTip = "If the specified language is not available, fallback to the standard language (the one defined for the current locale as base in the app)"
            )
    )
    bool bFallbackToDefaultLocale = true;

#pragma endregion

};
