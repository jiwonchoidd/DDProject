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
	static void		SyncLoadAsset(const TArray<FSoftObjectPath>& _SofList);
	static UObject* SyncLoadAsset(const FSoftObjectPath& _AssetPath);
	static AActor*	SpawnActor(UClass* _Class, UWorld* _World, const FVector& _Loc, const FRotator& _Rot, const FString& _Label,
	                          ESpawnActorCollisionHandlingMethod _Method = ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	/*template <typename T>
	static T* GetProperty(UClass* _Class, UObject* ContainerObject)
	{
		if (!IsValid(_Class) || _Class->PropertyLink == nullptr || !IsValid(ContainerObject))
			return nullptr;

		for (FProperty* pProp = _Class->PropertyLink; pProp != nullptr; pProp = pProp->PropertyLinkNext)
		{
			if (FObjectProperty* pObjProp = CastField<FObjectProperty>(pProp))
			{
				if (pObjProp->PropertyClass == T::StaticClass())
				{
					if (T* pTargetProperty = Cast<T>(pObjProp->GetObjectPropertyValue_InContainer(ContainerObject)))
					{
						if (pTargetProperty->MovieScene != nullptr)
						{
							FName animName = pTargetProperty->MovieScene->GetFName();
							mapAnimations.Add(animName, pTargetProperty);
							return pTargetProperty; // 첫 번째 발견된 T* 반환
						}
					}
				}
			}
		}
		return nullptr;
	}*/
};
