// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XMagicCharacter.h"
#include "Component/XAttributeComponent.h"
#include "Character/XCharacter.h"
#include "Component/XAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"

AXMagicCharacter::AXMagicCharacter()
{
	AttackAnimDelay = 0.2f;
	AttributeComp->SetDefaultHealth(1000, 1000);
}

//����ṥ��
void AXMagicCharacter::LightAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AXMagicCharacter::LightAttack_TimeElapsed, AttackAnimDelay);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void AXMagicCharacter::LightAttack_TimeElapsed()
{
	if (ensure(ProjectileClass)) {
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		//����ħ����λ�úͽǶ�
		FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

		//����ħ����Ч�ı���
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
}

void AXMagicCharacter::HeavyAttack()
{

}

void AXMagicCharacter::HeavyAttack_TimeElapsed()
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
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		//��������ħ����Ч�ı���
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		//������ײ��״��С
		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		//�����Լ�
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComp->GetComponentLocation();
		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 1000);

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();
		//��������ħ����λ�úͽǶ�
		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);

		GetWorld()->SpawnActor<AActor>(DashProjectile, SpawnTM, SpawnParams);
	}
}

void AXMagicCharacter::BeginPlay()
{
	Super::BeginPlay();
}
