// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/XMotionDataAsset.h"
#include "XMotionComboDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXMotionComboDataAsset : public UXMotionDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
	UXMotionDataAsset* NextCombo;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
	UXMotionDataAsset* BrachCombo;
};
