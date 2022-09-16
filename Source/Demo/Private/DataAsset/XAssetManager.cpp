// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/XAssetManager.h"

const FPrimaryAssetType UXAssetManager::SkillType = TEXT("SkillType");
const FPrimaryAssetType UXAssetManager::MotionType = TEXT("MotionType");
const FPrimaryAssetType UXAssetManager::ComboType = TEXT("ComboType");

UXAssetManager& UXAssetManager::Get()
{
	UXAssetManager* Singleton = Cast<UXAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		return *NewObject<UXAssetManager>();
	}
}