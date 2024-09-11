// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Struct/DDSingleton.h"
#include "UObject/Object.h"
#include "DDTableManager.generated.h"

UENUM()
enum ETableDataType
{
	UnitTable = 0,
};

UCLASS()
class DDFUNDAMENTAL_API UDDTableManager : public UObject, public DDSingleton<UDDSceneManager>
{
	GENERATED_BODY()

protected: 
	virtual void Initialize() override;
	virtual void Finalize() override;

private:
	TMap<ETableDataType, FString> GetTablePath() const;
};
