#include "DD_CharacterBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "Kismet/GameplayStatics.h"


ADD_CharacterBase::ADD_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADD_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void ADD_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADD_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

void ADD_CharacterBase::Equip(const FInputActionValue& _Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Input %s"), *_Value.ToString()));
}

