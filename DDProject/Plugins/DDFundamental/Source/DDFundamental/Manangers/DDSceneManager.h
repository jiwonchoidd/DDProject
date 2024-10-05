// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "DDFundamental/Struct/DDStateMachine.h"
#include "UObject/Object.h"
#include "DDSceneManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FDD_ChangeSceneState, uint8);

UCLASS()
class DDFUNDAMENTAL_API UDDSceneManager : public UObject, public DDSingleton<UDDSceneManager>
{
	GENERATED_BODY()
	
	enum class EChangeSceneStep
	{
		Ready,
		LoadLevel,
		LoadingProcess,
		Complete,
	};
	
protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float _DeltaTime) override;
public:
	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	void ChangeScene(T _SceneState);

	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	void AddScene(T _Enum, TSubclassOf<UDDStateBase> _SceneType);

	bool OpenLevel(const FName& _LevelPath);
	bool LoadLevelInstance(const FString& _LevelPath, const FVector& Location, const FRotator& Rotation);
	bool LoadStreamLevel(const FString& _LevelPath, const FLatentActionInfo& _LatentActionInfo);
	void LoadComplete();

	UFUNCTION()
	void AdditionalLevel_LoadComplete();
	
	class UDDSceneBase* GetCurrentScenePtr() const;
	uint8 GetCurrentStateID() const;
private:
	UPROPERTY()
	class UDDStateMachine* SceneState = nullptr;
	
	FDD_ChangeSceneState OnCompleteChangeScene;
	EChangeSceneStep ChangeSceneStep = EChangeSceneStep::Ready;

public:
	FORCEINLINE class UDDSoundManager* GetGetBgmUtil() const { return BgmUtil; }
private:
	UPROPERTY()
	class UDDSoundManager* BgmUtil = nullptr;
};

template <typename T, typename>
void UDDSceneManager::ChangeScene(T _SceneState)
{
	ChangeSceneStep = EChangeSceneStep::Ready;
	if (SceneState)
	{
		SceneState->SetState(_SceneState);
	}
}

template <typename T, typename>
void UDDSceneManager::AddScene(T _Enum, TSubclassOf<UDDStateBase> _SceneType)
{
	if(SceneState)
	{
		SceneState->AddState(_Enum, _SceneType, this);
	}
}

#define gSceneMng (*UDDSceneManager::GetInstance())
