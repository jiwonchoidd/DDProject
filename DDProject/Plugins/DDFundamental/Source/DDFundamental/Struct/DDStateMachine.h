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
	
	void AddState(uint8 _uiIndex, TSubclassOf<class UDDStateBase> _SceneType, UObject* _pOuter);

	void SetState(uint8 _uiIndex, bool _bInstant = true);

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