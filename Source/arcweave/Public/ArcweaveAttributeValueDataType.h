#pragma once

// Engine includes
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveAttributeValueDataType.generated.h"

/**
 * Represents the type of data stored in an Arcweave attribute
 */
UENUM(BlueprintType)
enum class EArcweaveAttributeValueDataType : uint8
{
    Undefined UMETA(DisplayName = "Undefined"),
    String UMETA(DisplayName = "String (Plain Text)"),
    StringRichText UMETA(DisplayName = "String (Rich Text)"),
    ComponentList UMETA(DisplayName = "Component List"),
    AssetList UMETA(DisplayName = "Asset List")
};
