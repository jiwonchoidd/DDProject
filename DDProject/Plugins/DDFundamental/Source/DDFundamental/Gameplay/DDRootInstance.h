// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DDRootInstance.generated.h"

/**
 * 
 */
enum class EDDDevice : uint8
{
	NONE,
	EOS,
	AOS,
	IOS = 0xff
};

UCLASS()
class DDFUNDAMENTAL_API UDDRootInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual bool Tick(float _DeltaTime);
private:
	void OnWorldBeginPlay();
protected:
	virtual void InitSingletons();
	virtual void ShutdownSingletons();
	TArray<class ISingleton*> Singletons;
private:
	FTSTicker::FDelegateHandle TickDelegateHandle;
	EDDDevice Device = EDDDevice::NONE;
};

extern DDFUNDAMENTAL_API UDDRootInstance* GDDInstance;