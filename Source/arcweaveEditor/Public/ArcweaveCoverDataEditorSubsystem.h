#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"

#include "ArcweaveCoverDataEditorSubsystem.generated.h"

/**
 * This class has the purpose of extrapolating information from the json downloaded from web or existing inside the ArcweaveExport folder
 * and associate the ids with the correct images inside a UDataAsset.
 */
UCLASS()
class ARCWEAVEEDITOR_API UArcweaveCoverDataEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arcweave| Cover Data Subsystem")
	bool bParseArcweaveCoverDataFromJson = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arcweave| Cover Data Subsystem", meta = (Tooltip = "The package path where the downloaded images are"))
	FString ImageSourcesPackagePath = TEXT("/Game/Arcweave/Content/ArcweaveExport/assets");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arcweave| Cover Data Subsystem", meta = (Tooltip = "The package path where the data asset will be created"))
    FString CoverAssetPackagePath = TEXT("/Game/Arcweave/Content/ArcweaveExport/assets");

	UFUNCTION(BlueprintCallable, Category = "Arcweave| Cover Data Subsystem")
	bool ParseArcweaveCoverDataFromJson(const FString& JsonString);

    UFUNCTION(BlueprintCallable)
    bool ParseArcweaveCoverDataFromDefaultJson();
};
