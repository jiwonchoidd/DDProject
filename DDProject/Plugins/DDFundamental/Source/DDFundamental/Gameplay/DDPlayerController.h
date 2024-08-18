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
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UFUNCTION() virtual void BaseMove(const FInputActionValue& _Value);
	UFUNCTION() virtual void BaseLook(const FInputActionValue& _Value);
	UFUNCTION() virtual void BaseJump(const FInputActionValue& _Value);
private:
	UPROPERTY()
	class UInputMappingContext* MappingContext = nullptr;
	UPROPERTY()
	class UInputAction* InputMove = nullptr;
	UPROPERTY()
	class UInputAction* InputLook = nullptr;
	UPROPERTY()
	class UInputAction* InputJump = nullptr;
};
