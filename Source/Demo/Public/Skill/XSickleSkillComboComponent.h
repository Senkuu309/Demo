// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "XSickleSkillComboComponent.generated.h"

class UXSkillFSMState;
class UXSkillFSM;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DEMO_API UXSickleSkillComboComponent : public UActorComponent
{
	GENERATED_BODY()

	UXSkillFSM* SickleSkillFSM;

public:	
	// Sets default values for this component's properties
	UXSickleSkillComboComponent();

	void AttackInput(FKey KeyCode, UXSkillFSMState* SkillState);
};
