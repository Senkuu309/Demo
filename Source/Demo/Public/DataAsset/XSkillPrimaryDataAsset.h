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
	//技能名字
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	FName SkillName;

	//技能是否学习
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	bool Active = true;

	//技能优先级
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	int32 SkillPriority = 0;

	//技能输入
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	TArray<FSkillInputStruct> SkillInput;

	//技能所有者
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
	TSubclassOf<ACharacter> Owner;
};
