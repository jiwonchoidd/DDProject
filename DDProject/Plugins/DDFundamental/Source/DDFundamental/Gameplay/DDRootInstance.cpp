// Fill out your copyright notice in the Description page of Project Settings.


#include "DDRootInstance.h"

#include "DDFundamental/Manangers/DDLoadManager.h"
#include "DDFundamental/Manangers/DDSceneManager.h"
#include "DDFundamental/Manangers/DDUnitManager.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

UDDRootInstance* UDDRootInstance::RootInstance = nullptr;

void UDDRootInstance::Init()
{
	Super::Init();

	RootInstance = this;
	
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

	RootInstance = nullptr;
	Super::Shutdown();
}

void UDDRootInstance::InitSingletons()
{
	Singletons.Emplace(UDDLoadManager::MakeInstance());
	Singletons.Emplace(UDDUnitManager::MakeInstance());
	Singletons.Emplace(UDDSceneManager::MakeInstance());
}

void UDDRootInstance::ShutdownSingletons()
{
	UDDSceneManager::RemoveInstance();
	UDDUnitManager::RemoveInstance();
	UDDLoadManager::RemoveInstance();
}
