#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DDGameModeBase.generated.h"

UCLASS()
class DDFUNDAMENTAL_API ADDGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADDGameModeBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
