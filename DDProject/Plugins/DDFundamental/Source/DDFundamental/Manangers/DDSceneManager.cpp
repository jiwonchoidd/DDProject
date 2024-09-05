// Fill out your copyright notice in the Description page of Project Settings.


#include "DDSceneManager.h"

#include "DDFundamental/Scene/DDLobbyScene.h"
#include "DDFundamental/Scene/DDTestScene.h"
#include "DDFundamental/Struct/DDState.h"

void UDDSceneManager::Initialize()
{
	SceneState = NewObject<UDDState>();
	if(IsValid(SceneState))
	{
		SceneState->AddToRoot();
		SceneState->Create();
	}

	SceneState->AddState(EDDSceneState::Test, UDDTestScene::StaticClass(), this);
	SceneState->AddState(EDDSceneState::Lobby, UDDLobbyScene::StaticClass(), this);
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
	
}

void UDDSceneManager::ChangeLevel(EDDSceneState _SceneState) const
{
	if(SceneState)
	{
		SceneState->SetState(static_cast<uint8>(_SceneState));
	}
}
