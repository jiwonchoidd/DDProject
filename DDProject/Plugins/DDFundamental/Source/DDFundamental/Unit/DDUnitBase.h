// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DDUnitBase.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDUnitBase : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE int32 GetUnitHandle() const { return Handle; }
private:
	int32 Handle = 0;
};
