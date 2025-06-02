// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DDTestSceneWidget.generated.h"

/**
 * 
 */
UCLASS()
class DDPROJECT_API UDDTestSceneWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
public:
	void AddViewportActor(class UActor* _Actor);
protected:
	UPROPERTY(meta=(BindWidget))
	class UOverlay* CPP_ViewPortPanel = nullptr;
	UPROPERTY()
	class UViewport* PreviewViewport;
};
