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
	AttributeComp->SetDefaultHealth(20, 20);
}

FTransform AXMagicCharacter::SpawnTM(FName ScoketLocation)
{
	FVector HandLocation = GetMesh()->GetSocketLocation(ScoketLocation);

	//设置碰撞形状大小
	FCollisionShape Shape;
	Shape.SetSphere(0.1f);

	//忽略自己
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	ObjParams.AddObjectTypesToQuery(ECC_Vehicle);
	ObjParams.AddObjectTypesToQuery(ECC_Destructible);

	FVector TraceStart = CameraComp->GetComponentLocation();
	FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 10000);

	FHitResult Hit;
	if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
	{
		TraceEnd = Hit.ImpactPoint;
	}

	FRotator ProjRotation = FRotationMatrix::MakeFromXZ(TraceEnd - HandLocation, TraceEnd - HandLocation).Rotator();

	//返回闪现魔法的位置和角度
	return FTransform(ProjRotation, HandLocation);
}



//左键轻攻击
void AXMagicCharacter::LightAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AXMagicCharacter::LightAttack_TimeElapsed, AttackAnimDelay);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void AXMagicCharacter::LightAttack_TimeElapsed()
{
	if (ensure(ProjectileClass)) 
	{
		//设置魔法特效的变量
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM("Muzzle_01"), SpawnParams);
	}
}

void AXMagicCharacter::HeavyAttack()
{

}

void AXMagicCharacter::HeavyAttack_TimeElapsed()
{

}

//额外技能 按键E
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
		//设置闪现魔法特效的变量
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

