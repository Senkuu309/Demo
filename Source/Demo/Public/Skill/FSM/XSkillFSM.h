// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill/FSM/XSkillFSMState.h"
#include "TimerManager.h"
#include "XSkillFSM.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXSkillFSM : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TMap<int32, UXSkillFSMState*> SkillFSMStateMap;

	UPROPERTY()
	UXSkillFSMState* CurrentState;

	UPROPERTY()
	bool OKay = false;

public:
	FTimerHandle ResetTimer;

	//ππΩ®◊¥Ã¨
	bool AddState(UXSkillFSMState* StateToAdd);
	
	bool ChangeState(int32 _StateID);
	
	//÷ÿ÷√
	void SetTimer(float TimeDelay);

	void Reset();

	void Check(int32 InputHash);

};
