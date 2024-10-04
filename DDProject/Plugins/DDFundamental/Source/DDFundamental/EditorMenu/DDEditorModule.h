#pragma once
#include "DDFundamental/DDModuleInterface.h"

class DDFUNDAMENTAL_API FDDEditorModule : public DDModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListener() override;

	TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; }

	static FDDEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FDDEditorModule>("DDEditor");
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

