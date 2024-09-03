#include "DDLoadManager.h"

#include "Engine/AssetManager.h"

void UDDLoadManager::Initialize()
{
}

void UDDLoadManager::Tick(float _DeltaTime)
{
}

void UDDLoadManager::Finalize()
{
}

TSharedPtr<FStreamableHandle> UDDLoadManager::LoadAsset(const FSoftObjectPath& _AssetRef, TFunction<void()>&& _Callback)
{
	TSharedPtr<FStreamableHandle> Handle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
		_AssetRef, FStreamableDelegate::CreateLambda(MoveTemp(_Callback)));
	
	return Handle;
}

TSharedPtr<FStreamableHandle> UDDLoadManager::LoadAsset(const TArray<FSoftObjectPath>& _AssetRef, TFunction<void()>&& _Callback)
{
	return UAssetManager::Get().LoadAssetList(_AssetRef, FStreamableDelegate::CreateLambda(MoveTemp(_Callback)));
}

TSharedPtr<FStreamableHandle> UDDLoadManager::LoadAsset(const FSoftObjectPath& _AssetRef,
	FStreamableDelegate _Callback)
{
	return UAssetManager::GetStreamableManager().RequestAsyncLoad(_AssetRef, _Callback);
}

TSharedPtr<FStreamableHandle> UDDLoadManager::LoadAsset(const TArray<FSoftObjectPath>& _AssetRef,
	FStreamableDelegate _Callback)
{
	return UAssetManager::Get().LoadAssetList(_AssetRef, _Callback);
}

AActor* UDDLoadManager::SpawnActor(UClass* _Class, UWorld* _World, const FVector& _Loc, const FRotator& _Rot,
	const FString& _Label, ESpawnActorCollisionHandlingMethod _Method /*= ESpawnActorCollisionHandlingMethod::AlwaysSpawn*/ )
{
	if (_Class == nullptr || _World == nullptr) return nullptr;

	AActor* pNewActor = nullptr;
	FActorSpawnParameters _params;
	_params.OverrideLevel = _World->GetCurrentLevel();
	_params.SpawnCollisionHandlingOverride = _Method;
	pNewActor = _World->SpawnActor(_Class, &_Loc, &_Rot, _params);
	
	return pNewActor;
}
