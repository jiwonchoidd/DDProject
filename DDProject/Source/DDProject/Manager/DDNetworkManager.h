// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Manager/DDSingleton.h"
#include "UObject/Object.h"
#include "DDNetworkManager.generated.h"

/**
 * 
 */
UCLASS()
class DDPROJECT_API UDDNetworkManager : public UObject, public DDSingleton<UDDNetworkManager>
{
	GENERATED_BODY()

protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float _DeltaTime) override;

public:
	void TryConnect();
};

#define gNetworkMng (*UDDNetworkManager::GetInstance())
#define gNetworkMngPtr UDDNetworkManager::GetInstance()