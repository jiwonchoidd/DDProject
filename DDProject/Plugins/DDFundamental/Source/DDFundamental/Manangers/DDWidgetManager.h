// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "UObject/Object.h"
#include "DDWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class DDFUNDAMENTAL_API UDDWidgetManager : public UObject, public DDSingleton<UDDWidgetManager>
{
	GENERATED_BODY()

public:
	static FName Appearance;
	static FName Disappearance;
protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Tick(float _DeltaTime) override;
public:
	template <typename T = UUserWidget, typename OwnerType = UObject>
	T* AddWidget(const FString& _Path, int32 _ZOrder = 0)
	{
		return Cast<T>(AddWidget_Internal(_Path, _ZOrder));
	}
	/*template<typename T> T* GetWidget(const FName& _TypeName)
	{
		return Cast<T>(GetWidget_Internal(_TypeName));
	}*/
	void RemoveAllWidgets();
	bool RemoveWidgets(const FName& _TypeName);
private:
	class UUserWidget* AddWidget_Internal(const FString& _Path, int32 _ZOrder);
private:
	TMap<FName, TWeakObjectPtr<class UUserWidget>> Widgets;
};
#define gWidgetMng (*UDDWidgetManager::GetInstance())