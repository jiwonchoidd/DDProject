// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDSingleton.h"
#include "UObject/Object.h"
#include "DDSceneManager.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDSceneManager : public UObject, public DDSingleton<UDDSceneManager>
{
	GENERATED_BODY()

public: 
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float _DeltaTime) override;
public:
	void OnChangeLevel();

private:
	UPROPERTY()
	class UDDState* SceneState = nullptr;
};

#define gSceneMng (*UGW_SceneManager::GetInstance())