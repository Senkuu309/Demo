// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/XMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Component/XAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/XCharacter.h"

// Sets default values
AXMagicProjectile::AXMagicProjectile()
{
	MoveComp->InitialSpeed = 1000.f;
	MoveComp->ProjectileGravityScale = 0.0f;

	SphereComp->OnComponentHit.AddDynamic(this, &AXMagicProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AXMagicProjectile::OnActorOverlap);
}

void AXMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ACharacter* Player = Cast<AXCharacter>(GetInstigator());
	if (OtherActor && Player != OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, EventInstigator, Player, DamageTypeClass);
		Explode();
	}
	else Explode();
}

void AXMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = Cast<AXCharacter>(GetInstigator());
	if (OtherActor && Player != OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, EventInstigator, Player, DamageTypeClass);
		Explode();
	}
	else Explode();
}