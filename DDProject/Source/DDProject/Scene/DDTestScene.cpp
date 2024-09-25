#include "DDTestScene.h"

#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Manangers/DDTableManager.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "DDFundamental/Unit/DDBaseCharacter.h"
#include "DDProject/GamePlay/GameDefine.h"
#include "DDProject/Table/RowHeader/BPResource.h"
#include "DDProject/Unit/DDPlayer.h"

void UDDTestScene::Begin()
{
	Super::Begin();

	if(const FBPResource* pResource = gTableMng.GetRowData<FBPResource>(ETableType::BPResource, 1001))
	{
		FDDSpawnCommand Command;
		Command.Pos = FVector(0, 0, 100);
		Command.Rot = FRotator(0, 0, 0);
		Command.AutoPossess = true;
		Command.BPPath = pResource->Blueprint.ToSoftObjectPath();

		UObject* d = Command.BPPath.ResolveObject();
			
		DDHandle hPlayer = gUnitMng.CreateActor(Command);
		if (hPlayer != INDEX_NONE)
		{
			PlayerHandle = hPlayer;
		}

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

	gUnitMng.DestroyUnit(PlayerHandle);
	PlayerHandle = INDEX_NONE;
}
