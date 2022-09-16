// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/XPrimaryDataAsset.h"
#include "Component/XAttributeTypes.h"
#include "XSkillPrimaryDataAsset.generated.h"

/**
 * 
 */
class ACharacter;

UCLASS()
class DEMO_API UXSkillPrimaryDataAsset : public UXPrimaryDataAsset
{
	GENERATED_BODY()

public:
	//��������
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	FName SkillName;

	//�����Ƿ�ѧϰ
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	bool Active = true;

	//�������ȼ�
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	int32 SkillPriority = 0;

	//��������
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	TArray<FSkillInputStruct> SkillInput;

	//����������
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	TSubclassOf<ACharacter> Owner;
};
