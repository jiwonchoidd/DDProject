#include "DDTestScene.h"

#include "DDFundamental/Gameplay/DDPlayerController.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "DDFundamental/Unit/DDCharacterBase.h"
#include "DDFundamental/Unit/DDUnitBase.h"
#include "DDProject/Unit/DDDefaultUnit.h"
#include "Kismet/GameplayStatics.h"

void UDDTestScene::Begin()
{
	Super::Begin();

	FDDSpawnCommand SC;
	SC.Pos = FVector(0, 0, 100);
	SC.Rot = FRotator(0, 0, 0);
	SC.AssetPath = TEXT("/Script/Engine.Blueprint'/Game/Unit/BP_CharBase.BP_CharBase'");

	if (const UDDUnitBase* UnitBase = gUnitMng.CreateUnit(UDDDefaultUnit::StaticClass(), SC))
	{
		PlayerHandle = UnitBase->GetUnitHandle();
	}

	const UWorld* World = GDDInstance->GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("World is null"));
		return;
	}
	ADDPlayerController* PC = Cast<ADDPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	if (PC == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is null"));
		return;
	}

	const TWeakObjectPtr<ADDCharacterBase> UnitActor = gUnitMng.GetUnit(PlayerHandle)->GetUnitActor();
	if (!UnitActor.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("UnitActor is null"));
		return;
	}

	PC->OnPossess(UnitActor.Get());

	UE_LOG(LogTemp, Log, TEXT("PlayerController possessed the UnitActor"));
}

void UDDTestScene::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);
}

void UDDTestScene::Exit()
{
	Super::Exit();

	gUnitMng.DestroyUnit(PlayerHandle);
	PlayerHandle = INDEX_NONE;
}
