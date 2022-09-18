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
	//�������н��
	TArray<FHitResult> HitResults;
	
	//��������Actor
	TArray<AActor*> HitActors;

	//�¼�������
	AController* EventInstigator;

	TSubclassOf<UDamageType> DamageTypeClass;

	FVector HandSocketLocation;

	FRotator HandSocketRotation;

	//�������λ��
	FVector SocketLocation1;

	//�������λ��
	FVector SocketLocation2;

	//�������λ��
	FVector SocketLocation3;

	//��ǰ���
	class AXCharacter* Player;

	//�������
	class USkeletalMeshComponent* Weapon;

	//����Ŀ��
	TArray<AActor*> ActorsToIgnore;

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;

	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;

	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
