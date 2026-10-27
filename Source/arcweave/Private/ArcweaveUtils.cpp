// File include
#include "ArcweaveUtils.h"

// Engine includes
#include "Containers/Map.h"

const EArcweaveAttributeValueDataType* ArcweaveUtils::TryGetAttributeValueDataTypeFromString(const FString& Type)
{
    static const TMap<FString, EArcweaveAttributeValueDataType> AttributeValueDataTypeMap =
    {
        { TEXT("string"), EArcweaveAttributeValueDataType::String },
        { TEXT("component-list"), EArcweaveAttributeValueDataType::ComponentList },
        { TEXT("asset-list"), EArcweaveAttributeValueDataType::AssetList },
        { TEXT("boolean"), EArcweaveAttributeValueDataType::Boolean },
        { TEXT("integer"), EArcweaveAttributeValueDataType::Integer },
        { TEXT("float"), EArcweaveAttributeValueDataType::Float }
    };
    return AttributeValueDataTypeMap.Find(Type);
}

const EArcweaveAttributeDataType* ArcweaveUtils::TryGetAttributeDataTypeFromString(const FString& Type)
{
    static const TMap<FString, EArcweaveAttributeDataType> AttributeDataTypeMap =
    {
        { TEXT("elements"), EArcweaveAttributeDataType::Elements },
        { TEXT("components"), EArcweaveAttributeDataType::Components },
        { TEXT("global"), EArcweaveAttributeDataType::Global },
        { TEXT("boards"), EArcweaveAttributeDataType::Boards }
    };
    return AttributeDataTypeMap.Find(Type);
}
