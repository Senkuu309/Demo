// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XProjectileBase.h"
#include "XMagicProjectile.generated.h"

UCLASS()
class DEMO_API AXMagicProjectile : public AXProjectileBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXMagicProjectile();

protected:

	virtual void OnActorHit(class UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnActorOverlap(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};