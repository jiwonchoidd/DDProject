// Fill out your copyright notice in the Description page of Project Settings.


#include "DDUnitManager.h"

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

bool UDDUnitManager::DestroyUnit(DDHandle _UnitHandle)
{
	if(UnitContainer.Contains(_UnitHandle))
	{
		UDDUnitBase* pUnit = UnitContainer[_UnitHandle];
		if (pUnit != nullptr)
		{
			pUnit->DestroyUnit();
			pUnit->RemoveFromRoot();
			pUnit->MarkAsGarbage();
			pUnit = nullptr;
			UnitContainer.Remove(_UnitHandle);
			return true;
		}
	}
	return false;
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