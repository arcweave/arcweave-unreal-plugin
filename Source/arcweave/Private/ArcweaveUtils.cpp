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

const TMap<FString, EArcweaveAttributeDataType> ArcweaveUtils::AttributeDataTypeMap =
{
    { TEXT("elements"), EArcweaveAttributeDataType::Elements },
    { TEXT("components"), EArcweaveAttributeDataType::Components },
    { TEXT("global"), EArcweaveAttributeDataType::Global },
};


const EArcweaveAttributeValueDataType* ArcweaveUtils::TryGetAttributeValueDataTypeFromString(const FString& Type)
{
    return AttributeValueDataTypeMap.Find(Type);
}

const EArcweaveAttributeDataType* ArcweaveUtils::TryGetAttributeDataTypeFromString(const FString& Type)
{
    return AttributeDataTypeMap.Find(Type);
}
