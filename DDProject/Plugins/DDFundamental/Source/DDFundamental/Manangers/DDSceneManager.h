// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "UObject/Object.h"
#include "DDSceneManager.generated.h"

/**
 * 
 */
UENUM()
enum class EDDSceneState : uint8
{
	None,
	Logo,
	Login,
	Lobby,
	Test,
	Max = 0xff
};

UCLASS()
class DDFUNDAMENTAL_API UDDSceneManager : public UObject, public DDSingleton<UDDSceneManager>
{
	GENERATED_BODY()

protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float _DeltaTime) override;
public:
	void ChangeLevel(EDDSceneState _SceneState) const;

private:
	UPROPERTY()
	class UDDState* SceneState = nullptr;
};

#define gSceneMng (*UDDSceneManager::GetInstance())