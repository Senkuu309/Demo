// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XAttackComponent.h"
#include "GameFramework/Character.h"

UXAttackComponent::UXAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UXAttackComponent::PlayAttackMontage(AActor* Instigator, FAttackStruct NextSkill)
{
	isAttacking = true;
	ACharacter* Player = Cast<ACharacter>(Instigator);
	Player->PlayAnimMontage(NextSkill.AttackAnim);
	CurrentSkill = NextSkill;
	InputBuffer = EInputType::EPropertyNone;
}


void UXAttackComponent::SkillInput(AActor* Instigator, EInputType InputType)
{
	if (!isAttacking)
	{
		FName* Name = SkillList.Find(InputType);
		if (Name) 
		{
			isAttacking = true;
			PlayAttackMontage(Instigator, *AttackSkillData.Find(*Name));
			//OnAttacking.Broadcast(nullptr, this, *AttackSkillData.Find(*Name));
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
				PlayAttackMontage(Instigator, *AttackSkillData.Find(*SkillName));
				//OnAttacking.Broadcast(nullptr, this, *AttackSkillData.Find(*SkillName));
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
		SkillInput(GetOwner(), InputBuffer);
	}
}
