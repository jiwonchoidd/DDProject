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
	void Initialize(UObject* _CreatedObject = nullptr);
	void Finalize();
	FORCEINLINE TWeakObjectPtr<UObject> GetSourceObject() const { return SourceObject; }

private:
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent>		BaseCamera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent>	SpringArm = nullptr;
private:
	UPROPERTY()
	TWeakObjectPtr<UObject> SourceObject = nullptr;

public:
	ADDCharacterBase();
};
