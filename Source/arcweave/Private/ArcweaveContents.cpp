// Fill out your copyright notice in the Description page of Project Settings.

// File include
#include "ArcweaveContents.h"

FArcweaveContent FArcweaveContents::GetContent(const FString& Id) const
{
    if (Contents.Contains(Id))
    {
        return Contents[Id];
    }
    return FArcweaveContent();
}

void FArcweaveContents::AddContent(const FString& ContentKey, const FArcweaveContent& Content)
{
    Contents.Add(ContentKey, Content);
}
