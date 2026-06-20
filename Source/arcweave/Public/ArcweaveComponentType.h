#pragma once

// Engine includes
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveComponentType.generated.h"

/**
 * Represents the type of component in an Arcweave project (cType field)
 */
UENUM(BlueprintType)
enum class EArcweaveComponentType : uint8
{
	Boards UMETA(DisplayName = "Boards"),
	Components UMETA(DisplayName = "Components"),
	Elements UMETA(DisplayName = "Elements"),
	Global UMETA(DisplayName = "Global"),
	Undefined UMETA(DisplayName = "Undefined"),
};
