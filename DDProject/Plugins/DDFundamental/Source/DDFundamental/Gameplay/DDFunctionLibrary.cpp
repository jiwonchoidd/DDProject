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

UObject* UDDFunctionLibrary::SyncLoadAsset(const FString& _AssetPath)
{
	UObject* LoadedAsset = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr, *_AssetPath));
	return LoadedAsset;
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