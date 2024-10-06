// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "UObject/Object.h"
#include "DDSoundManager.generated.h"

struct FDDBgmStack
{
public:
	FString Path;
	float Volume = 1.0f;
	float StartTime = 0.0f;
	float FadeInTime = 0.0f;
	float FadeOutTime = 0.0f;
	FDDBgmStack(const FString& _strSOP, float _Volume = 1.0f, float _StartTime = 0.0f, float _FadeInTime = 0.0f,
			float _FadeOutTime = 0.0f);
};

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDSoundManager : public UObject, public DDSingleton<UDDSoundManager>
{
	GENERATED_BODY()

private:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;
public:
	/**
	 * @brief 브금을 저장해놓습니다. 
	 */
	void Push(const FString& _strSOP, float _Volume = 1.0f, float _StartTime = 0.0f, float _FadeInTime = 0.0f, float _FadeOutTime = 0.0f);
	void Pop();
	void Clear();
private:
	void Play(const FDDBgmStack& _Info);
	void Stop(const FDDBgmStack& _Info);
	UFUNCTION() void OnAudioFinishedPlaying();
	
	TWeakObjectPtr<UAudioComponent> CurPlayingComponent = nullptr;
	FTimerHandle StartBgmTimerHandle;
private:
#if WITH_EDITOR
	void Print() const;
#endif
private:
	TArray<FDDBgmStack> BgmStack;
};

#define gSoundMng (*UDDSoundManager::GetInstance())