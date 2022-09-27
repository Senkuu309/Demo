// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/XAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AXAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(BehaviorTree))
	{
		RunBehaviorTree(BehaviorTree);
	}
	
	/*APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (MyPawn)
	{

		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}*/
}
