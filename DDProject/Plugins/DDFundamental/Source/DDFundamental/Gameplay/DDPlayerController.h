// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API ADDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADDPlayerController();
private:
	virtual void BeginPlay() override;

	void SetupInputForPawn();
private:
	UPROPERTY()
	class UInputMappingContext* MappingContext = nullptr;
	UPROPERTY()
	TWeakPtr<class UInputAction> InputActions;
};
