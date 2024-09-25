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
	FVector Pos = FVector::ZeroVector;
	FRotator Rot = FRotator::ZeroRotator;
	FSoftObjectPath BPPath = FSoftObjectPath();
	bool AutoPossess = false;
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
	DDHandle		CreateActor(const FDDSpawnCommand& _SpawnCommand);
	bool			DestroyUnit(DDHandle _UnitHandle);
	
	TWeakObjectPtr<class ADDBaseCharacter> GetUnitActor(DDHandle _Handle);

	bool TryPossess(DDHandle _UnitHandle);
private:
	DDHandle CreateUnit_Internal(const FDDSpawnCommand& _Command);
private:
	TMap<DDHandle, TWeakObjectPtr<ADDBaseCharacter>> UnitContainer;
	DDHandle PlayerHandle = INDEX_NONE;
};

#define gUnitMng (*UDDUnitManager::GetInstance())