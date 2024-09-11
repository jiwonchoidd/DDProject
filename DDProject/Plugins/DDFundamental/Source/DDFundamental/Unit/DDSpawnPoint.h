// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DDSpawnPoint.generated.h"

USTRUCT()
struct FDDSpawnOption
{
	int32 UnitTableId = 0;
};

UCLASS()
class DDFUNDAMENTAL_API ADDSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ADDSpawnPoint();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	class UBillboardComponent* SpriteComponent = nullptr;
	UPROPERTY()
	class UArrowComponent* ArrowComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = SpawnOption, meta=(AllowPrivateAccess = "true"))
	FDDSpawnOption UnitTableId;
};
