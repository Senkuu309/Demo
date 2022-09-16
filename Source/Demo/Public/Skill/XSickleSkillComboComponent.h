// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FSM/XSkillFSM.h"
#include "XSickleSkillComboComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class DEMO_API UXSickleSkillComboComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UXSickleSkillComboComponent();

	void AttackInput(int32 KeyID, UXSkillFSMState* CurrentState, TMap<int32, UXSkillFSMState*> SkillFSMStateMap, bool OKay);
};
