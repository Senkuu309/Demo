// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "XTaskNode_RangedAttack.generated.h"

class AXAICharacter;

/**
 * 
 */
UCLASS()
class DEMO_API UXTaskNode_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	AXAICharacter* IgnoreSelf; 

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
