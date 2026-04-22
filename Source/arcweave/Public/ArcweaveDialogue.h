#pragma once

// Engine includes
#include "CoreMinimal.h"

// Generated include
#include "ArcweaveDialogue.generated.h"

//struct for dialogue
USTRUCT(BlueprintType)
struct FArcweaveDialogue
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString CharacterName = FString("");

	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	FString QuestionTitle = FString("");

    UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
    FString Content = FString("");

	UPROPERTY(BlueprintReadWrite, Category = "Arcweave")
	TArray<FString> Connections;

	FArcweaveDialogue()
		: CharacterName(FString(""))
		, QuestionTitle(FString(""))
		, Content(FString(""))
		, Connections(TArray<FString>())
	{}
};