// Fill out your copyright notice in the Description page of Project Settings.


#include "XGameInstance.h"
#include "DataAsset/XAssetManager.h"

void UXGameInstance::Init()
{
	Super::Init();
	AutoLoadDataAssets();
}

void UXGameInstance::AutoLoadDataAssets()
{
	UXAssetManager& Manager = UXAssetManager::Get();
	for (auto& Type : AutoLoadTypes)
	{
		FPrimaryAssetType CurrentType = Type;
		TArray<FPrimaryAssetId> AssetIds;
		if (Manager.GetPrimaryAssetIdList(CurrentType, AssetIds))
		{
			Manager.LoadPrimaryAssets(AssetIds, TArray<FName>(), FStreamableDelegate(), 0);
		}
	}
}
