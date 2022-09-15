// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/XMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Component/XAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AXMagicProjectile::AXMagicProjectile()
{
	Damage = -20.0f;

	MoveComp->InitialSpeed = 1000.f;
	MoveComp->ProjectileGravityScale = 0.0f;

	SphereComp->OnComponentHit.AddDynamic(this, &AXMagicProjectile::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AXMagicProjectile::OnActorOverlap);
}

void AXMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	AXProjectileBase::OnActorHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);
}

void AXMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && GetInstigator() != OtherActor)
	{
		UXAttributeComponent* AttritbuteComp = Cast<UXAttributeComponent>(OtherActor->GetComponentByClass(UXAttributeComponent::StaticClass()));
		if (AttritbuteComp && Damage < 0.0f)
		{
			AttritbuteComp->ApplyHealthChange(Damage);
			Explode();
		}
	}
}