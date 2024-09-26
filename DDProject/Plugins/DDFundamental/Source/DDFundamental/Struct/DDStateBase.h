// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "DDStateBase.generated.h"

/**
 * 
 */
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