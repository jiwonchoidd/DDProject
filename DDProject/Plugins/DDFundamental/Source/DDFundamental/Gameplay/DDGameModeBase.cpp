#include "DDGameModeBase.h"

#include "DDPlayerController.h"
#include "DDFundamental/Unit/DDCharacterBase.h"

// Sets default values
ADDGameModeBase::ADDGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ADDCharacterBase::StaticClass();
	PlayerControllerClass = ADDPlayerController::StaticClass();
} 

void ADDGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADDGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

