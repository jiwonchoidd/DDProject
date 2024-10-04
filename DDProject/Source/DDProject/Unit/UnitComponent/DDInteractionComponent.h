// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DDInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DDPROJECT_API UDDInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UDDInteractionComponent();

protected:
	virtual void OnRegister() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
private:
	//TArray<FHitResult> TraceSphere(const FVector& _Start, const FVector& _End, float _Radius) const;
	FHitResult TraceSingleLine(const FVector& _Start, const FVector& _End) const;
	FHitResult TraceSphereSingle(const FVector& _Start, const FVector& _End, float _Radius, AActor* _IgnoreActor = nullptr) const;
	FHitResult TraceCapsuleSingle(const FVector& _Start, const FVector& _End, float _Radius, float _Height) const;

private:
	void StartParkour() const;
	bool ClimbWall() const;
	bool CanBeClimb(const FHitResult& _HitResult) const;
private:
	float JumpHeight = 0.0f;
};
