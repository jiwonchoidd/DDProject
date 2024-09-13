// Fill out your copyright notice in the Description page of Project Settings.


#include "DDTableManager.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "DDFundamental/Gameplay/DDFunctionLibrary.h"

void UDDTableManager::Initialize()
{
	mapTables.Reset();
	LoadCounter = 0;
}

void UDDTableManager::Finalize()
{
	LoadCounter = 0;

	for(auto Table : mapTables)
	{
		Table.Value->RemoveFromRoot();
		Table.Value = nullptr;
	}
	mapTables.Reset();
}

void UDDTableManager::LoadDataTable(const FString& _BaseTablePath, const UEnum* _pEnum, bool _bAsyncLoad /* = false */)
{
	TArray<FSoftObjectPath> Paths = GetTableSofPaths(_BaseTablePath, _pEnum);
	
	if(!_bAsyncLoad)
	{
		UDDFunctionLibrary::SyncLoadAsset(Paths);
		OnLoadComplete(_pEnum, Paths);
	}
	else // 비동기 로드
	{
		TWeakObjectPtr<UDDTableManager> WeakThis(this);
		UDDFunctionLibrary::AsyncLoadAsset(Paths, [WeakThis, Paths, _pEnum]
		{
			if (WeakThis.IsValid() && IsValid(_pEnum))
			{
				WeakThis->OnLoadComplete(_pEnum, Paths);
			}
		});
	}
}

// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------

void UDDTableManager::OnLoadComplete(const UEnum* _pEnum, const TArray<FSoftObjectPath>& _LoadedSof)
{
	for(auto Sof : _LoadedSof)
	{
		FString AssetName = FPaths::GetBaseFilename(Sof.GetAssetName());
		
		const uint8 Index = _pEnum->GetIndexByName(FName(AssetName));
		if (Index == INDEX_NONE)
		{
			continue;
		}

		UDataTable* Obj = Cast<UDataTable>(Sof.ResolveObject());

		check(Obj);
		
		mapTables.Add(Index, Obj);
	}
	LoadCounter++;
}

TArray<FSoftObjectPath> UDDTableManager::GetTableSofPaths(const FString& _BaseTablePath, const UEnum* _pEnum) const
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//AssetRegistryModule.Get().ScanPathsSynchronous({TablePath});

	FARFilter Filter;
	Filter.PackagePaths.Add(FName(_BaseTablePath));
	Filter.ClassPaths.Add(UDataTable::StaticClass()->GetClassPathName());

	TArray<FAssetData> arrAssetData;
	AssetRegistryModule.Get().GetAssets(Filter, arrAssetData);
	
	TArray<FSoftObjectPath> ResultPath;

	for (int32 i = 0; i < arrAssetData.Num(); ++i)
	{
		FString AssetName = FPaths::GetBaseFilename(arrAssetData[i].AssetName.ToString());
		const int64 Index = _pEnum->GetIndexByName(FName(AssetName));
		if (Index == INDEX_NONE) // Enum 값과 테이블 이름 일치 체크
		{
			UE_LOG(LogTemp, Error, TEXT("%hs Table AssetName is Wrong %s"), __FUNCTION__, *AssetName)
			continue;
		}
		
		ResultPath.Emplace(arrAssetData[i].GetSoftObjectPath());
	}

	return ResultPath;
}
