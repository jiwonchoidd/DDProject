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
	void				LoadDataTable(const UEnum* _pEnum);
	template <typename T, typename = typename TEnableIf<TIsEnum<T>::Value>::Type>
	class UDataTable*	GetTableData(T _Enum);
	
	FORCEINLINE int32	GetLoadCounter() const { return LoadCounter; }
private:
	void					OnLoadComplete(const UEnum* _pEnum, const TArray<FSoftObjectPath>& _LoadedSof);
	TArray<FSoftObjectPath> GetTableSofPaths(const UEnum* _pEnum) const;
	
private:
	UPROPERTY()
	TMap<uint8, class UDataTable*> mapTables;

	int32 LoadCounter = 0;
};

#define gTable (*UDDTableManager::GetInstance())
