// Fill out your copyright notice in the Description page of Project Settings.


#include "DDGameInstance.h"

#include "DDFundamental/Manager/DDSceneManager.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

void UDDGameInstance::Init()
{
	Super::Init();

#if defined(ANDROID_PLATFORM)
	Device = EDDDevice::AOS;
	FPlatformApplicationMisc::ControlScreensaver(FGenericPlatformApplicationMisc::EScreenSaverAction::Disable);
#elif defined(IOS_PLATFORM)
	Device = EDDDevice::IOS;
	FPlatformApplicationMisc::ControlScreensaver(FGenericPlatformApplicationMisc::EScreenSaverAction::Disable);
#else
	Device = EDDDevice::EOS;
#endif

	Singletons.Reset();
	Singletons.Emplace(UDDSceneManager::MakeInstance());
	for(ISingleton* Singleton : Singletons)
	{
		Singleton->Initialize();
	}
}

void UDDGameInstance::Shutdown()
{
	for(ISingleton* Singleton : Singletons)
	{
		Singleton->Finalize();
		Singleton = nullptr;
	}
	UDDSceneManager::RemoveInstance();
	Singletons.Reset();
	
	Super::Shutdown();
}