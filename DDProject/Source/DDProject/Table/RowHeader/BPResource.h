#pragma once
#include "BPResource.generated.h"

USTRUCT()
struct FBPResource : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aseet")
	TSoftObjectPtr<UBlueprint> Blueprint;
};