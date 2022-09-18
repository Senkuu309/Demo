// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XAttackComponent.h"

// Sets default values for this component's properties
UXAttackComponent::UXAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UXAttackComponent::SkillInput(EInputType InputType)
{
	if (!isAttacking)
	{
		FName* Name = SkillList.Find(InputType);
		if (Name) 
		{
			isAttacking = true;
			OnAttacking.Broadcast(nullptr, this, *AttackSkillData.Find(*Name));
		}
		else
		{
			ComboEnd();
		}
	}
	else
	{
		if (SaveAttack)
		{
			FName* SkillName = CurrentSkill.NextCombo.Find(InputType);
			if (SkillName)
			{
				OnAttacking.Broadcast(nullptr, this, *AttackSkillData.Find(*SkillName));
			}
			//else ComboEnd();
		}
		else {
			InputBuffer = InputType;
		}
	}
}

void UXAttackComponent::ComboEnd()
{
	isAttacking = false;
	SaveAttack = false;
	InputBuffer = EInputType::EPropertyNone;
	CurrentSkill.AttackAnim = NULL;
}

void UXAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (InputBuffer != EInputType::EPropertyNone) {
		SkillInput(InputBuffer);
	}
}
