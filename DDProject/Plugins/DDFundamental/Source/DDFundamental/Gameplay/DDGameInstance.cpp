// Fill out your copyright notice in the Description page of Project Settings.


#include "DDGameInstance.h"

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
}

void UDDGameInstance::Shutdown()
{
	Super::Shutdown();
}
