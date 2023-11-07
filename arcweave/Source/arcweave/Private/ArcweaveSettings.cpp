// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcweaveSettings.h"

UArcweaveSettings::UArcweaveSettings()
{
}

void UArcweaveSettings::PostInitProperties()
{
	UObject::PostInitProperties();
	TryUpdateDefaultConfigFile(TEXT(""), false);
}
