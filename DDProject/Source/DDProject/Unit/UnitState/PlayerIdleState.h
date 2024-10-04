// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDStateBase.h"
#include "PlayerIdleState.generated.h"

/**
 * 
 */
UCLASS()
class DDPROJECT_API UPlayerIdleState : public UDDStateBase
{
	GENERATED_BODY()

	virtual void Begin() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Exit();
};
