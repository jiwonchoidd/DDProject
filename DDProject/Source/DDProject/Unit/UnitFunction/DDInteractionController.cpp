// Fill out your copyright notice in the Description page of Project Settings.


#include "DDInteractionController.h"

#include "Components/SphereComponent.h"
#include "DDFundamental/Unit/DDCharacterBase.h"
#include "DDFundamental/Unit/DDUnitBase.h"

void UDDInteractionController::Initialize()
{
	Owner = CastChecked<UDDUnitBase>(GetOuter());

	TWeakObjectPtr<ADDCharacterBase> Actor = Owner->GetUnitActor();
	if (Actor.IsValid())
	{
		USphereComponent* pComp = Cast<USphereComponent>(Actor->AddComponentByClass(USphereComponent::StaticClass(), false, FTransform::Identity, false ));
		pComp->SetSphereRadius(300.f);
		pComp->SetGenerateOverlapEvents(true);
		pComp->SetEnableGravity(false);
		pComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		pComp->SetCollisionProfileName(TEXT("QueryOnly"));

		// 테스트 임시 노출
		pComp->SetHiddenInGame(false);
		
		FComponentBeginOverlapSignature* FOnBegin = &pComp->OnComponentBeginOverlap;
		FComponentEndOverlapSignature* FOnEnd = &pComp->OnComponentEndOverlap;

		if (FOnBegin && FOnEnd)
		{
			FOnBegin->AddDynamic(this, &ThisClass::UDDInteractionController::OnBeginOverlap);
			FOnEnd->AddDynamic(this, &ThisClass::UDDInteractionController::OnEndOverlap);
		}
	}
}

void UDDInteractionController::Finalize()
{
	TWeakObjectPtr<ADDCharacterBase> Actor = Owner->GetUnitActor();
	if(Actor.IsValid())
	{
		USphereComponent* pComp = Cast<USphereComponent>(Actor->GetComponentByClass(USphereComponent::StaticClass()));
		
		FComponentBeginOverlapSignature* FOnBegin = &pComp->OnComponentBeginOverlap;
		FComponentEndOverlapSignature* FOnEnd = &pComp->OnComponentEndOverlap;

		if(FOnBegin && FOnEnd)
		{
			FOnBegin->RemoveDynamic(this, &ThisClass::UDDInteractionController::OnBeginOverlap);
			FOnEnd->RemoveDynamic(this, &ThisClass::UDDInteractionController::OnEndOverlap);
		}
	}
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