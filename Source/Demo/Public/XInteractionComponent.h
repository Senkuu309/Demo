// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XInteractionComponent.generated.h"

class UXWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_API UXInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PrimaryInteract();

protected:
	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocus);

	void FindBestInteractable();

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UXWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UXWorldUserWidget* DefaultWidgetInstance;

public:	
	UXInteractionComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};
