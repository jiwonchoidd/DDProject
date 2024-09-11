// Fill out your copyright notice in the Description page of Project Settings.


#include "DDUnitManager.h"

#include "DDFunctionLibrary.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Unit/DDCharacterBase.h"
#include "DDFundamental/Unit/DDUnitBase.h"


DDHandle UDDUnitManager::NextHandle = 0;

void UDDUnitManager::Initialize()
{
	UnitContainer.Reset();
	NextHandle = 0;
}

void UDDUnitManager::Finalize()
{
}

void UDDUnitManager::Tick(float _DeltaTime)
{
	
}

UDDUnitBase* UDDUnitManager::CreateUnit(const TSubclassOf<UDDUnitBase>& _UnitType, const FDDSpawnCommand& _SpawnCommand)
{
	return CreateUnit_Internal(_UnitType, _SpawnCommand);
}

TWeakObjectPtr<UDDUnitBase> UDDUnitManager::GetUnit(DDHandle _Handle)
{
	if(UnitContainer.Contains(_Handle))
	{
		return UnitContainer[_Handle];
	}
	return nullptr;
}

UDDUnitBase* UDDUnitManager::CreateUnit_Internal(const TSubclassOf<UDDUnitBase>& _UnitType,
                                                 const FDDSpawnCommand& _Command)
{
	UDDUnitBase* pUnit = NewObject<UDDUnitBase>(this, _UnitType);
	pUnit->AddToRoot();
	if (!pUnit->CreateUnit(NextHandle, _Command))
	{
		pUnit->RemoveFromRoot();
		pUnit = nullptr;
		return nullptr;
	}
	UnitContainer.Add(NextHandle++, pUnit);
	return pUnit;
}

void UDDUnitManager::Test()
{
	/*UObject* pObj = _Command.Sop.ResolveObject();
	if (!IsValid(pObj))
		return false;

	const UBlueprint* pBp = Cast<UBlueprint>(pObj);
	ADDCharacterBase* SpawnActor = nullptr;
	if (pBp->GeneratedClass->IsChildOf(ADDCharacterBase::StaticClass()))
	{
		if (UWorld* pWorld = UDDRootInstance::RootInstance->GetWorld())
		{
			SpawnActor = Cast<ADDCharacterBase>(gLoader.SpawnActor(
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
	return true;*/
}
