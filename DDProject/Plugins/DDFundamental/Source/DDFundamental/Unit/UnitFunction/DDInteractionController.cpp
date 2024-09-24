// Fill out your copyright notice in the Description page of Project Settings.


#include "DDInteractionController.h"

#include "DDFundamental/Unit/DDCharacterBase.h"
#include "DDFundamental/Unit/DDUnitBase.h"

void UDDInteractionController::Initialize()
{
	Owner = CastChecked<UDDUnitBase>(GetOuter());

	FComponentBeginOverlapSignature& FOnBegin	= Owner->GetUnitActor()->GetBeginOverlapSignature();
	FComponentEndOverlapSignature&	 FOnEnd		= Owner->GetUnitActor()->GetEndOverlapSignature();

	FOnBegin.AddDynamic(this, &ThisClass::UDDInteractionController::OnBeginOverlap);
	FOnEnd.AddDynamic(this, &ThisClass::UDDInteractionController::OnEndOverlap);
}

void UDDInteractionController::Finalize()
{
	FComponentBeginOverlapSignature& FOnBegin	= Owner->GetUnitActor()->GetBeginOverlapSignature();
	FComponentEndOverlapSignature&	 FOnEnd		= Owner->GetUnitActor()->GetEndOverlapSignature();
	
	FOnBegin.RemoveDynamic(this, &ThisClass::UDDInteractionController::OnBeginOverlap);
	FOnEnd.RemoveDynamic(this, &ThisClass::UDDInteractionController::OnEndOverlap);
	
	Owner.Reset();
	Owner = nullptr;
}

void UDDInteractionController::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                              const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("대충 오버랩 시작 유닛 핸들 : %d"), Owner->GetUnitHandle()));
}

void UDDInteractionController::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("대충 오버랩 끝 유닛 핸들 : %d"), Owner->GetUnitHandle()));
}
