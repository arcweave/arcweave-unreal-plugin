// Fill out your copyright notice in the Description page of Project Settings.

// File include
#include "ArcweaveContent.h"

bool FArcweaveContent::GetTranslationForKey(FString& OutTranslation, const FString& Locale, const FString& Key) const
{
    if (LocalizedStringFields.Contains(Key))
    {
        return LocalizedStringFields[Key].GetTranslation(OutTranslation, Locale);
    }

    return false;
}

void FArcweaveContent::AddTranslationForKey(const FString& Locale, const FString& Translation, const FString& Key)
{
    if (LocalizedStringFields.Contains(Key))
    {
        FArcweaveLocalizedText& LocalizedTextRef = LocalizedStringFields[Key];
        LocalizedTextRef.AddTranslation(Locale, Translation);
    }
    else
    {
        FArcweaveLocalizedText LocalizedText;
        LocalizedText.AddTranslation(Locale, Translation);
        LocalizedStringFields.Add(Key, LocalizedText);
    }

}
