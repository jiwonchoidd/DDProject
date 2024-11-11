#include "DDTestScene.h"

#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Manangers/DDSoundManager.h"
#include "DDFundamental/Manangers/DDTableManager.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "DDFundamental/Manangers/DDWidgetManager.h"
#include "DDProject/GamePlay/GameDefine.h"
#include "DDProject/Table/RowHeader/BPResource.h"
#include "Blueprint/UserWidget.h"

void UDDTestScene::Begin()
{
	Super::Begin();

	bool bSuccess = OpenLevel(TEXT("/Game/Map/TestMap"));
		
	if(bSuccess == false)
	{
		check(false);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("UDDTestScene OpenLevel Fail"));
	}
}

void UDDTestScene::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);

	if (APlayerController* PlayerController = GDDInstance->GetWorld()->GetFirstPlayerController())
	{
		if (PlayerController->WasInputKeyJustReleased(EKeys::P))
		{
			gSoundMng.Push(TEXT("/Game/Sound/Test.Test"), 1.0f, 0.f, 2.0f, 2.f);
		}

		if (PlayerController->WasInputKeyJustReleased(EKeys::O))
		{
			gSoundMng.Pop();
		}
	}
}

void UDDTestScene::Exit()
{
	Super::Exit();

	gWidgetMng.RemoveAllWidgets();
	gUnitMng.DestroyUnit(PlayerHandle);
	PlayerHandle = INDEX_NONE;
}

void UDDTestScene::LevelLoadComplete()
{
	Super::LevelLoadComplete();

	gSoundMng.Push(TEXT("/Game/Sound/Test.Test"), 1.0f, 0.f, 4.0f, 4.f);

	if(const FBPResource* pResource = gTableMng.GetRowData<FBPResource>(ETableType::BPResource, 1001))
	{
		FDDSpawnCommand Command;
		Command.Pos = FVector(0, 0, 100);
		Command.Rot = FRotator(0, 0, 0);
		Command.AutoPossess = true;
		Command.BPPath = pResource->Blueprint.ToSoftObjectPath();
		
		DDHandle hPlayer = gUnitMng.CreateActor(Command);
		if (hPlayer != INDEX_NONE)
		{
			PlayerHandle = hPlayer;
		}

		UE_LOG(LogTemp, Log, TEXT("PlayerController possessed the UnitActor"));
	}

	UUserWidget* Widget = gWidgetMng.AddWidget<UUserWidget>(TEXT("/Game/Widget/WB_Test.WB_Test"));
}
