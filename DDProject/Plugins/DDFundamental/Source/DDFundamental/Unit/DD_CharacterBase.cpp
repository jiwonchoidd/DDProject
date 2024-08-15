#include "DD_CharacterBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "DDFundamental/Gameplay/DDPlayerController.h"
#include "Kismet/GameplayStatics.h"


ADD_CharacterBase::ADD_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADD_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADD_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADD_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const ADDPlayerController* PlayerController = Cast<ADDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		PlayerController->BindingInputAction(PlayerInputComponent);
	}
}


