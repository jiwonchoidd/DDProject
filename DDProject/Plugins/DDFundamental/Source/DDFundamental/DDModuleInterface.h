#pragma once

#include "CoreMinimal.h"

namespace EditorMenuNames
{
	static const FName DD = FName(TEXT("DD"));
}
class IDDModuleListenerInterface
{
public:
	virtual ~IDDModuleListenerInterface () {}
	
	virtual void OnStartupModule() {}
	virtual void OnShutdownModule() {}
};

class DDFUNDAMENTAL_API DDModuleInterface : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		if (!IsRunningCommandlet())
		{
			AddModuleListener();
			for (int32 i = 0; i < ModuleListener.Num(); ++i)
			{
				ModuleListener[i]->OnStartupModule();
			}
		}
	}

	virtual void ShutdownModule() override
	{
		for (int32 i = 0; i < ModuleListener.Num(); ++i)
		{
			ModuleListener[i]->OnShutdownModule();
		}
	}

	virtual void AddModuleListener() {}

protected:
	TArray<TSharedRef<IDDModuleListenerInterface>> ModuleListener;
};