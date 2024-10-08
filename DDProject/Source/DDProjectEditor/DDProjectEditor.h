#pragma once
#include "DDFundamental/DDModuleInterface.h"

class FDDProjectEditor : public DDModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListener() override;

	TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; }

	static FDDProjectEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FDDProjectEditor>("DDEditor");
	}

protected:
	void MakePulldownMenu(FMenuBarBuilder& menuBuilder);
	void FillPulldownMenu(FMenuBuilder& menuBuilder);

protected:
	static TSharedRef<FWorkspaceItem> MenuRoot;

private:
	TSharedPtr<class FExtensibilityManager> ExtensibilityManager;
	TSharedPtr<class FExtender> MenuExtender;
};

