// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DDMovementComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DDPROJECT_API UDDMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UDDMovementComponent();

private:
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
public:
	/** @return 충돌된 벽 상태를 반환합니다. */
	uint8 QueryDetectWall();

private:
	TStaticArray<FHitResult, 3> DetectedWallHits;
};
