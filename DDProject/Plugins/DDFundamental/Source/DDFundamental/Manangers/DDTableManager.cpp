// Fill out your copyright notice in the Description page of Project Settings.


#include "DDTableManager.h"

#include "AssetRegistry/AssetRegistryModule.h"

void UDDTableManager::Initialize()
{
	
}

void UDDTableManager::Finalize()
{
	
}

TMap<ETableDataType, FString> UDDTableManager::GetTablePath() const
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	FARFilter Filter;
	Filter.PackagePaths.Add("/Game/Table");
	Filter.ClassNames.Add(UDataTable::StaticClass()->GetFName());
	//AssetRegistryModule.Get().ScanPathsSynchronous(sPackagePaths);

	TArray<FAssetData> arrAssetData;
	AssetRegistryModule.Get().GetAssets(Filter, arrAssetData);

	const UEnum* Enum = StaticEnum<ETableDataType>();
	
	TMap<ETableDataType, FString> ResultPath;
	for (int32 i = 0; i < arrAssetData.Num(); ++i)
	{
		FString AssetName = FPaths::GetBaseFilename(arrAssetData[i].AssetName.ToString());
		
		const int64 Index = Enum->GetIndexByName(FName(AssetName));
		if (Index == INDEX_NONE)
		{
			continue;
		}

		ResultPath.Emplace(static_cast<ETableDataType>(Index), arrAssetData[i].ObjectPath.ToString());
	}

	return ResultPath;
}
