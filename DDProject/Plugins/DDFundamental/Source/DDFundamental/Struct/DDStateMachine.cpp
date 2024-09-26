#include "DDStateMachine.h"
#include "Templates/SubclassOf.h"

void UDDStateMachine::Create()
{
	mapState.Reset();
}

void UDDStateMachine::Destroy()
{
	for (TTuple<uint8, UDDStateBase*>& State : mapState)
	{
		if (!IsValid(State.Value))
			continue;
		
		State.Value->RemoveFromRoot();
		State.Value->Finalize();
		State.Value = nullptr;
	}
	mapState.Reset();
}

void UDDStateMachine::Tick(float _fDeltaTime)
{
	if (ChangeStateID == -1)
		return;

	if (UDDStateBase* pCurrentState = GetStatePtr(CurrentStateID))
	{
		pCurrentState->OnTickState(_fDeltaTime);
	}
}

void UDDStateMachine::AddState(uint8 _uiIndex, TSubclassOf<UDDStateBase> _SceneType, UObject* _pOuter)
{
	if (mapState.Contains(_uiIndex))
		return;

	UObject* ParentObject = IsValid(_pOuter) ? _pOuter : nullptr;
	if (UDDStateBase* StateBase = NewObject<UDDStateBase>(ParentObject, _SceneType))
	{
		StateBase->Initialize(_uiIndex);
		mapState.Add(_uiIndex, StateBase);
	}
}

void UDDStateMachine::SetState(uint8 _uiIndex, bool _bInstant)
{
	SetState_Internal(_uiIndex);
}

UDDStateBase* UDDStateMachine::GetStatePtr(uint8 _nIndex)
{
	if (mapState.Contains(_nIndex))
	{
		UDDStateBase* pStateBase = *mapState.Find(_nIndex);
		if (IsValid(pStateBase))
		{
			return pStateBase;
		}
	}
	return nullptr;
}

UDDStateBase* UDDStateMachine::GetCurrentStatePtr()
{
	return GetStatePtr(CurrentStateID);
}

UDDStateBase* UDDStateMachine::GetPreviousStatePtr()
{
	return GetStatePtr(PreviousStateID);
}

void UDDStateMachine::SetState_Internal(uint8 _nIndex)
{
	ChangeStateID = -1;
	PreviousStateID = CurrentStateID;

	if (UDDStateBase* pCurrentState = GetStatePtr(CurrentStateID))
	{
		pCurrentState->OnExitState();
	}

	ChangeStateID = _nIndex;

	if (UDDStateBase* pNextState = GetStatePtr(ChangeStateID))
	{
		pNextState->OnBeginState();
	}

	CurrentStateID = ChangeStateID;
}

//-------------------------------------------------------------------------------------------

