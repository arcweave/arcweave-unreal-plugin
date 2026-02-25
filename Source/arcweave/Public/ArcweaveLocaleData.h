
#pragma once

#include "ArcweaveLocaleData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveLocaleData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Iso = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Base = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Name = FString("");

    FArcweaveLocaleData()
        : Iso(FString(""))
        , Base()
        , Name(FString(""))
    {}
};