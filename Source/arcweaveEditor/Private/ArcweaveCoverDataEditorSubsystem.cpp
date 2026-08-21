#include "ArcweaveCoverDataEditorSubsystem.h"

#include "ArcweaveCoverDataAsset.h"
#include "ArcweaveCoverDataAssetInfo.h"
#include "ArcweaveCoverData.h"

#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/Texture2D.h"
#include "Misc/PackageName.h"
#include "Modules/ModuleManager.h"
#include "UObject/Package.h"
#include "UObject/SavePackage.h"
#include "UObject/SoftObjectPath.h"

bool UArcweaveCoverDataEditorSubsystem::ParseArcweaveCoverDataFromJson(const FString& JsonString)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	const FSoftObjectPath ExistingPath(FString(CoverAssetPackagePath) + TEXT(".DA_CoverIdMap"));
	if (AssetRegistryModule.Get().GetAssetByObjectPath(ExistingPath).IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("CoverData asset already exists, skipping creation"));
		return true;
	}

	TSharedPtr<FJsonObject> RootObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(Reader, RootObject) || !RootObject.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON string"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* Entries = nullptr;
	if (!RootObject->TryGetArrayField(TEXT("CoverMap"), Entries))
	{
		UE_LOG(LogTemp, Error, TEXT("CoverMap field not found in JSON"));
		return false;
	}

	UPackage* Package = CreatePackage(*CoverAssetPackagePath);
	Package->FullyLoad();

	UArcweaveCoverDataAsset* NewAsset = NewObject<UArcweaveCoverDataAsset>(
		Package, FName(TEXT("DA_CoverIdMap")), RF_Public | RF_Standalone);

	for (const TSharedPtr<FJsonValue>& EntryValue : *Entries)
	{
		const TSharedPtr<FJsonObject> Entry = EntryValue->AsObject();
		if (!Entry.IsValid())
		{
			continue;
		}

		FString IdString;
		FString TextureName;
		FString FileString;
		FString TypeString;
		Entry->TryGetStringField(TEXT("id"), IdString);
		Entry->TryGetStringField(TEXT("texture"), TextureName);
		Entry->TryGetStringField(TEXT("file"), FileString);
		Entry->TryGetStringField(TEXT("type"), TypeString);

		FGuid Guid;
		if (!FGuid::Parse(IdString, Guid))
		{
			continue;
		}

		const FString ObjectPath = FString::Printf(ImageSourcesPackagePath, *TextureName, *TextureName);
        TSoftObjectPtr<UTexture2D> TexturePtr = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(ObjectPath));

		NewAsset->CoverDataMap.Add(FCString::Atoi(*IdString), TexturePtr);
	}

	FAssetRegistryModule::AssetCreated(NewAsset);
	Package->MarkPackageDirty();

	const FString FilePath = FPackageName::LongPackageNameToFilename(
		CoverAssetPackagePath, FPackageName::GetAssetPackageExtension());

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	UPackage::SavePackage(Package, NewAsset, *FilePath, SaveArgs);

	UE_LOG(LogTemp, Log, TEXT("CoverData asset created and saved in %s"), *FilePath);
	return true;
}


bool ParseArcweaveCoverDataFromDefaultJson()
{
    return ParseArcweaveCoverDataFromJson("Test");
}