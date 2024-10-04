#pragma once

#include "CoreMinimal.h"
#include "DDEditorModule.h"
#include "DDFundamental/DDModuleInterface.h"

class DDFUNDAMENTAL_API FDDToolTabBase : public IDDModuleListenerInterface, public TSharedFromThis<FDDToolTabBase>
{
	virtual ~FDDToolTabBase() override
	{
	}

	virtual void OnStartupModule() override
	{
		Initialize();
		FGlobalTabmanager::Get()->RegisterNomadTabSpawner(TabName, FOnSpawnTab::CreateRaw(this, &FDDToolTabBase::SpawnTab))
			.SetGroup(FDDEditorModule::Get().GetMenuRoot())
			.SetDisplayName(TabDisplayName)
			.SetTooltipText(ToolTipText)
			.SetIcon(FSlateIcon(FAppStyle::GetAppStyleSetName(), IconName));
		
	};

	virtual void OnShutdownModule() override
	{
		FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(TabName);
	};

	virtual void Initialize()
	{
	};

	virtual TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& _TabSpawnArgs)
	{
		return SNew(SDockTab);
	};

	virtual void MakeMenuEntry(FMenuBuilder& _MenuBuilder)
	{
		FGlobalTabmanager::Get()->PopulateTabSpawnerMenu(_MenuBuilder, TabName);
	};
	
protected:
	FName TabName;
	FText TabDisplayName;
	FText ToolTipText;
	FName IconName;
};
