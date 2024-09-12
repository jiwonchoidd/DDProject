// Fill out your copyright notice in the Description page of Project Settings.


#include "DDTableManager.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "DDFundamental/Gameplay/DDFunctionLibrary.h"

namespace TableMng
{
	FString BaseTablePath = TEXT("/Game/Table");
}

void UDDTableManager::Initialize()
{
	mapTables.Reset();
	LoadCounter = 0;

	LoadDataTable();
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

// --------------------------------------------------------------------------------

void UDDTableManager::LoadDataTable()
{
	TArray<FSoftObjectPath> Paths = GetTablePaths();
	UDDFunctionLibrary::AsyncLoadAsset(Paths, [this, Paths]
	{
		OnLoadComplete(Paths);
	});
}

// --------------------------------------------------------------------------------

void UDDTableManager::OnLoadComplete(const TArray<FSoftObjectPath>& _LoadedSof)
{
	const UEnum* Enum = StaticEnum<ETableDataType>();
	for(auto Sof : _LoadedSof)
	{
		FString AssetName = FPaths::GetBaseFilename(Sof.GetAssetName());
		
		const int64 Index = Enum->GetIndexByName(FName(AssetName));
		if (Index == INDEX_NONE)
		{
			continue;
		}

		UDataTable* Obj = Cast<UDataTable>(Sof.ResolveObject());

		check(Obj);
		
		mapTables.Add(static_cast<ETableDataType>(Index), Obj);
	}
	LoadCounter++;
}

TArray<FSoftObjectPath> UDDTableManager::GetTablePaths() const
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//AssetRegistryModule.Get().ScanPathsSynchronous({TablePath});

	FARFilter Filter;
	Filter.PackagePaths.Add(FName(TableMng::BaseTablePath));
	Filter.ClassPaths.Add(UDataTable::StaticClass()->GetClassPathName());

	TArray<FAssetData> arrAssetData;
	AssetRegistryModule.Get().GetAssets(Filter, arrAssetData);

	TArray<FSoftObjectPath> ResultPath;
	for (int32 i = 0; i < arrAssetData.Num(); ++i)
	{
		ResultPath.Emplace(FSoftObjectPath(arrAssetData[i].GetSoftObjectPath()));
	}

	return ResultPath;
}
