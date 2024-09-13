// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DDUnitBase.generated.h"

struct FDDSpawnCommand;

UCLASS()
class DDFUNDAMENTAL_API UDDUnitBase : public UObject
{
	GENERATED_BODY()

public:
	virtual bool CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command);

	FORCEINLINE int32 GetUnitHandle() const { return Handle; }
	FORCEINLINE TWeakObjectPtr<class ADDCharacterBase> GetUnitActor() const { return UnitActor; }
private:
	int32 Handle = 0;
	TWeakObjectPtr<class ADDCharacterBase> UnitActor;
};
