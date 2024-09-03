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
	//Camera
	SpringArm_Cam = CreateDefaultSubobject<USpringArmComponent>(TEXT("SA_Cam"));
	SpringArm_Cam->SetupAttachment(RootComponent, NAME_None);
	SpringArm_Cam->TargetArmLength = 500.f;

	SpringArm_Cam->bEnableCameraRotationLag = true;
	SpringArm_Cam->CameraRotationLagSpeed = 25.f;
	SpringArm_Cam->bUsePawnControlRotation = true;
	SpringArm_Cam->bInheritPitch = true;
	SpringArm_Cam->bInheritYaw = true;
	SpringArm_Cam->bInheritRoll = true;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	BaseCamera->SetupAttachment(SpringArm_Cam, NAME_None);
	BaseCamera->SetFieldOfView(90.f);

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
