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
	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
public:
	void Initialize(UObject* _CreatedObject = nullptr);
	void Finalize();
public:
	FComponentBeginOverlapSignature&	GetBeginOverlapSignature() const; 
	FComponentEndOverlapSignature&		GetEndOverlapSignature() const;

	FORCEINLINE TWeakObjectPtr<UObject> GetSourceObject() const { return SourceObject; }

private:
	// Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent>		BaseCamera = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent>	SpringArm = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent>		RangeBound = nullptr;
private:
	TWeakObjectPtr<UObject> SourceObject = nullptr;
};
