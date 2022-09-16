// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/XPrimaryDataAsset.h"
#include "XMotionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXMotionDataAsset : public UXPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//蒙太奇动画
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	UAnimMontage* MotionMontage;

	//动画播放速度
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	float MontagePlayRate = 1.f;

	//动画开始部分
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	FName MontageStartingSection = FName("None");

	//动画开始位置
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	float MontageStartingPosition = 0.f;
};
