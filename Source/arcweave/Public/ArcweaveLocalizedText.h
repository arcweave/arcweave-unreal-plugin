#pragma once

// Engine include
#include "Containers/Map.h"
#include "Containers/UnrealString.h"

// Generate include
#include "ArcweaveLocalizedText.generated.h"

/*
* This class keeps record of the translation of the arcweave content in
* the different locales (e.g. en, fr, it...)
*/
USTRUCT(BlueprintType)
struct FArcweaveLocalizedText
{
    GENERATED_BODY()

    void AddTranslation(const FString& Locale, const FString& Translation);

    /* 
    * Try get translation for the defined locale, return false if it can't find anything
    */
    bool GetTranslation(FString& OutTranslation, const FString& Locale) const;

private:
    TMap<FString, FString> TextTranslations;
};