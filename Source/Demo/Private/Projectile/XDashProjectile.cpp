// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/XDashProjectile.h"
#include "Projectile/XProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Component/XAttributeComponent.h"

AXDashProjectile::AXDashProjectile()
{
	TelePortDelay = 0.1f;

	MoveComp->InitialSpeed = 3000.f;
	MoveComp->ProjectileGravityScale = 0.0f;

	Damage = 0.0f;
}

void AXDashProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && GetInstigator() != OtherActor)
	{
		Explode();
	}
	
}

void AXDashProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && GetInstigator() != OtherActor)
	{
		Explode();
	}
}


void AXDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(this->GetInstigator(), true);

	SphereComp->OnComponentHit.AddDynamic(this, &AXDashProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AXDashProjectile::OnActorOverlap);
	
	//GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &AXDashProjectile::Explode, DetonateDelay);
}

void AXDashProjectile::Explode_Implementation()
{
	
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AXDashProjectile::TeleportInstigator, TelePortDelay);
}


void AXDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}


