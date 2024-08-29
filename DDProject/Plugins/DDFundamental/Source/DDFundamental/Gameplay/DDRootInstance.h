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
	
protected:
	virtual void Init() override;
	virtual void Shutdown() override;
private:
	virtual void InitSingletons();
protected:
	TArray<class ISingleton*> Singletons;
private:
	EDDDevice Device = EDDDevice::NONE;
};
