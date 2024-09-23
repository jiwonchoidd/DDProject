#include "DDCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADDCharacterBase::ADDCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->JumpZVelocity = 200.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true; // 유닛 이동 시 회전

	//GetMesh()->SetupAttachment(SpringArm_Cam);
}

void ADDCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADDCharacterBase::TryAttack()
{
}

void ADDCharacterBase::TryAiming() const
{
}

void ADDCharacterBase::Jump()
{
	Super::Jump();
}
