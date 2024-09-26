// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSceneBase.h"
#include "DDLobbyScene.generated.h"

/**
 * 
 */
UCLASS()
class UDDLobbyScene : public UDDSceneBase
{
	GENERATED_BODY()

private:
	virtual void Begin() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Exit() override;
};
