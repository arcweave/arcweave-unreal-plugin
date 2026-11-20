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

    /** Returns the content with the given id, or nullptr if there is none. The pointer is valid until the contents are changed */
    const FArcweaveContent* GetContent(const FString& Id) const;

    void AddContent(const FString& ContentKey, const FArcweaveContent& Content);

    void PrintContents() const;

    bool IsEmpty() const { return Contents.IsEmpty(); }

private:
    /*
    * Map containing all the contents of the project, indexed by their id.
    */
    TMap<FString, FArcweaveContent> Contents;
};
