// Fill out your copyright notice in the Description page of Project Settings.


#include "DDUnitManager.h"

#include "DDLoadManager.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Unit/DDCharacterBase.h"
#include "DDFundamental/Unit/DDUnitBase.h"


DDHandle UDDUnitManager::UnitHandle = 0;

void UDDUnitManager::Initialize()
{
	UnitContainer.Reset();
	UnitHandle = 0;
}

void UDDUnitManager::Finalize()
{
}

void UDDUnitManager::Tick(float _DeltaTime)
{
	
}

void UDDUnitManager::CreateUnit(const TSubclassOf<UDDUnitBase>& _UnitType, const FDDSpawnCommand& _SpawnCommand)
{
	gLoader.LoadAsset(_SpawnCommand.Sop, FStreamableDelegate::CreateLambda(
		                  [_WeakThis = MakeWeakObjectPtr(this), _UnitType, _SpawnCommand]()
		                  {
			                  if (!_WeakThis.IsValid())
				                  return;
		                  	
			                  _WeakThis->OnLoadComplete(_UnitType, _SpawnCommand);
		                  }));
}

void UDDUnitManager::OnLoadComplete(TSubclassOf<UDDUnitBase> _UnitType, const FDDSpawnCommand& _Command)
{
	UObject* pObj = _Command.Sop.ResolveObject();
	if (!IsValid(pObj))
		return;

	UBlueprint* pBp = Cast<UBlueprint>(pObj);
	if(pBp->GeneratedClass->IsChildOf(ADDCharacterBase::StaticClass()))
	{
		if(!IsValid(UDDRootInstance::RootInstance))
			return;

		if (UWorld* pWorld = UDDRootInstance::RootInstance->GetWorld())
		{
			ADDCharacterBase* pChar = Cast<ADDCharacterBase>(gLoader.SpawnActor(
				pBp->GeneratedClass, pWorld,
				_Command.Pos, _Command.Rot,
				_Command.Sop.ToString(),
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
		}
	}

	/*if (pUnit->GetUnitHandle() == )
	{
		return nullptr;
	}


	UnitContainer.Add(pUnit->GetUnitHandle(), pUnit);

	return pUnit;*/
}