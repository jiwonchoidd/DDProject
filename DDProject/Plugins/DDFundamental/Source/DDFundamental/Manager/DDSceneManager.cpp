// Fill out your copyright notice in the Description page of Project Settings.


#include "DDSceneManager.h"

#include "DDFundamental/Gameplay/DDState.h"

void UDDSceneManager::Initialize()
{
	SceneState = NewObject<UDDState>();
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
	
}

void UDDSceneManager::OnChangeLevel()
{
}
