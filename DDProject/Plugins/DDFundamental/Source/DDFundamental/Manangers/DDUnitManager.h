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
	FString AssetPath;
	FVector Pos = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
};

typedef int32 DDHandle;

UCLASS()
class DDFUNDAMENTAL_API UDDUnitManager : public UObject, public DDSingleton<UDDUnitManager>
{
	GENERATED_BODY()

public:
	static DDHandle NextHandle;
protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;
	
public:
	class UDDUnitBase* CreateUnit(const TSubclassOf<class UDDUnitBase>& _UnitType, const FDDSpawnCommand& _SpawnCommand);
	TWeakObjectPtr<class UDDUnitBase> GetUnit(DDHandle _Handle);
private:
	class UDDUnitBase* CreateUnit_Internal(const TSubclassOf<UDDUnitBase>& _UnitType, const FDDSpawnCommand& _Command);
	void Test();
private:
	TMap<DDHandle, class UDDUnitBase*> UnitContainer;
};

#define gUnitMng (*UDDUnitManager::GetInstance())