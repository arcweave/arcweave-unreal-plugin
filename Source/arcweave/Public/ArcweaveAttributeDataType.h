#pragma once

// Engine includes
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveAttributeDataType.generated.h"

/**
 * Represents the type of attribute in an Arcweave project (cType field):
 * Attribute can:
 * - belong to an element
 * - be globally defined
 * - be part of a component
 * - belong to a board
 */
UENUM(BlueprintType)
enum class EArcweaveAttributeDataType : uint8
{
    Undefined UMETA(DisplayName = "Undefined"),
    Elements UMETA(DisplayName = "Elements"),
    Global UMETA(DisplayName = "Global"),
    Components UMETA(DisplayName = "Components"),
    Boards UMETA(DisplayName = "Boards"),
};
