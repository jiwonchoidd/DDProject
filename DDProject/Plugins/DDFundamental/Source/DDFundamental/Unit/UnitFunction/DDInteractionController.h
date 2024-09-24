// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DDInteractionController.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDInteractionController : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize();
	void Finalize();

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	TWeakObjectPtr<class UDDUnitBase> Owner = nullptr;
};
