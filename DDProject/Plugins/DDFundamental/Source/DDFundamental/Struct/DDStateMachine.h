#pragma once
#include "DDFundamental/Struct/DDStateBase.h"
#include "DDStateMachine.generated.h"
/**
 * 
 */

UCLASS()
class DDFUNDAMENTAL_API UDDStateMachine : public UObject
{
	GENERATED_BODY()

public:
	void Create();
	void Destroy();
	void Tick(float _fDeltaTime);

	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	void AddState(T _Enum, TSubclassOf<UDDStateBase> _SceneType, UObject* _pOuter = nullptr);

	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	void SetState(T _SceneState);

	FORCEINLINE uint8 GetPreviousStateID() const { return PreviousStateID; }
	FORCEINLINE uint8 GetCurrentStateID() const { return CurrentStateID; }
	FORCEINLINE uint8 GetChangeStateID() const { return ChangeStateID; }

	class UDDStateBase* GetStatePtr(uint8 _nIndex);
	class UDDStateBase* GetCurrentStatePtr();
	class UDDStateBase* GetPreviousStatePtr();

private:
	void SetState_Internal(uint8 _nIndex);

private:
	uint8 PreviousStateID = -1;
	uint8 CurrentStateID = -1;
	uint8 ChangeStateID = -1;
	UPROPERTY()
	TMap<uint8, class UDDStateBase*> mapState;
};

template <typename T, typename>
void UDDStateMachine::SetState(T _SceneState)
{
	uint8 uiIndex = static_cast<uint8>(_SceneState);
	SetState_Internal(uiIndex);
}

template <typename T, typename>
void UDDStateMachine::AddState(T _Enum, TSubclassOf<UDDStateBase> _SceneType, UObject* _pOuter)
{
	const uint8 uiIndex = static_cast<uint8>(_Enum);
	if (mapState.Contains(uiIndex))
		return;

	UObject* ParentObject = IsValid(_pOuter) ? _pOuter : nullptr;
	if (UDDStateBase* StateBase = NewObject<UDDStateBase>(ParentObject, _SceneType))
	{
		StateBase->Initialize(uiIndex);
		mapState.Add(uiIndex, StateBase);
	}
}