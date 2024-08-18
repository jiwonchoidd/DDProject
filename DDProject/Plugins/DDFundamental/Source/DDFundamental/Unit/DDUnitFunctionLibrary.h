// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DDUnitFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDUnitFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category=UDDUnitFunctionLibrary)
	void SetPlayerSpeed(int32 _Speed);
};
