﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArcweaveSettings.generated.h"



/**
 * 
 */
UCLASS(config = Game, DefaultConfig)
class ARCWEAVE_API UArcweaveSettings : public UObject
{
    GENERATED_BODY()

public:
    UArcweaveSettings();

    /*
     * Enable to receive the data from local JSON file instead of API.
     * The JSON file and resource files should be located in the Content/ArcweaveExport folder.
     */
    UPROPERTY(Config, EditAnywhere, Category = ArcweaveSettings)
    bool EnableReceiveMethodFromLocalJSON = false;

    /*
     * API token that you can find in your Arcweave account settings.
     */
    UPROPERTY(Config, EditAnywhere, meta = (EditCondition = "!EnableReceiveMethodFromLocalJSON"), Category = ArcweaveSettings)
    FString APIToken = FString("");

    /*
     * Project hash that we want to retrieve the information for. You can find it by looking at the URL of your project.
     */
    UPROPERTY(Config, EditAnywhere, meta = (EditCondition = "!EnableReceiveMethodFromLocalJSON"), Category = ArcweaveSettings)
    FString Hash = FString("");

    //override post init properties to check if the settings are valid
    virtual void PostInitProperties() override;
};
