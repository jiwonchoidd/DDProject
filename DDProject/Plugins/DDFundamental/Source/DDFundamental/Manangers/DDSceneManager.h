// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "DDFundamental/Struct/DDStateMachine.h"
#include "UObject/Object.h"
#include "DDSceneManager.generated.h"

/**
 * 
 */

UCLASS()
class DDFUNDAMENTAL_API UDDSceneManager : public UObject, public DDSingleton<UDDSceneManager>
{
	GENERATED_BODY()

protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float _DeltaTime) override;
public:
	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	void ChangeScene(T _SceneState) const;

	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	void AddScene(T _Enum, TSubclassOf<UDDBaseState> _SceneType);
private:
	UPROPERTY()
	class UDDStateMachine* SceneState = nullptr;
};

template <typename T, typename>
void UDDSceneManager::ChangeScene(T _SceneState) const
{
	if(SceneState)
	{
		SceneState->SetState(static_cast<uint8>(_SceneState));
	}
}

template <typename T, typename>
void UDDSceneManager::AddScene(T _Enum, TSubclassOf<UDDBaseState> _SceneType)
{
	const uint8 Idx = static_cast<uint8>(_Enum);
	if(SceneState)
	{
		SceneState->AddState(Idx, _SceneType, this);
	}
}

#define gSceneMng (*UDDSceneManager::GetInstance())
