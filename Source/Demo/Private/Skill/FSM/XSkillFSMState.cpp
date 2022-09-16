// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FSM/XSkillFSMState.h"

void UXSkillFSMState::Init_SkillFSMStateInfo(uint32 _KeyID, float _InputTime, int32 _StateID, int32 _MaxStateID)
{
	KeyID = _KeyID;
	InputTime = _InputTime;
	StateID = _StateID;
	MaxStateID = _MaxStateID;
}

void UXSkillFSMState::Init_SkillFSMStateInfo(FKey _KeyCode, float _InputTime, int32 _StateID, int32 _MaxStateID)
{
	KeyID = GetTypeHash(_KeyCode.GetFName());
	InputTime = _InputTime;
	StateID = _StateID;
	MaxStateID = _MaxStateID;
}
