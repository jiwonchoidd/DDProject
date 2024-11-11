// Fill out your copyright notice in the Description page of Project Settings.


#include "DDWidgetManager.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "DDFundamental/Gameplay/DDFunctionLibrary.h"
#include "DDFundamental/Gameplay/DDRootInstance.h"

FName UDDWidgetManager::Appearance = TEXT("appearance");
FName UDDWidgetManager::Disappearance = TEXT("disappearance");

void UDDWidgetManager::Initialize()
{
}

void UDDWidgetManager::Finalize()
{
	RemoveAllWidgets();
}

void UDDWidgetManager::Tick(float _DeltaTime)
{
}

UUserWidget* UDDWidgetManager::AddWidget_Internal(const FString& _Path, int32 _ZOrder)
{
	const UUserWidgetBlueprint* pWidgetBP = Cast<UUserWidgetBlueprint>(UDDFunctionLibrary::SyncLoadAsset(_Path));
	if (!IsValid(pWidgetBP) || !IsValid(pWidgetBP->GeneratedClass))
	{
		return nullptr;
	}

	UWorld* World = GDDInstance->GetWorld();
	if (World != nullptr && World->bIsTearingDown == false)
	{
		UClass* WidgetClass = pWidgetBP->GeneratedClass;
		if (UUserWidget* Widget = CreateWidget(World, WidgetClass))
		{
			Widget->AddToViewport(_ZOrder);
			Widgets.Emplace(Widget->GetName(), Widget);
			return Widget;
		}
	}

	return nullptr;
}

void UDDWidgetManager::RemoveAllWidgets()
{
	for (const auto& Pair : Widgets)
	{
		if (const TWeakObjectPtr<UUserWidget>& Ptr = Pair.Value; Ptr.IsValid())
		{
			Ptr->RemoveFromRoot();
			Ptr->MarkAsGarbage();
		}
	}
	Widgets.Empty();
}

bool UDDWidgetManager::RemoveWidgets(const FName& _TypeName)
{
	TWeakObjectPtr<UUserWidget> WidgetPtr = Widgets.Contains(_TypeName) ? *Widgets.Find(_TypeName) : nullptr;
	if (!WidgetPtr.IsValid())
		return false;

	Widgets.Remove(_TypeName);
	return true;
}
