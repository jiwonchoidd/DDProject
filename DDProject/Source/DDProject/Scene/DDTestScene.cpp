#include "DDTestScene.h"

#include "DDFundamental/Gameplay/DDFunctionLibrary.h"
#include "DDFundamental/Gameplay/DDPlayerController.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "DDFundamental/Unit/DDCameraActor.h"
#include "DDFundamental/Unit/DDCharacterBase.h"
#include "DDFundamental/Unit/DDUnitBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

void UDDTestScene::Begin()
{
	Super::Begin();

	FDDSpawnCommand SC;
	SC.Pos = FVector(0,0,100);
	SC.Rot = FRotator(0,0,0);
	SC.AssetPath = TEXT("/Script/Engine.Blueprint'/Game/Unit/BP_CharBase.BP_CharBase'");

	// 테스트 코드 
	if(const UDDUnitBase* UnitBase = gUnitMng.CreateUnit(UDDUnitBase::StaticClass(), SC))
	{
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

		TWeakObjectPtr<ADDCharacterBase> UnitActor = UnitBase->GetUnitActor();
		if (!UnitActor.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("UnitActor is null"));
			return;
		}

		const auto pTestCam = Cast<ADDCameraActor>(UDDFunctionLibrary::SpawnActor(
				ADDCameraActor::StaticClass(), GDDInstance->GetWorld(),
				SC.Pos, SC.Rot,
				TEXT("UnitCam"),
				ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
		
		PC->OnPossess(UnitActor.Get());
		
		UE_LOG(LogTemp, Log, TEXT("PlayerController possessed the UnitActor"));
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
