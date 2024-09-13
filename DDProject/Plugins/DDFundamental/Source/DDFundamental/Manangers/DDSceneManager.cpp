// Fill out your copyright notice in the Description page of Project Settings.


#include "DDSceneManager.h"

#include "DDFundamental/Scene/DDLobbyScene.h"
#include "DDFundamental/Scene/DDTestScene.h"
#include "DDFundamental/Struct/DDStateMachine.h"

void UDDSceneManager::Initialize()
{
	SceneState = NewObject<UDDStateMachine>();
	if(IsValid(SceneState))
	{
		SceneState->AddToRoot();
		SceneState->Create();
	}
}

void UDDSceneManager::Finalize()
{
	if(IsValid(SceneState))
	{
		SceneState->Destroy();
		SceneState->RemoveFromRoot();
		SceneState = nullptr;
	}
}

void UDDSceneManager::Tick(float _DeltaTime)
{
	if(IsValid(SceneState))
	{
		SceneState->Tick(_DeltaTime);
	}
}
