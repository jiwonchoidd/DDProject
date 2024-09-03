#include "DDState.h"
#include "Templates/SubclassOf.h"

void UDDState::Create()
{
	mapState.Reset();
}

void UDDState::Destroy()
{
	for (TTuple<uint8, UDDBaseState*>& State : mapState)
	{
		if (!IsValid(State.Value))
			continue;
		
		State.Value->RemoveFromRoot();
		State.Value->Finalize();
		State.Value = nullptr;
	}
	mapState.Reset();
}

void UDDState::Tick(float _fDeltaTime)
{
	if (ChangeStateID == -1)
		return;

	if (UDDBaseState* pCurrentState = GetStatePtr(CurrentStateID))
	{
		pCurrentState->OnTickState(_fDeltaTime);
	}
}

void UDDState::SetState(uint8 _uiIndex, bool _bInstant)
{
	SetState_Internal(_uiIndex);
}

UDDBaseState* UDDState::GetStatePtr(uint8 _nIndex)
{
	if (mapState.Contains(_nIndex))
	{
		UDDBaseState* pStateBase = *mapState.Find(_nIndex);
		if (IsValid(pStateBase))
		{
			return pStateBase;
		}
	}
	return nullptr;
}

UDDBaseState* UDDState::GetCurrentStatePtr()
{
	return GetStatePtr(CurrentStateID);
}

UDDBaseState* UDDState::GetPreviousStatePtr()
{
	return GetStatePtr(PreviousStateID);
}

void UDDState::SetState_Internal(uint8 _nIndex)
{
	ChangeStateID = -1;
	PreviousStateID = CurrentStateID;

	if (UDDBaseState* pCurrentState = GetStatePtr(CurrentStateID))
	{
		pCurrentState->OnExitState();
	}

	ChangeStateID = _nIndex;

	if (UDDBaseState* pNextState = GetStatePtr(ChangeStateID))
	{
		pNextState->OnBeginState();
	}

	CurrentStateID = ChangeStateID;
}

//-------------------------------------------------------------------------------------------

