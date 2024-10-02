#include "DDUnitManager.h"

#include "DDFundamental/Gameplay/DDFunctionLibrary.h"
#include "DDFundamental/Gameplay/DDPlayerController.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Unit/DDBaseCharacter.h"
#include "Kismet/GameplayStatics.h"

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

//------------------------------------------------------------------------------------------

DDHandle UDDUnitManager::CreateActor(const FDDSpawnCommand& _SpawnCommand)
{
	return CreateUnit_Internal(_SpawnCommand);
}

bool UDDUnitManager::DestroyUnit(DDHandle _UnitHandle)
{
	if (UnitContainer.Contains(_UnitHandle))
	{
		TWeakObjectPtr<ADDBaseCharacter> pUnit = UnitContainer[_UnitHandle];
		if (pUnit.IsValid() && GDDInstance->GetWorld()->DestroyActor(pUnit.Get()))
		{
			pUnit.Reset();
			UnitContainer.Remove(_UnitHandle);
			return true;
		}
	}
	return false;
}

//------------------------------------------------------------------------------------------

TWeakObjectPtr<ADDBaseCharacter> UDDUnitManager::GetUnitActor(DDHandle _Handle)
{
	if (UnitContainer.Contains(_Handle))
	{
		return UnitContainer[_Handle];
	}
	return nullptr;
}

bool UDDUnitManager::TryPossess(DDHandle _UnitHandle)
{
	const UWorld* World = GDDInstance->GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is null"));
		return false;
	}

	const TWeakObjectPtr<ADDBaseCharacter> UnitActor = GetUnitActor(_UnitHandle);
	if (!UnitActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitActor is null"));
		return false;
	}

	ADDPlayerController* PC = Cast<ADDPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	if (PC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is null"));
		return false;
	}
	PC->OnPossess(UnitActor.Get());
	return true;
}

//------------------------------------------------------------------------------------------

DDHandle UDDUnitManager::CreateUnit_Internal(const FDDSpawnCommand& _Command)
{
	const UBlueprint* pBP = Cast<UBlueprint>(UDDFunctionLibrary::SyncLoadAsset(_Command.BPPath));
	if (!IsValid(pBP))
	{
		UE_LOG(LogTemp, Warning, TEXT("BP is null"));
		return INDEX_NONE;
	}

	ADDBaseCharacter* SpawnActor = nullptr;
	if (pBP->GeneratedClass->IsChildOf(ADDBaseCharacter::StaticClass()))
	{
		if (UWorld* pWorld = GDDInstance->GetWorld())
		{
			SpawnActor = Cast<ADDBaseCharacter>(UDDFunctionLibrary::SpawnActor(
				pBP->GeneratedClass, pWorld,
				_Command.Pos, _Command.Rot,
				TEXT("DDCharacter"),
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
		}
	}

	if (SpawnActor != nullptr)
	{
		SpawnActor->Initialize(NextHandle);
		
		UnitContainer.Add(NextHandle, SpawnActor);

		if(_Command.AutoPossess)
		{
			TryPossess(SpawnActor->GetHandle());
		}

		return NextHandle++;
	}
	return INDEX_NONE;
}
