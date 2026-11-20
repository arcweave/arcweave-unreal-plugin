// Fill out your copyright notice in the Description page of Project Settings.

// File include
#include "ArcweaveContents.h"

const FArcweaveContent* FArcweaveContents::GetContent(const FString& Id) const
{
    return Contents.Find(Id);
}

void FArcweaveContents::AddContent(const FString& ContentKey, const FArcweaveContent& Content)
{
    Contents.Add(ContentKey, Content);
}

void FArcweaveContents::PrintContents() const
{
    //Print contents
    UE_LOG(LogTemp, Log, TEXT(" ---- CONTENTS ---- "));

    for (const TPair<FString, FArcweaveContent>& Pair : Contents)
    {
        const FString& Key = Pair.Key;
        const FArcweaveContent& LocalizedText = Pair.Value;
        UE_LOG(LogTemp, Log, TEXT(" Key: %s"), *Key);
        LocalizedText.PrintContent();
    }

    UE_LOG(LogTemp, Log, TEXT(" ---- ---------- ---- "));

}
