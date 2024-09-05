// Fill out your copyright notice in the Description page of Project Settings.


#include "DDTestScene.h"

#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "DDFundamental/Unit/DDCharacterBase.h"
#include "DDFundamental/Unit/DDUnitBase.h"
#include "Kismet/GameplayStatics.h"

void UDDTestScene::Begin()
{
	Super::Begin();

	FDDSpawnCommand sc;
	sc.Pos = FVector(0,0,100);
	sc.Rot = FRotator(0,0,0);
	sc.AssetPath = TEXT("/Script/Engine.Blueprint'/Game/Unit/BP_CharBase.BP_CharBase'");
	gUnitMng.CreateUnit(UDDUnitBase::StaticClass(), sc);
	APawn* Pawn = gUnitMng.GetUnit(0)->GetUnitActor().Get();
	const UWorld* World = UDDRootInstance::RootInstance->GetWorld();
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0))
	{
		PC->Possess(Pawn);
	}
}

void UDDTestScene::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);
}

void UDDTestScene::Exit()
{
	Super::Exit();
}
