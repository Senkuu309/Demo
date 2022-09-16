// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/XSickleSkillComboComponent.h"
#include "Skill/FSM/XSkillFSM.h"
#include "Skill/FSM/XSkillFSMState.h"

// Sets default values for this component's properties
UXSickleSkillComboComponent::UXSickleSkillComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UXSickleSkillComboComponent::AttackInput(FKey KeyCode, UXSkillFSMState* SkillState)
{

}
