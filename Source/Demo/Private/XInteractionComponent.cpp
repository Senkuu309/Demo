// Fill out your copyright notice in the Description page of Project Settings.


#include "XInteractionComponent.h"
#include "XGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "UserWidget/XWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.DebugDrawInteraction"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);

UXInteractionComponent::UXInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceRadius = 30.f;
	TraceDistance = 500.f;
	CollisionChannel = ECC_WorldDynamic;
}

void UXInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
}


void UXInteractionComponent::FindBestInteractable()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	TArray<FHitResult> Hits;

	bool bBlockngHit = GetWorld()->LineTraceMultiByObjectType(Hits, EyeLocation, End, ObjectQueryParams);
	
	FColor LinearColor = bBlockngHit ? FColor::Green : FColor::Red;
	
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	FocusedActor = nullptr;

	for (FHitResult Hit : Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LinearColor, false, 2.0f);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UXGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<UXWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}
	
	if (bDebugDraw)
	{
		
		DrawDebugLine(GetWorld(), EyeLocation, End, LinearColor, false, 2.0f, 0, 2.0f);
	}
}

void UXInteractionComponent::PrimaryInteract()
{
	ServerInteract(FocusedActor);
}


void UXInteractionComponent::ServerInteract_Implementation(AActor* InFocus)
{
	if (InFocus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "No Focus Actor on Interact.");
		return;
	}

	APawn* MyPawn = Cast<APawn>(GetOwner());
	IXGameplayInterface::Execute_Interact(InFocus, MyPawn);
}

