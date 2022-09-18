// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "XComponentTypes.generated.h"

UENUM(BlueprintType)
enum class EAttributePropertyName : uint8
{
	EPropertyHP UMETA(DisplayName = "HP"),
	EPropertyExp UMETA(DisplayName = "Exp"),
	EPropertyLevel UMETA(DisplayName = "Level"),
};

USTRUCT(BlueprintType)
struct FAttributePropertyValue
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Min;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Current;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Max;
};

USTRUCT(BlueprintType)
struct FSkillInputStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FKey Key;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float InputTime = .5f;
};

UENUM(BlueprintType)
enum class EInputType : uint8
{
	EPropertyNone UMETA(DisplayName = "None"),
	EPropertyMBL UMETA(DisplayName = "MBL"),
	EPropertyMBR UMETA(DisplayName = "MBR"),
	EPropertyExtra UMETA(DisplayName = "Extra"),
	EPropertySMBL UMETA(DisplayName = "SMBL"),
	EPropertySMBR UMETA(DisplayName = "SMBR"),
};

USTRUCT(BlueprintType)
struct FAttackStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName SkillName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<EInputType, FName> NextCombo;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UAnimMontage* AttackAnim;
};

