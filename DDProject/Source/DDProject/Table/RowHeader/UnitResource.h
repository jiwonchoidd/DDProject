#pragma once
#include "UnitResource.generated.h"

USTRUCT()
struct FUnitResource : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	USkeletalMesh* Mesh = nullptr;
};