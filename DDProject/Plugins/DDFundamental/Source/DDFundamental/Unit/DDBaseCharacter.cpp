#include "DDBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

void ADDBaseCharacter::Initialize(DDHandle _Handle)
{
	OwnHandle = _Handle; 
}

void ADDBaseCharacter::Finalize()
{
	OwnHandle = INDEX_NONE;
}

ADDBaseCharacter::ADDBaseCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->JumpZVelocity = 250.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true; // 유닛 이동 시 회전
	GetCharacterMovement()->bRunPhysicsWithNoController = true; // 컨트롤러가 없어도 중력 적용
}
