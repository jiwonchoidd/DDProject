// Fill out your copyright notice in the Description page of Project Settings.


#include "DDRootInstance.h"

#include "DDFundamental/Manager/DDSceneManager.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

void UDDRootInstance::Init()
{
	Super::Init();

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
	
	for(ISingleton* Singleton : Singletons)
	{
		Singleton->Initialize();
	}
}

void UDDRootInstance::Shutdown()
{
	for(ISingleton* Singleton : Singletons)
	{
		Singleton->Finalize();
		Singleton = nullptr;
	}
	
	ShutdownSingletons();

	Singletons.Reset();
	
	Super::Shutdown();
}

void UDDRootInstance::InitSingletons()
{
	Singletons.Emplace(UDDSceneManager::MakeInstance());
}

void UDDRootInstance::ShutdownSingletons()
{
	UDDSceneManager::RemoveInstance();
}
