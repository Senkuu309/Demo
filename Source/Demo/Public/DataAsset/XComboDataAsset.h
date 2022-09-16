// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/XPrimaryDataAsset.h"
#include "Engine/Texture2D.h"
#include "XMotionComboDataAsset.h"
#include "XComboDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXComboDataAsset : public UXPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UXMotionComboDataAsset* StartState;
};
