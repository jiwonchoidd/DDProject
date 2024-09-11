// Fill out your copyright notice in the Description page of Project Settings.


#include "DDUnitBase.h"

#include "DDCharacterBase.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Manangers/DDFunctionLibrary.h"
#include "DDFundamental/Manangers/DDUnitManager.h"

bool UDDUnitBase::CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command)
{
	UObject* pObj = UDDFunctionLibrary::SyncLoadAsset(_Command.AssetPath);
	if (!IsValid(pObj))
	{
		return false;
	}

	const UBlueprint* pBp = Cast<UBlueprint>(pObj);
	ADDCharacterBase* SpawnActor = nullptr;
	if (pBp->GeneratedClass->IsChildOf(ADDCharacterBase::StaticClass()))
	{
		if (UWorld* pWorld = GDDInstance->GetWorld())
		{
			SpawnActor = Cast<ADDCharacterBase>(UDDFunctionLibrary::SpawnActor(
				pBp->GeneratedClass, pWorld,
				_Command.Pos, _Command.Rot,
				TEXT("UnitActor"),
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
		}
	}
	if (SpawnActor == nullptr)
		return false;

	UnitActor = SpawnActor;
	Handle = _Handle;
	return true;
}
