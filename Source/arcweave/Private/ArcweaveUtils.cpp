// File include
#include "ArcweaveUtils.h"

// Engine includes
#include "Containers/Map.h"
#include "HAL/Platform.h"

const TMap<FString, EArcweaveAttributeValueDataType> ArcweaveUtils::AttributeValueDataTypeMap =
{
    { TEXT("string"),  EArcweaveAttributeValueDataType::String },
    { TEXT("StringRichText"), EArcweaveAttributeValueDataType::StringRichText },
    { TEXT("component-list"), EArcweaveAttributeValueDataType::ComponentList },
    { TEXT("asset-list"),   EArcweaveAttributeValueDataType::AssetList }
};

const EArcweaveAttributeValueDataType* ArcweaveUtils::TryGetAttributeValueDataTypeFromString(const FString& Type)
{
    return AttributeValueDataTypeMap.Find(Type);
}

const TMap <FString, EArcweaveComponentType> ArcweaveUtils::ComponentTypeMap =
{
    { TEXT("boards"),  EArcweaveComponentType::Boards },
    { TEXT("components"),   EArcweaveComponentType::Components },
    { TEXT("elements"),   EArcweaveComponentType::Elements },
    { TEXT("global"),   EArcweaveComponentType::Global },
    { TEXT("undefined"),   EArcweaveComponentType::Undefined }
};

const EArcweaveComponentType* ArcweaveUtils::TryGetComponentType(const FString& Type)
{
    return ComponentTypeMap.Find(Type);
}
