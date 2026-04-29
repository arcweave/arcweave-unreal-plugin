#pragma once

// Engine includes
#include "CoreMinimal.h"
#include "Containers/Map.h"

// Arcweave includes
#include "ArcweaveAttributeDataType.h"
#include "ArcweaveAttributeValueDataType.h"

static class ArcweaveUtils
{

public: 

    static const EArcweaveAttributeValueDataType* TryGetAttributeValueDataTypeFromString(const FString& Type);
    static const EArcweaveAttributeDataType* TryGetAttributeDataTypeFromString(const FString& Type);

protected:
    static const TMap<FString, EArcweaveAttributeValueDataType> AttributeValueDataTypeMap;
    static const TMap<FString, EArcweaveAttributeDataType> AttributeDataTypeMap;
};


