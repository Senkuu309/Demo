// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XMagicCharacter.h"
#include "Component/XAttributeComponent.h"

AXMagicCharacter::AXMagicCharacter()
{
	AttributeComp->SetDefaultHealth(1000);
}

void AXMagicCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AXMagicCharacter::TimerHandle_TimeElapsed, 0.2f);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void AXMagicCharacter::TimerHandle_TimeElapsed()
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
