// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Unit/DDUnitBase.h"
#include "DDDefaultUnit.generated.h"

/**
 * 
 */
UCLASS()
class DDPROJECT_API UDDDefaultUnit : public UDDUnitBase
{
	GENERATED_BODY()

public:
	virtual bool CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command) override;
};
