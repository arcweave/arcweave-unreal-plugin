// Fill out your copyright notice in the Description page of Project Settings.

// File include
#include "ArcweaveContent.h"

bool FArcweaveContent::GetTranslationForKey(FString& OutTranslation, const FString& Locale, const FString& Key) const
{
    const FArcweaveLocalizedText* localizedText = LocalizedStringFields.Find(Key);

    if (localizedText != nullptr)
    {
        return localizedText->GetTranslation(OutTranslation, Locale);
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

void FArcweaveContent::PrintContent() const
{
    UE_LOG(LogTemp, Log, TEXT(" ---- ArcweaveContent: LocalizedStringFields count: %d ----"), LocalizedStringFields.Num());
    for (const TPair<FString, FArcweaveLocalizedText>& Pair : LocalizedStringFields)
    {
        const FString& Key = Pair.Key;
        const FArcweaveLocalizedText& LocalizedText = Pair.Value;
        UE_LOG(LogTemp, Log, TEXT("  Key: %s"), *Key);
        LocalizedText.PrintTranslations();
    }

    UE_LOG(LogTemp, Log, TEXT(" ---- ------------------------------------------------- ----"));

}
