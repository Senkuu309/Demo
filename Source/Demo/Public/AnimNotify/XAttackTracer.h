// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "XAttackTracer.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXAttackTracer : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	//武器命中结果
	TArray<FHitResult> HitResults;
	
	//武器命中Actor
	TArray<AActor*> HitActors;

	//事件发起者
	AController* EventInstigator;

	TSubclassOf<UDamageType> DamageTypeClass;

	FVector HandSocketLocation;

	FRotator HandSocketRotation;

	//武器插槽位置
	FVector SocketLocation1;

	//武器插槽位置
	FVector SocketLocation2;

	//武器插槽位置
	FVector SocketLocation3;

	//当前玩家
	class AXCharacter* Player;

	//玩家武器
	class USkeletalMeshComponent* Weapon;

	//忽略目标
	TArray<AActor*> ActorsToIgnore;

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
