// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Arcweave_BP.generated.h"

/**
 * 
 */
UCLASS()
class ARCWEAVE_API UArcweave_BP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Arcweave | Functions")
	static bool ArcweaveTest();
};
