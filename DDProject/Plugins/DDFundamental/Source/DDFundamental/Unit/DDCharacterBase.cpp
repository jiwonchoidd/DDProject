#include "DDCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADDCharacterBase::ADDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//Camera
	SpringArm_Cam = CreateDefaultSubobject<USpringArmComponent>(TEXT("SA_Cam"));
	SpringArm_Cam->SetupAttachment(RootComponent, NAME_None);
	SpringArm_Cam->TargetArmLength = 0.f;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	BaseCamera->SetupAttachment(SpringArm_Cam, NAME_None);

	BaseCamera->bUsePawnControlRotation = true;
	BaseCamera->SetFieldOfView(90.f);
}
