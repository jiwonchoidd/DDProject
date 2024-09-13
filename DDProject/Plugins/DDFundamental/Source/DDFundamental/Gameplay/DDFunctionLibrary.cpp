#include "DDFunctionLibrary.h"

#include "Engine/AssetManager.h"

TSharedPtr<FStreamableHandle> UDDFunctionLibrary::AsyncLoadAsset(const FSoftObjectPath& _AssetRef, TFunction<void()>&& _Callback)
{
	TSharedPtr<FStreamableHandle> Handle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
		_AssetRef, FStreamableDelegate::CreateLambda(MoveTemp(_Callback)));
	
	return Handle;
}

TSharedPtr<FStreamableHandle> UDDFunctionLibrary::AsyncLoadAsset(const TArray<FSoftObjectPath>& _AssetRef, TFunction<void()>&& _Callback)
{
	return UAssetManager::Get().LoadAssetList(_AssetRef, FStreamableDelegate::CreateLambda(MoveTemp(_Callback)));
}

TSharedPtr<FStreamableHandle> UDDFunctionLibrary::AsyncLoadAsset(const FSoftObjectPath& _AssetRef,
	FStreamableDelegate _Callback)
{
	return UAssetManager::GetStreamableManager().RequestAsyncLoad(_AssetRef, _Callback);
}

TSharedPtr<FStreamableHandle> UDDFunctionLibrary::AsyncLoadAsset(const TArray<FSoftObjectPath>& _AssetRef,
	FStreamableDelegate _Callback)
{
	return UAssetManager::Get().LoadAssetList(_AssetRef, _Callback);
}

void UDDFunctionLibrary::SyncLoadAsset(const TArray<FSoftObjectPath>& _SofList)
{
	TArray<UObject*> LoadObjs;

	for(const auto& Sof : _SofList)
	{
		TSharedPtr<FStreamableHandle> Handle = UAssetManager::GetStreamableManager().RequestSyncLoad(Sof);
	}
}

UObject* UDDFunctionLibrary::SyncLoadAsset(const FSoftObjectPath& _AssetPath)
{
	const TSoftObjectPtr LoadPtr = TSoftObjectPtr(_AssetPath);
	return LoadPtr.LoadSynchronous();
}

AActor* UDDFunctionLibrary::SpawnActor(UClass* _Class, UWorld* _World, const FVector& _Loc, const FRotator& _Rot,
                                   const FString& _Label, ESpawnActorCollisionHandlingMethod _Method /*= ESpawnActorCollisionHandlingMethod::AlwaysSpawn*/ )
{
	if (_Class == nullptr || _World == nullptr) return nullptr;

	FActorSpawnParameters _params;
	_params.OverrideLevel = _World->GetCurrentLevel();
	_params.SpawnCollisionHandlingOverride = _Method;
	AActor* pNewActor = _World->SpawnActor(_Class, &_Loc, &_Rot, _params);
	
	return pNewActor;
}