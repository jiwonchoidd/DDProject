// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "Engine/StreamableManager.h"
#include "UObject/Object.h"
#include "DDLoadManager.generated.h"

/**
 * 
 */


UCLASS()
class DDFUNDAMENTAL_API UDDLoadManager : public UObject, public DDSingleton<UDDLoadManager>
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Tick(float _DeltaTime) override;
	virtual void Finalize() override;
public:
	TSharedPtr<FStreamableHandle> LoadAsset(const FSoftObjectPath& _AssetRef, TFunction<void()>&& _Callback);
	TSharedPtr<FStreamableHandle> LoadAsset(const TArray<FSoftObjectPath>& _AssetRef, TFunction<void()>&& _Callback);
	TSharedPtr<FStreamableHandle> LoadAsset(const FSoftObjectPath& _AssetRef, FStreamableDelegate _Callback);
	TSharedPtr<FStreamableHandle> LoadAsset(const TArray<FSoftObjectPath>& _AssetRef, FStreamableDelegate _Callback);

	UFUNCTION(BlueprintCallable, Category = "DDAsset")
	AActor* SpawnActor(UClass* _Class, UWorld* _World, const FVector& _Loc, const FRotator& _Rot, const FString& _Label, ESpawnActorCollisionHandlingMethod _Method = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
};

#define gLoader (*UDDLoadManager::GetInstance())