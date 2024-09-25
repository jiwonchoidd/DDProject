// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Unit/DDUnitBase.h"
#include "UObject/Object.h"
#include "DDNpcUnit.generated.h"

/**
 *  NPC
 */
UCLASS()
class DDPROJECT_API UDDNpcUnit : public UDDUnitBase
{
	GENERATED_BODY()

private:
	virtual bool CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command) override;
	virtual bool DestroyUnit() override;
private:
};
