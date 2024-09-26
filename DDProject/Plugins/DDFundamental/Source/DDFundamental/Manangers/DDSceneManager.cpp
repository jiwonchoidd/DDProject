// Fill out your copyright notice in the Description page of Project Settings.


#include "DDSceneManager.h"

#include "DDFundamental/Gameplay/DDRootInstance.h"
#include "DDFundamental/Struct/DDSceneBase.h"
#include "DDFundamental/Struct/DDStateMachine.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Kismet/GameplayStatics.h"

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
		if(ChangeSceneStep == EChangeSceneStep::Complete)
		{
			SceneState->Tick(_DeltaTime);
		}
		else if(UDDSceneBase* CurrentScene = GetCurrentScenePtr())
		{
			if(ChangeSceneStep == EChangeSceneStep::LoadingProcess)
			{
				CurrentScene->TickLoading(_DeltaTime);

				if (CurrentScene->IsCompleteLoading())
				{
					ChangeSceneStep = EChangeSceneStep::Complete;
					OnCompleteChangeScene.Broadcast(GetCurrentStateID());
				}
			}
		}
	}
}

bool UDDSceneManager::OpenLevel(const FName& _LevelPath)
{
	const UWorld* World = GDDInstance->GetWorld();
	if(!World)
		return false;

	ChangeSceneStep = EChangeSceneStep::LoadLevel;

	UGameplayStatics::OpenLevel(World, _LevelPath, true);
	
	return true;
}

bool UDDSceneManager::LoadLevelInstance(const FString& _LevelPath, const FVector& Location, const FRotator& Rotation)
{
	UWorld* World = GDDInstance->GetWorld();
	if(!World)
		return false;

	ChangeSceneStep = EChangeSceneStep::LoadLevel;

	bool bSuccess = false;
	ULevelStreamingDynamic* StreamingLevel = ULevelStreamingDynamic::LoadLevelInstance(World, _LevelPath, Location, Rotation, bSuccess);
	if (bSuccess && StreamingLevel)
	{
		StreamingLevel->OnLevelShown.AddDynamic(this, &UDDSceneManager::AdditionalLevel_LoadComplete);
		return true;
	}

	return false;
}

bool UDDSceneManager::LoadStreamLevel(const FString& _LevelPath, const FLatentActionInfo& _LatentActionInfo)
{
	const UWorld* World = GDDInstance->GetWorld();
	if(!World)
		return false;

	ChangeSceneStep = EChangeSceneStep::LoadLevel;

	UGameplayStatics::LoadStreamLevel(World, *_LevelPath, true, false,_LatentActionInfo);

	return true;
}
void UDDSceneManager::LoadComplete()
{
	ChangeSceneStep = EChangeSceneStep::LoadingProcess;
	
	if(UDDSceneBase* CurrentScene = GetCurrentScenePtr())
	{
		CurrentScene->LevelLoadComplete();
	}
}

void UDDSceneManager::AdditionalLevel_LoadComplete()
{
	ChangeSceneStep = EChangeSceneStep::LoadingProcess;

	if(UDDSceneBase* CurrentScene = GetCurrentScenePtr())
	{
		CurrentScene->AdditionalLevel_LoadComplete();
	}
}

UDDSceneBase* UDDSceneManager::GetCurrentScenePtr() const
{
	if (SceneState)
		return Cast<UDDSceneBase>(SceneState->GetCurrentStatePtr());
	return nullptr;
}

uint8 UDDSceneManager::GetCurrentStateID() const
{
	if (SceneState)
		return SceneState->GetCurrentStateID();
	return -1;
}
