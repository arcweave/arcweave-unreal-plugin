#pragma once

// Engine includes
#include "Containers/Map.h"
#include "CoreMinimal.h"

// Arcweave includes
#include "ArcweaveAttributeValueDataType.h"
#include "ArcweaveComponentType.h"

static class ArcweaveUtils
{


public:
    // Helper function to get from input string the enum representing the possible attribute value data type
    static const EArcweaveAttributeValueDataType* TryGetAttributeValueDataTypeFromString(const FString& Type);

    // Helper function to get the relative cType enum respect to the string extrapolated from the json
    static const EArcweaveComponentType* TryGetComponentType(const FString& Type);

protected:
    static const TMap<FString, EArcweaveAttributeValueDataType> AttributeValueDataTypeMap;

    // Map holding information to switch from string to ctype enum class
    static const TMap<FString, EArcweaveComponentType> ComponentTypeMap;

};


