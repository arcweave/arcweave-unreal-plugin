// File include
#include "ArcweaveUtils.h"

// Engine includes
#include "Containers/Map.h"


const TMap<FString, EArcweaveAttributeDataType> ArcweaveUtils::AttributeEnumDataTypeMap =
{
    { TEXT("string"),  EArcweaveAttributeDataType::String },
    { TEXT("StringRichText"), EArcweaveAttributeDataType::StringRichText },
    { TEXT("component-list"), EArcweaveAttributeDataType::ComponentList },
    { TEXT("asset-list"),   EArcweaveAttributeDataType::AssetList }
};


const EArcweaveAttributeDataType* ArcweaveUtils::TryGetEnumFromString(FString& Type)
{
    return AttributeEnumDataTypeMap.Find(Type);
}
