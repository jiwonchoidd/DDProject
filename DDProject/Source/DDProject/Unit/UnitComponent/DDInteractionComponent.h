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

public:
	void Move(const FVector2D& _Input);
	void Jump();
	void Look(const FVector2D& _Input) const;
private:
	void ClimbStopJump(class ADDPlayer* Owner);
	bool bClimbable = false;

private:
	TStaticArray<FHitResult, 3> WallHits;
};
