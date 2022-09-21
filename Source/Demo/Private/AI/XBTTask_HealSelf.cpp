// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XBTTask_HealSelf.h"
#include "Component/XAttributeComponent.h"
#include "AIController.h"

EBTNodeResult::Type UXBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* MyPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	UXAttributeComponent* AttributeComp = UXAttributeComponent::GetAttributes(MyPawn);
	if (ensure(AttributeComp))
	{
		AttributeComp->ApplyHealthChange(MyPawn, AttributeComp->GetMaxHealth());
	}
	return EBTNodeResult::Succeeded;
}
