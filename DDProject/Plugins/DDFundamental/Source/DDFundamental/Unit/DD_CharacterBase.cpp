#include "DD_CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADD_CharacterBase::ADD_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	BaseCamera->SetupAttachment(RootComponent, NAME_None);
	BaseCamera->bUsePawnControlRotation = true;
	BaseCamera->SetFieldOfView(90.f);
}
