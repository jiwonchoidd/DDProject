#include "DDGameModeBase.h"

// Sets default values
ADDGameModeBase::ADDGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultPawnClass = nullptr;
} 

void ADDGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADDGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

