#include "DDCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
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
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SA_Cam"));
	SpringArm->SetupAttachment(RootComponent, NAME_None);
	SpringArm->TargetArmLength = 500.f;

	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 25.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	BaseCamera->SetupAttachment(SpringArm, NAME_None);
	BaseCamera->SetFieldOfView(90.f);
}

void ADDCharacterBase::Initialize(UObject* _CreatedObject)
{
	SourceObject = _CreatedObject;
}

void ADDCharacterBase::Finalize()
{
	SourceObject.Reset();
}