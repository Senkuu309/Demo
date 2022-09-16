// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "XAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static const FPrimaryAssetType SkillType;
	static const FPrimaryAssetType MotionType;
	static const FPrimaryAssetType ComboType;

	static UXAssetManager& Get();
	
};
