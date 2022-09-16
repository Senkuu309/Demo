// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/FSM/XSkillFSM.h"
#include "Skill/FSM/XSkillFSMState.h"

bool UXSkillFSM::AddState(UXSkillFSMState* StateToAdd)
{
	if (StateToAdd && !SkillFSMStateMap.Contains(StateToAdd->StateID))
	{
		SkillFSMStateMap.Add(StateToAdd->StateID, StateToAdd);
		return true;
	}
	return false;
}

bool UXSkillFSM::ChangeState(int32 _StateID)
{
	if (SkillFSMStateMap.Contains(_StateID))
	{
		UXSkillFSMState* _State = SkillFSMStateMap[_StateID];
		if (_State)
		{
			return true;
		}
	}
	return false;
}

void UXSkillFSM::SetTimer(float TimeDelay)
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &UXSkillFSM::Reset, (TimeDelay == 0) ? 0.0001f : TimeDelay, false, -1.f);
	}
}

void UXSkillFSM::Reset()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ResetTimer);
		ChangeState(0);
	}
}

void UXSkillFSM::Check(int32 InputHash)
{
	if (CurrentState == nullptr && SkillFSMStateMap[0]) Reset();
	if (CurrentState && InputHash == CurrentState->KeyID)
	{
		if (CurrentState->StateID == CurrentState->MaxStateID)
		{
			OKay = true;
			ChangeState(0);
			return;
		}
		else ChangeState(CurrentState->StateID + 1);
	}
	else Reset();
}
