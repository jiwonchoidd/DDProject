#include "DDProjectEditor.h"

#include "LevelEditor.h"
#include "DDFundamental/DDModuleInterface.h"

#define LOCTEXT_NAMESPACE "DDProjectEditor"

TSharedRef<FWorkspaceItem> FDDProjectEditor::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

IMPLEMENT_PRIMARY_GAME_MODULE(FDDProjectEditor, DDProjectEditor, "DDProjectEditor");

void FDDProjectEditor::StartupModule()
{
	DDModuleInterface::StartupModule();

	if (!IsRunningCommandlet())
	{
		FLevelEditorModule& levelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		ExtensibilityManager = levelEditorModule.GetMenuExtensibilityManager();
		MenuExtender = MakeShareable(new FExtender);
		MenuExtender->AddMenuBarExtension(TEXT("Window"), EExtensionHook::After, NULL, FMenuBarExtensionDelegate::CreateRaw(this, &FDDProjectEditor::MakePulldownMenu));
		ExtensibilityManager->AddExtender(MenuExtender);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("FDDEditorModule::StartupModule"));
}

void FDDProjectEditor::ShutdownModule()
{
	DDModuleInterface::ShutdownModule();
	
}

void FDDProjectEditor::AddModuleListener()
{
	DDModuleInterface::AddModuleListener();
}

void FDDProjectEditor::MakePulldownMenu(FMenuBarBuilder& menuBuilder)
{
	menuBuilder.AddPullDownMenu(
		FText::FromString(TEXT("DD Studio")),
		FText::FromString(TEXT("DD Stuido Editor")),
		FNewMenuDelegate::CreateRaw(this, &FDDProjectEditor::FillPulldownMenu),
		TEXT("DD Studio"),
		TEXT("DD Studio")
	);
}

void FDDProjectEditor::FillPulldownMenu(FMenuBuilder& menuBuilder)
{
	menuBuilder.BeginSection(TEXT(""), FText::FromName(EditorMenuNames::DD));
	menuBuilder.AddMenuSeparator(EditorMenuNames::DD);
	menuBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE
