// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
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

public:
	void BindingInputAction(UInputComponent* _InputComponent) const;
private:
	UPROPERTY()
	class UInputMappingContext* MappingContext = nullptr;
	UPROPERTY()
	TArray<class UInputAction*> InputActions;
};
