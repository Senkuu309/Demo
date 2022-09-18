// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/XSickleCharacter.h"
#include "Component/XAttributeComponent.h"
#include "Component/XAttackComponent.h"
#include "Character/XCharacter.h"

AXSickleCharacter::AXSickleCharacter()
{
	AttributeComp->SetDefaultHealth(1);
	WeaponComp->SetupAttachment(GetMesh(), TEXT("hand_rSocket"));

	WeaponLocation1 = GetMesh()->GetSocketLocation("hand_rSocket");
	WeaponLocation2 = WeaponComp->GetSocketLocation("Mid");
	WeaponLocation3 = WeaponComp->GetSocketLocation("End");
}
