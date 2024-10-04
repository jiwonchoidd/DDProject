#include "DDEditorModule.h"

#include "LevelEditor.h"
#include "DDFundamental/DDModuleInterface.h"

#define LOCTEXT_NAMESPACE "DD_Editor"

TSharedRef<FWorkspaceItem> FDDEditorModule::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

IMPLEMENT_PRIMARY_GAME_MODULE(FDDEditorModule, DDProject, "DDProject");

void FDDEditorModule::StartupModule()
{
	DDModuleInterface::StartupModule();

	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& levelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		ExtensibilityManager = levelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension(TEXT("Window"), EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FDDEditorModule::MakePulldownMenu));
		ExtensibilityManager->AddExtender(MenuExtender);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("FDDEditorModule::StartupModule"));
}

void FDDEditorModule::ShutdownModule()
{
	DDModuleInterface::ShutdownModule();
	
}

void FDDEditorModule::AddModuleListener()
{
	DDModuleInterface::AddModuleListener();
}

void FDDEditorModule::MakePulldownMenu(FMenuBarBuilder& menuBuilder)
{
	menuBuilder.AddPullDownMenu(
		FText::FromString(TEXT("DD Studio")),
		FText::FromString(TEXT("DD Stuido Editor")),
		FNewMenuDelegate::CreateRaw(this, &FDDEditorModule::FillPulldownMenu),
		TEXT("DD Studio"),
		TEXT("DD Studio")
	);
}

void FDDEditorModule::FillPulldownMenu(FMenuBuilder& menuBuilder)
{
	menuBuilder.BeginSection(TEXT(""), FText::FromName(EditorMenuNames::DD));
	menuBuilder.AddMenuSeparator(EditorMenuNames::DD);
	menuBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE
