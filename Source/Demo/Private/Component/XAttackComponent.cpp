// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/XAttackComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UXAttackComponent::UXAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void UXAttackComponent::PlayAttackMontage(AActor* Instigator)
{
	//isAttacking = true;
	ACharacter* Player = Cast<ACharacter>(Instigator);
	
	Player->PlayAnimMontage(AttackAnim);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, NextSkill.SkillName.ToString());
}

void UXAttackComponent::SkillInput(AActor* Instigator, EInputType InputType)
{
	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		ServerPlayAnimMontage(Instigator, InputType);
	}
}

void UXAttackComponent::ComboEnd_Implementation()
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

void UXAttackComponent::ServerPlayAnimMontage_Implementation(AActor* Instigator, EInputType InputType)
{
	if (!isAttacking)
	{
		FName* Name = SkillList.Find(InputType);
		if (Name)
		{
			isAttacking = true;
			NextSkill = *AttackSkillData.Find(*Name);

			AttackAnim = NextSkill.AttackAnim;
			PlayAttackMontage(Instigator);
			bIsAttack = !bIsAttack;
			CurrentSkill = NextSkill;
			InputBuffer = EInputType::EPropertyNone;

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
				NextSkill = *AttackSkillData.Find(*SkillName);

				AttackAnim = NextSkill.AttackAnim;
				PlayAttackMontage(Instigator);
				bIsAttack = !bIsAttack;
				CurrentSkill = NextSkill;
				InputBuffer = EInputType::EPropertyNone;
			}
			//else ComboEnd();
		}
		else {
			InputBuffer = InputType;
		}
	}
}

void UXAttackComponent::OnRep_bIsAttack()
{
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,  *GetNameSafe(AttackAnim));
	if (Player)
	{
		Player->PlayAnimMontage(AttackAnim);
	}
}


void UXAttackComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXAttackComponent, isAttacking);
	DOREPLIFETIME(UXAttackComponent, bIsAttack);
	DOREPLIFETIME(UXAttackComponent, AttackAnim);
	DOREPLIFETIME(UXAttackComponent, SaveAttack);
}