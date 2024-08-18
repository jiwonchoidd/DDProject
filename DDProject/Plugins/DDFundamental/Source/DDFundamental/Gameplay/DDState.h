#pragma once
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

	void RegistState(uint8 _nIndex, TSubclassOf<class UDDStateBase> _SceneType, UObject* _pOuter = nullptr);
	void UnRegistState();

	void SetState(uint8 _uiIndex, bool _bInstant = true);

	FORCEINLINE uint8 GetPreviousStateID() const { return PreviousStateID; }
	FORCEINLINE uint8 GetCurrentStateID() const { return CurrentStateID; }
	FORCEINLINE uint8 GetChangeStateID() const { return ChangeStateID; }

	UDDStateBase* GetStatePtr(uint8 _nIndex);
	UDDStateBase* GetCurrentStatePtr();
	UDDStateBase* GetPreviousStatePtr();

private:
	void SetState_Internal(uint8 _nIndex);

private:
	uint8 PreviousStateID = 0;
	uint8 CurrentStateID = 0;
	uint8 ChangeStateID = 0;
	UPROPERTY() TMap<uint8, class UDDStateBase*> mapState;
};


UCLASS()
class DDFUNDAMENTAL_API UDDStateBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(uint8 _nIndex);
	virtual void Finalize();

	UFUNCTION()
	void OnBeginState();
	UFUNCTION()
	void OnTickState(const float& Deltatime);
	UFUNCTION()
	void OnExitState();

protected:
	virtual void Begin(){}
	virtual void Tick(float _fDeltaTime){}
	virtual void Exit(){}

public:
	FORCEINLINE uint8 GetStateIndex() const { return StateIndex; }

private:
	UPROPERTY()
	int32 StateIndex = -1;
};
