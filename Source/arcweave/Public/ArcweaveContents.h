// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Plugin includes
#include "ArcweaveContent.h"

// Engine includes
#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "Containers/UnrealString.h"
#include "JsonObjectConverter.h"

// Generated include
#include "ArcweaveContents.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARCWEAVE_API FArcweaveContents
{
    GENERATED_BODY()

    bool GetContent(FArcweaveContent& OutContent, const FString& Id) const;

    void AddContent(const FString& ContentKey, const FArcweaveContent& Content);

    void PrintContents() const;

private:
    /*
    * Map containg all the contents of the project, indexed by their id.
    */
    TMap<FString, FArcweaveContent> Contents;
};
