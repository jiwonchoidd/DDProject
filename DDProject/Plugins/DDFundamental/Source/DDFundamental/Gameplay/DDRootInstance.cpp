// Fill out your copyright notice in the Description page of Project Settings.


#include "DDRootInstance.h"

#include "DDFundamental/Manangers/DDSceneManager.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

UDDRootInstance* GDDInstance = nullptr;

void UDDRootInstance::Init()
{
	Super::Init();

	GDDInstance = this;

#if defined(ANDROID_PLATFORM)
	Device = EDDDevice::AOS;
	FPlatformApplicationMisc::ControlScreensaver(FGenericPlatformApplicationMisc::EScreenSaverAction::Disable);
#elif !defined(IOS_PLATFORM)
	Device = EDDDevice::IOS;
	FPlatformApplicationMisc::ControlScreensaver(FGenericPlatformApplicationMisc::EScreenSaverAction::Disable);
#else
	Device = EDDDevice::EOS;
#endif

	Singletons.Reset();

	InitSingletons();

	for (ISingleton* Singleton : Singletons)
	{
		Singleton->Initialize();
	}

	if (UWorld* pWorld = GetWorld())
	{
		pWorld->OnWorldBeginPlay.AddUObject(this, &ThisClass::OnWorldBeginPlay);
	}
	
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &ThisClass::Tick));
}

void UDDRootInstance::Shutdown()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	if (UWorld* pWorld = GetWorld())
	{
		pWorld->OnWorldBeginPlay.RemoveAll(this);
	}
	
	for (ISingleton* Singleton : Singletons)
	{
		Singleton->Finalize();
		Singleton = nullptr;
	}

	ShutdownSingletons();

	Singletons.Reset();
	
	GDDInstance = nullptr;
	Super::Shutdown();
}

bool UDDRootInstance::Tick(float _DeltaTime)
{
	for (ISingleton* Singleton : Singletons)
	{
		Singleton->Tick(_DeltaTime);
	}
	return true;
}

void UDDRootInstance::OnWorldBeginPlay()
{
#if WITH_EDITOR
	if (IsValid(GEditor)
		&& GEditor->IsPlayingSessionInEditor()
		&& GEditor->GetPlayInEditorSessionInfo()->OriginalRequestParams.HasPlayWorldPlacement())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("TEST-MODE"));
		gSceneMng.ChangeLevel(EDDSceneState::Test);
	}
	else
#endif
	{
	}
}

void UDDRootInstance::InitSingletons()
{
	Singletons.Emplace(UDDUnitManager::MakeInstance());
	Singletons.Emplace(UDDSceneManager::MakeInstance());
}

void UDDRootInstance::ShutdownSingletons()
{
	UDDSceneManager::RemoveInstance();
	UDDUnitManager::RemoveInstance();
}
