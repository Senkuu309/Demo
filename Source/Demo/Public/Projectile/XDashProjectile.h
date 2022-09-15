// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile/XProjectileBase.h"
#include "XDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AXDashProjectile : public AXProjectileBase
{
	GENERATED_BODY()

public:
	AXDashProjectile();

	void BeginPlay();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TelePortDelay;

	FTimerHandle TimerHandle_DelayedDetonate;

	virtual void Explode_Implementation() override;

	void TeleportInstigator();

	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
