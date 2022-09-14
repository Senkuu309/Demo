// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "XAIController.generated.h"

/**
 * 
 */
class UBehaviorTree;
UCLASS()
class DEMO_API AXAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	void BeginPlay();

};
