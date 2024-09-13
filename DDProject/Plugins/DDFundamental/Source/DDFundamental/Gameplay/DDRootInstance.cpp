#include "DDRootInstance.h"

#include "DDFundamental/Struct/DDSingleton.h"
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
}

void UDDRootInstance::InitSingletons()
{
}

void UDDRootInstance::ShutdownSingletons()
{
}
