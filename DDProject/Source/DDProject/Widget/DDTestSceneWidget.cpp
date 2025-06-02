// Fill out your copyright notice in the Description page of Project Settings.


#include "DDTestSceneWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/Viewport.h"
#include "Components/WidgetComponent.h"

void UDDTestSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_ViewPortPanel)
	{
		PreviewViewport = WidgetTree->ConstructWidget<UViewport>(UViewport::StaticClass(), TEXT("PreviewViewport"));
		CPP_ViewPortPanel->AddChild(PreviewViewport);
	}
}

void UDDTestSceneWidget::AddViewportActor(class UActor* _Actor)
{
	if (PreviewViewport)
	{
		// 3D 객체를 추가할 새로운 UWidgetComponent 생성
		UWidgetComponent* WidgetComponent = NewObject<UWidgetComponent>(this);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::World);  // 월드 공간에서 렌더링

		// 캐릭터를 `WidgetComponent`에 추가 (캐릭터의 부모로 설정)
		if (_Actor)
		{
			WidgetComponent->SetWorldLocation(_Actor->GetActorLocation());  // 캐릭터 위치
			WidgetComponent->SetWorldRotation(_Actor->GetActorRotation());  // 캐릭터 회전
			WidgetComponent->AttachToComponent(PreviewViewport->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

			// UI 위에 추가된 3D 캐릭터를 렌더링
			CPP_ViewPortPanel->AddChildToOverlay(WidgetComponent);
		}
	}
}
