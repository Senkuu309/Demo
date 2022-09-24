// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XActionComponent.h"
#include "Component/XAction.h"



UXActionComponent::UXActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UXActionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UXActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UXActionComponent::AddAction(TSubclassOf<UXAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}
	UXAction* NewAction =  NewObject<UXAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);
	}

}

bool UXActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UXAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UXActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UXAction * Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}