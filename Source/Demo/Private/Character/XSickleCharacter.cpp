// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XSickleCharacter.h"
#include "Component/XAttributeComponent.h"
#include "Component/XAttackComponent.h"

AXSickleCharacter::AXSickleCharacter()
{
	AttributeComp->SetDefaultHealth(100);
}
//�������
void AXSickleCharacter::MBLAttack()
{
	AttackComp->SkillInput(EInputType::EPropertyMBL);
		
}

//�Ҽ�����
void AXSickleCharacter::MBRAttack()
{
	AttackComp->SkillInput(EInputType::EPropertyMBR);
}
