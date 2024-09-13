// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "UObject/Object.h"
#include "DDTableManager.generated.h"

UCLASS()
class DDFUNDAMENTAL_API UDDTableManager : public UObject, public DDSingleton<UDDTableManager>
{
	GENERATED_BODY()

protected:
	virtual void Initialize() override;
	virtual void Finalize() override;

public:
	void LoadDataTable(const FString& _BaseTablePath, const UEnum* _pEnum, bool _bAsyncLoad = false);
	
	template <class FRowData, typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	const FRowData* GetRowData(T _Enum, int32 _RowId);
	
	FORCEINLINE int32 GetLoadCounter() const { return LoadCounter; }
private:
	void OnLoadComplete(const UEnum* _pEnum, const TArray<FSoftObjectPath>& _LoadedSof);
	TArray<FSoftObjectPath> GetTableSofPaths(const FString& _BaseTablePath, const UEnum* _pEnum) const;

private:
	UPROPERTY()
	TMap<uint8, class UDataTable*> mapTables;

	int32 LoadCounter = 0;
};

template <class FRowData, typename T, typename>
const FRowData* UDDTableManager::GetRowData(T _Enum, int32 _RowId)
{
	static_assert(std::is_base_of_v<FTableRowBase, FRowData>, "FRowData must inherit from FTableRowBase");

	const uint8 Index = static_cast<uint8>(_Enum);

	if (mapTables.Contains(Index))
	{
		const UDataTable* pTable = mapTables[Index];
		FTableRowBase* RowBase = pTable->FindRow<FTableRowBase>(FName(FString::FromInt(_RowId)), TEXT("GENERAL"));
		return static_cast<FRowData*>(RowBase);
	}
	return nullptr;
}

#define gTableMng (*UDDTableManager::GetInstance())
