// Fill out your copyright notice in the Description page of Project Settings.


#include "Arcweave_BP.h"
#include "Arcweave.h"

bool UArcweave_BP::ArcweaveTest()
{
	FarcweaveModule& ArcweaveModule = FModuleManager::LoadModuleChecked<FarcweaveModule>("Arcweave");
	return ArcweaveModule.TestJsonFile();
}
