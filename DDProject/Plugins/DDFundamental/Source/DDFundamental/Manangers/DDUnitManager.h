// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "UObject/Object.h"
#include "DDUnitManager.generated.h"

/**
 * 
 */

struct FDDSpawnCommand
{
	FSoftObjectPath Sop;
	FVector Pos = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
};

typedef int32 DDHandle;

UCLASS()
class DDFUNDAMENTAL_API UDDUnitManager : public UObject, public DDSingleton<UDDUnitManager>
{
	GENERATED_BODY()

public:
	static DDHandle UnitHandle;
protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float _DeltaTime) override;
public:
	void CreateUnit(const TSubclassOf<class UDDUnitBase>& _UnitType, const FDDSpawnCommand& _SpawnCommand);
private:
	void OnLoadComplete(TSubclassOf<UDDUnitBase> _UnitType, const FDDSpawnCommand& _Command);
private:
	TMap<DDHandle, class UDDUnitBase*> UnitContainer;
};

#define gUnitMng (*UDDUnitManager::GetInstance())