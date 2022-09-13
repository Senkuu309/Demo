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

	float AttackAnimDelay;

protected:
	//魔法
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	//闪现魔法
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> DashProjectileClass;

	//魔法动作
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	
	FTimerHandle TimerHandle_Dash;

public:
	AXMagicCharacter();

protected:

	//左键攻击
	virtual void PrimaryAttack() override;
	void TimerHandle_TimeElapsed();

	//额外技能：魔法闪现
	virtual void ExtraSkill() override;

	//闪现
	void Dash();
	void Dash_TimeElapsed();
	void SpawnProjectile(TSubclassOf<AActor> DashProjectile);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
