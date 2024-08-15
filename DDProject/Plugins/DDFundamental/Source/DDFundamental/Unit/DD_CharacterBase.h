// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "DD_CharacterBase.generated.h"

UCLASS()
class DDFUNDAMENTAL_API ADD_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADD_CharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
