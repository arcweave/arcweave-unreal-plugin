#pragma once

// Engine includes
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveAttributeDataType.h"

static class ArcweaveUtils
{

public: 

    static const EArcweaveAttributeDataType* TryGetEnumFromString(FString& Type);

protected:
    static const TMap<FString, EArcweaveAttributeDataType> AttributeEnumDataTypeMap;
};


