// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XBTService_CheckHealth.h"
#include "Component/XAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UXBTService_CheckHealth::UXBTService_CheckHealth()
{
	LowHealthFraction = 0.3f;
}

void UXBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ensure(MyPawn))
	{
		UXAttributeComponent* AttributeComp = UXAttributeComponent::GetAttributes(MyPawn);
		if (ensure(AttributeComp))
		{
			bool bLowHealth = (AttributeComp->GetCurrentHealth() / AttributeComp->GetMaxHealth()) < LowHealthFraction;

			UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

			BlackBoardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
		}
	}
}
