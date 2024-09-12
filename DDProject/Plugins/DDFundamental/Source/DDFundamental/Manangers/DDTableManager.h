// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "UObject/Object.h"
#include "DDTableManager.generated.h"

UENUM()
enum class ETableDataType : uint8
{
	UnitResource = 0,
};

UCLASS()
class DDFUNDAMENTAL_API UDDTableManager : public UObject, public DDSingleton<UDDTableManager>
{
	GENERATED_BODY()

protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;

public:
	void	LoadDataTable();
private:
	void OnLoadComplete(const TArray<FSoftObjectPath>& _LoadedSof);
	TArray<FSoftObjectPath> GetTablePaths() const;
	
private:
	UPROPERTY()
	TMap<ETableDataType, class UDataTable*> mapTables;

	int32 LoadCounter = 0;
};

#define gTable (*UDDTableManager::GetInstance())