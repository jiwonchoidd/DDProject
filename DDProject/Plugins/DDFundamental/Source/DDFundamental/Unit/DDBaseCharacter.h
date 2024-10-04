// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "GameFramework/Character.h"
#include "DDBaseCharacter.generated.h"


/*
 *	유닛 매니져에서 생성하는 베이스 액터
 */
UCLASS()
class DDFUNDAMENTAL_API ADDBaseCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(DDHandle _Handle);
	virtual void Finalize();
public:
	FORCEINLINE DDHandle GetHandle() const { return OwnHandle; }
private:
	DDHandle OwnHandle = INDEX_NONE;
public:
	virtual void TryMove(const FVector2D& _Input){}
	virtual void TryLook(const FVector2D& _Input){}
	virtual void TryJump() {}
public:
	ADDBaseCharacter();
};
