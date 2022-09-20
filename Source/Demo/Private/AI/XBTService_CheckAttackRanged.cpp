// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XBTService_CheckAttackRanged.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Character/XCharacter.h"
#include "Kismet/GameplayStatics.h"

void UXBTService_CheckAttackRanged::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboardComp))
	{
		TArray<AActor*> AllActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(),CharacterClass, AllActors);
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = DistanceTo < 1000.f;
					
					bool isVisible = false;
					if (bWithinRange)
					{
						isVisible = MyController->LineOfSightTo(TargetActor);
					}
					BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithinRange && isVisible));
				}
			}
		}
	}
}
