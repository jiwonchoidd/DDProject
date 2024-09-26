// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DDPROJECT_API UDDGameInstance : public UDDRootInstance
{
	GENERATED_BODY()

private:
	virtual void Init() override;
	virtual void InitSingletons() override;
	virtual void ShutdownSingletons() override;
	virtual void OnWorldBeginPlay() override;

	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;
};
