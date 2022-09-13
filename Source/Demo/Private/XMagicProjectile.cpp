// Fill out your copyright notice in the Description page of Project Settings.


#include "XMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/SparseDelegate.h"
#include "Component/XAttributeComponent.h"

// Sets default values
AXMagicProjectile::AXMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	SphereComp->OnComponentHit.AddDynamic(this, &AXMagicProjectile::OnHit);
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AXMagicProjectile::OnOverlap);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void AXMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(this->GetInstigator(), true);
}


// Called every frame
void AXMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXMagicProjectile::OnHit(UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello!"));
	if (GetInstigator() != OtherActor) {
		Destroy();
	}
}

void AXMagicProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && GetInstigator() != OtherActor)
	{
		UXAttributeComponent* AttritbuteComp = Cast<UXAttributeComponent>(OtherActor->GetComponentByClass(UXAttributeComponent::StaticClass()));
		if (AttritbuteComp)
		{
			AttritbuteComp->ApplyHealthChange(-20);
		}
		Destroy();
	}
}