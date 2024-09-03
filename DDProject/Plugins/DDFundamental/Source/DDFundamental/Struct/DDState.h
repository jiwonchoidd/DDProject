#pragma once
#include "DDFundamental/Struct/DDBaseState.h"
#include "DDState.generated.h"
/**
 * 
 */

UCLASS()
class DDFUNDAMENTAL_API UDDState : public UObject
{
	GENERATED_BODY()

public:
	void Create();
	void Destroy();
	void Tick(float _fDeltaTime);

	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
    void AddState(T _Enum, TSubclassOf<class UDDBaseState> _SceneType, UObject* _pOuter)
    {
        const uint8 Num = static_cast<uint8>(_Enum);
        if (mapState.Contains(Num))
            return;

        UObject* ParentObject = IsValid(_pOuter) ? _pOuter : nullptr;
        if (UDDBaseState* StateBase = NewObject<UDDBaseState>(ParentObject, _SceneType))
        {
            StateBase->Initialize(Num);
            mapState.Add(Num, StateBase);
        }
    }
	
	void SetState(uint8 _uiIndex, bool _bInstant = true);

	FORCEINLINE uint8 GetPreviousStateID() const { return PreviousStateID; }
	FORCEINLINE uint8 GetCurrentStateID() const { return CurrentStateID; }
	FORCEINLINE uint8 GetChangeStateID() const { return ChangeStateID; }

	class UDDBaseState* GetStatePtr(uint8 _nIndex);
	class UDDBaseState* GetCurrentStatePtr();
	class UDDBaseState* GetPreviousStatePtr();

private:
	void SetState_Internal(uint8 _nIndex);

private:
	uint8 PreviousStateID = 0;
	uint8 CurrentStateID = 0;
	uint8 ChangeStateID = 0;
	UPROPERTY()
	TMap<uint8, class UDDBaseState*> mapState;
};
