// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSceneBase.h"
#include "DDTestScene.generated.h"

/**
 * 
 */
UCLASS()
class UDDTestScene : public UDDSceneBase
{
	GENERATED_BODY()
public:
	virtual void Begin() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Exit() override;

	virtual void LevelLoadComplete() override;
private:
	int32 PlayerHandle = INDEX_NONE;
};
