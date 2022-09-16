// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputCoreTypes.h"
#include "XSkillFSMState.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API UXSkillFSMState : public UObject
{
	GENERATED_BODY()

public:
	//Key ID
	uint32 KeyID;

	float InputTime;

	//ID
	int32 StateID;

	//max ID
	int32 MaxStateID;

	void Init_SkillFSMStateInfo(uint32 _KeyID, float _InputTime, int32 _StateID, int32 _MaxStateID);

	void Init_SkillFSMStateInfo(FKey _KeyCode, float _InputTime, int32 _StateID, int32 _MaxStateID);
	
};
