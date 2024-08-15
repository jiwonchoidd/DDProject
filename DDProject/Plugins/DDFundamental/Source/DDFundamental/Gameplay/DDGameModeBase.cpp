#include "DDGameModeBase.h"

#include "DDPlayerController.h"
#include "DDFundamental/Unit/DD_CharacterBase.h"

// Sets default values
ADDGameModeBase::ADDGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = ADD_CharacterBase::StaticClass();
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

