// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/XProjectileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Component/XAttributeComponent.h"
#include "AI/XAICharacter.h"
#include "EngineUtils.h"

// Sets default values
AXProjectileBase::AXProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->InitialSpeed = 8000.f;
	MoveComp->ProjectileGravityScale = 0.0f;
}

void AXProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AXProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Explode();
}

void AXProjectileBase::Explode_Implementation()
{
	
	if (ensure(!IsPendingKill()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	
		Destroy();
	}
} 

void AXProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AXProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(this->GetInstigator(), true);
	for (TActorIterator<AXAICharacter> It(GetWorld()); It; ++It)
	{
		AXAICharacter* Itself = *It;
		SphereComp->IgnoreActorWhenMoving(Itself, true);
	}
}


