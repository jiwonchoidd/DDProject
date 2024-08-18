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

	template<typename TEnum>
	void AddState(TEnum _Enum, TSubclassOf<class UDDStateBase> _SceneType, UObject* _pOuter = nullptr);
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


UINTERFACE(MinimalAPI)
class UStateBaseInterface : public UInterface
{
	GENERATED_BODY()
};

class DDFUNDAMENTAL_API IStateBaseInterface
{
	GENERATED_BODY()

public:
	virtual void Begin() = 0;
	virtual void Tick(float _fDeltaTime) = 0;
	virtual void Exit() = 0;
};

UCLASS()
class DDFUNDAMENTAL_API UDDStateBase : public UObject, public IStateBaseInterface
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
	virtual void Begin() override {}
	virtual void Tick(float _fDeltaTime) override {}
	virtual void Exit() override {}

public:
	FORCEINLINE uint8 GetStateIndex() const { return StateIndex; }

private:
	UPROPERTY()
	int32 StateIndex = -1;
};
