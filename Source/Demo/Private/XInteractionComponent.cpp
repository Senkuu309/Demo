// Fill out your copyright notice in the Description page of Project Settings.


#include "XInteractionComponent.h"
#include "XGameplayInterface.h"
#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.DebugDrawInteraction"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

UXInteractionComponent::UXInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UXInteractionComponent::PrimaryInteract()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * 1000);

	FHitResult Hit;

	bool bBlockngHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	AActor* HitActor = Hit.GetActor();
	if (HitActor)
	{
		if (HitActor->Implements<UXGameplayInterface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			IXGameplayInterface::Execute_Interact(HitActor, MyPawn);
		}
	}
	if (bDebugDraw)
	{
		FColor LinearColors = bBlockngHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), EyeLocation, End, LinearColors, false, 2.0f, 0, 2.0f);
	}
	
}

