// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/XCharacter.h"
#include "XMagicCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AXMagicCharacter : public AXCharacter
{
	GENERATED_BODY()

protected:
	//ħ��
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	//ħ������
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;

public:
	AXMagicCharacter();

protected:

	virtual void PrimaryAttack();

	void TimerHandle_TimeElapsed();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
