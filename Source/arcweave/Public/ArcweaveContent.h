// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Plugin include
#include "ArcweaveLocalizedText.h"

// Engine include
#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "JsonObjectConverter.h"

#include "ArcweaveContent.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveContent {

    GENERATED_BODY()

    bool GetTranslationForKey(FString& OutTranslation, const FString& Locale, const FString& Key) const;

    void AddTranslationForKey(const FString& Locale, const FString& Translation, const FString& Key);

    void PrintContent() const;

private: 
    /*
    * Will contain value for the content fields (e.g label, title, text)
    */
    TMap<FString, FArcweaveLocalizedText> LocalizedStringFields;


};