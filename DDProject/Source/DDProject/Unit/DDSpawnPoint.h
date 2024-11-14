// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DDSpawnPoint.generated.h"

USTRUCT(BlueprintType)
struct FDDSpawnOption
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 UnitTableId = 0;
};

UCLASS()
class ADDSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	ADDSpawnPoint();

protected:
	virtual void BeginPlay() override;
public:
	bool SpawnUnit() const;
private:
	UPROPERTY()
	class UBillboardComponent* SpriteComponent = nullptr;
	UPROPERTY()
	class UArrowComponent* ArrowComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = SpawnOption, meta=(AllowPrivateAccess = "true"))
	FDDSpawnOption SpawnOption;
};
