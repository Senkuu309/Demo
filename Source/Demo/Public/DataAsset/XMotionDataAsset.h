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
	//��̫�涯��
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	UAnimMontage* MotionMontage;

	//���������ٶ�
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	float MontagePlayRate = 1.f;

	//������ʼ����
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	FName MontageStartingSection = FName("None");

	//������ʼλ��
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
	float MontageStartingPosition = 0.f;
};
