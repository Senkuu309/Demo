// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XAICharacter.generated.h"

class UPawnSensingComponent;
class UXAttributeComponent;

UCLASS()
class DEMO_API AXAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXAICharacter();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UXAttributeComponent* AttributeComp;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);
};
