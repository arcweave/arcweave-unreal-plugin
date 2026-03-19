#pragma once

// File include
#include "ArcweaveLocalizedText.h"

void FArcweaveLocalizedText::AddTranslation(const FString& Locale, const FString& Translation)
{
    TextTranslations.Add(Locale, Translation);
}

bool FArcweaveLocalizedText::GetTranslation(FString& OutTranslation, const FString& Locale) const
{
    const FString* FoundTranslation = TextTranslations.Find(Locale);
    if (FoundTranslation)
    {
        OutTranslation = *FoundTranslation;
        return true;
    }
    return false;
}

void FArcweaveLocalizedText::PrintTranslations() const
{
    UE_LOG(LogTemp, Log, TEXT(" ---- Translations ----"));
    for (const auto& Pair : TextTranslations)
    {
        UE_LOG(LogTemp, Log, TEXT("Locale: %s, Translation: %s"), *Pair.Key, *Pair.Value);
    }
    UE_LOG(LogTemp, Log, TEXT(" ---- ----------- ----"));

}

