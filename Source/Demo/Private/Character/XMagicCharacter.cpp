// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XMagicCharacter.h"
#include "Component/XAttributeComponent.h"
#include "Character/XCharacter.h"
#include "Component/XAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Blueprint/UserWidget.h"

AXMagicCharacter::AXMagicCharacter()
{
	AttackAnimDelay = 0.2f;
	AttributeComp->SetDefaultHealth(100);
}

FTransform AXMagicCharacter::SpawnTM(FName ScoketLocation)
{
	FVector HandLocation = GetMesh()->GetSocketLocation(ScoketLocation);

	//������ײ��״��С
	FCollisionShape Shape;
	Shape.SetSphere(0.1f);

	//�����Լ�
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);

	FVector TraceStart = CameraComp->GetComponentLocation();
	FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 10000);

	FHitResult Hit;
	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
	{
		TraceEnd = Hit.ImpactPoint;
	}

	FRotator ProjRotation = FRotationMatrix::MakeFromXZ(TraceEnd - HandLocation, TraceEnd - HandLocation).Rotator();

	//����ħ����λ�úͽǶ�
	return FTransform(ProjRotation, HandLocation);
}

//����ṥ��
void AXMagicCharacter::MBLAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AXMagicCharacter::MBLAttack_TimeElapsed, AttackAnimDelay);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void AXMagicCharacter::MBLAttack_TimeElapsed()
{
	if (ensure(ProjectileClass)) 
	{
		//����ħ����Ч�ı���
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM("Muzzle_01"), SpawnParams);
	}
}

void AXMagicCharacter::MBRAttack()
{
}

void AXMagicCharacter::MBRAttack_TimeElapsed()
{
}

//���⼼�� ����E
void AXMagicCharacter::ExtraSkill()
{
	Dash();
}

void AXMagicCharacter::Dash()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Dash, this, &AXMagicCharacter::Dash_TimeElapsed, AttackAnimDelay);
}

void AXMagicCharacter::Dash_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void AXMagicCharacter::SpawnProjectile(TSubclassOf<AActor> DashProjectile)
{
	if (ensure(DashProjectile))
	{
		//��������ħ����Ч�ı���
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(DashProjectile, SpawnTM("Muzzle_01"), SpawnParams);
	}
}

void AXMagicCharacter::BeginPlay()
{
	Super::BeginPlay();
}