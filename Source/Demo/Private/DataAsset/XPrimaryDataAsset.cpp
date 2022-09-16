// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/XPrimaryDataAsset.h"

FPrimaryAssetId UXPrimaryDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}
