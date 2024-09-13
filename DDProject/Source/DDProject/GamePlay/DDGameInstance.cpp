#include "DDGameInstance.h"

#include "GameDefine.h"
#include "DDFundamental/Manangers/DDSceneManager.h"
#include "DDFundamental/Manangers/DDTableManager.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "DDFundamental/Scene/DDTestScene.h"
#include "DDProject/Manager/DDNetworkManager.h"

void UDDGameInstance::Init()
{
	Super::Init();

	gTableMng.LoadDataTable(TEXT("/Game/Table"), StaticEnum<ETableType>(), false);
	gSceneMng.AddScene(ESceneType::Test, UDDTestScene::StaticClass());
}

void UDDGameInstance::InitSingletons()
{
	Super::InitSingletons();
	
	Singletons.Emplace(UDDNetworkManager::MakeInstance());
	Singletons.Emplace(UDDUnitManager::MakeInstance());
	Singletons.Emplace(UDDTableManager::MakeInstance());
	Singletons.Emplace(UDDSceneManager::MakeInstance());
}

void UDDGameInstance::ShutdownSingletons()
{
	UDDSceneManager::RemoveInstance();
	UDDTableManager::RemoveInstance();
	UDDUnitManager::RemoveInstance();
	UDDNetworkManager::RemoveInstance();
	
	Super::ShutdownSingletons();
}

void UDDGameInstance::OnWorldBeginPlay()
{
	Super::OnWorldBeginPlay();
	
#if WITH_EDITOR
	if (IsValid(GEditor)
		&& GEditor->IsPlayingSessionInEditor()
		&& GEditor->GetPlayInEditorSessionInfo()->OriginalRequestParams.HasPlayWorldPlacement())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("테스트 모드"));
		gSceneMng.ChangeScene(ESceneType::Test);
	}
	else
#endif
	{
	}
}
