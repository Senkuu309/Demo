// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatoActor, UXAttributeComponent*, OwningComp, float, maxHealth, float, newHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMO_API UXAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

	float MaxHealth;

	float CurrentHealth;
	
public:	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	// Sets default values for this component's properties
	UXAttributeComponent();

	UFUNCTION()
	bool SetDefaultHealth(float MaxHealth, float CurrentHealth);

	//血量变化组件
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta);

};
