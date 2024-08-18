#include "DDState.h"
#include "Templates/SubclassOf.h"

void UDDState::Create()
{
	mapState.Reset();
}

void UDDState::Destroy()
{
	for (TTuple<uint8, UDDStateBase*> State : mapState)
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

	if (UDDStateBase* pCurrentState = GetStatePtr(CurrentStateID))
	{
		pCurrentState->OnTickState(_fDeltaTime);
	}
}

void UDDState::RegistState(uint8 _nIndex,
                           TSubclassOf<UDDStateBase> _SceneType, UObject* _pOuter)
{
	if (mapState.Contains(_nIndex))
		return;

	UObject* ParentObject = IsValid(_pOuter) ? _pOuter : nullptr;
	UDDStateBase* StateBase = NewObject<UDDStateBase>(ParentObject, _SceneType);

	StateBase->Initialize(_nIndex);

	mapState.Add(_nIndex, StateBase);
}

void UDDState::UnRegistState()
{
	for (const auto State : mapState)
	{
		State.Value->Finalize();
	}
	mapState.Reset();
}

void UDDState::SetState(uint8 _uiIndex, bool _bInstant)
{
	SetState_Internal(_uiIndex);
}

UDDStateBase* UDDState::GetStatePtr(uint8 _nIndex)
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

UDDStateBase* UDDState::GetCurrentStatePtr()
{
	return GetStatePtr(CurrentStateID);
}

UDDStateBase* UDDState::GetPreviousStatePtr()
{
	return GetStatePtr(PreviousStateID);
}

void UDDState::SetState_Internal(uint8 _nIndex)
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

void UDDStateBase::Initialize(uint8 _nIndex)
{
	StateIndex = _nIndex;
}

void UDDStateBase::Finalize()
{
	StateIndex = -1;
}

void UDDStateBase::OnBeginState()
{
	Begin();
}

void UDDStateBase::OnTickState(const float& Deltatime)
{
	Tick(Deltatime);
}

void UDDStateBase::OnExitState()
{
	Exit();
}
