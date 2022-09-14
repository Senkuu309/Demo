// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/XMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Component/XAttributeComponent.h"

// Sets default values
AXMagicProjectile::AXMagicProjectile()
{
	SphereComp->OnComponentHit.AddDynamic(this, &AXMagicProjectile::OnActorHit);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AXMagicProjectile::OnActorOverlap);

	MoveComp->InitialSpeed = 1000.0f;
	MoveComp->ProjectileGravityScale = 0.0f;

	Damage = -20.0f;
}

void AXMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AXProjectileBase::OnActorHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}

void AXMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AXProjectileBase::OnActorOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
