#pragma once

// Engine include
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveComponentData.h"
#include <Templates/SharedPointer.h>

// Generated include
#include "ArcweaveComponentsData.generated.h"

USTRUCT(BlueprintType)
struct FArcweaveComponentsData
{
    GENERATED_BODY()

public:
    TSharedPtr<FArcweaveComponentData> ComponentDatPtr;

};