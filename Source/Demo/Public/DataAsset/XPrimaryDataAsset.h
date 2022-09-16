// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "XPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEMO_API UXPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FPrimaryAssetType ItemType;

	virtual FPrimaryAssetId GetPrimaryAssetId()const override;
};
