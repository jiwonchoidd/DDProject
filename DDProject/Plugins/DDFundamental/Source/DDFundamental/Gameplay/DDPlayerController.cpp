// Fill out your copyright notice in the Description page of Project Settings.


#include "DDPlayerController.h"

#include "EnhancedInputSubsystems.h"

ADDPlayerController::ADDPlayerController()
{
	const ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if(IMCFinder.Succeeded())
	{
		MappingContext = IMCFinder.Object;
	}
}

void ADDPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		SubSystem->AddMappingContext(MappingContext, 0);
	}
}

void ADDPlayerController::SetupInputForPawn()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		for(const UInputAction* InputAction : InputActions)
		{
			if(InputAction == nullptr)
				continue;

			EnhancedInputComponent->BindActionValue(InputAction);
			EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::Equip);
		}
	}
}
