// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DDCharacterBase.generated.h"

UCLASS()
class DDFUNDAMENTAL_API ADDCharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	ADDCharacterBase();
protected:
	virtual void BeginPlay() override;
public:
	void TryAttack();
	void TryAiming() const;
	virtual void Jump() override;

};
