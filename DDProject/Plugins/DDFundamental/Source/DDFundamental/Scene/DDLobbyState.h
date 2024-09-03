// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDBaseState.h"
#include "DDLobbyState.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDLobbyState : public UDDBaseState
{
	GENERATED_BODY()

private:
	virtual void Begin() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Exit() override;
};
