#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "UObject/Object.h"
#include "DDFunctionLibrary.generated.h"

UCLASS()
class DDFUNDAMENTAL_API UDDFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static TSharedPtr<FStreamableHandle> AsyncLoadAsset(const FSoftObjectPath& _AssetRef, TFunction<void()>&& _Callback);
	static TSharedPtr<FStreamableHandle> AsyncLoadAsset(const TArray<FSoftObjectPath>& _AssetRef, TFunction<void()>&& _Callback);
	static TSharedPtr<FStreamableHandle> AsyncLoadAsset(const FSoftObjectPath& _AssetRef, FStreamableDelegate _Callback);
	static TSharedPtr<FStreamableHandle> AsyncLoadAsset(const TArray<FSoftObjectPath>& _AssetRef, FStreamableDelegate _Callback);
	static UObject*						 SyncLoadAsset(const FString& _AssetPath);
	static AActor*						 SpawnActor(UClass* _Class, UWorld* _World, const FVector& _Loc, const FRotator& _Rot, const FString& _Label, ESpawnActorCollisionHandlingMethod _Method = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
};