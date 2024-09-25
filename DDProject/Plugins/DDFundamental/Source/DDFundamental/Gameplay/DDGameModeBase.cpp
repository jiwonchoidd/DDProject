#include "DDGameModeBase.h"

#include "DDPlayerController.h"
#include "DDFundamental/Unit/DDBaseCharacter.h"

// Sets default values
ADDGameModeBase::ADDGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

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

