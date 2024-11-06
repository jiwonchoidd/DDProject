// Fill out your copyright notice in the Description page of Project Settings.


#include "DDPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UnitComponent/DDInteractionComponent.h"
#include "UnitComponent/DDMovementComponent.h"

// ---------------------------------------------------------------
ADDPlayer::ADDPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDDMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	Interaction = CreateDefaultSubobject<UDDInteractionComponent>(TEXT("Interaction"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SA_Cam"));
	SpringArm->SetupAttachment(RootComponent, NAME_None);
	SpringArm->TargetArmLength = 500.f;

	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bEnableCameraLag = false;
	
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	PlayerCamera->SetupAttachment(SpringArm, NAME_None);
	PlayerCamera->SetFieldOfView(80.f);
}

void ADDPlayer::Initialize(DDHandle _Handle)
{
	Super::Initialize(_Handle);
}

void ADDPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ADDPlayer::Finalize()
{
	Super::Finalize();
}

void ADDPlayer::TryLook(const FVector2D& _Input)
{
	const float Sensitivity = 0.5f;

	AddControllerYawInput(_Input.X * Sensitivity);

	const float MinPitch = -80.0f;
	const float MaxPitch = 80.0f;
	const float NewPitch = FMath::Clamp(_Input.Y * Sensitivity, MinPitch, MaxPitch);

	AddControllerPitchInput(NewPitch);
}

void ADDPlayer::TryMove(const FVector2D& _Input)
{
	if (GetCharacterMovement()->MovementMode == MOVE_Custom)
	{
		FVector MoveDirection = GetActorUpVector() * _Input.Y + GetActorRightVector() * _Input.X;

		if (MoveDirection.IsNearlyZero())
			return;
		
		MoveDirection = MoveDirection.GetSafeNormal();
		AddMovementInput(MoveDirection, .2f);
	}
	else
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		FVector MoveDirection = ForwardDirection * _Input.Y + RightDirection * _Input.X;
		if (MoveDirection.IsNearlyZero())
			return;
		
		AddMovementInput(MoveDirection, 1.0f);
	}
}

void ADDPlayer::TryJump()
{
	UDDMovementComponent* pMovement = Cast<UDDMovementComponent>(GetCharacterMovement());
	if (!IsValid(pMovement))
		return;

	bool PrevState = pMovement->MovementMode == MOVE_Custom;
	if (pMovement->QueryDetectWall() > 0x06)
	{
		if (!PrevState)
		{
			pMovement->bOrientRotationToMovement = false;
			pMovement->SetMovementMode(MOVE_Custom);
		}
		else
		{
			pMovement->bOrientRotationToMovement = true;
			pMovement->SetMovementMode(MOVE_Walking);
		}
	}
	else
	{
		if (PrevState)
		{
			pMovement->bOrientRotationToMovement = true;
			pMovement->SetMovementMode(MOVE_Walking);
		}
		else if (CanJump() && !pMovement->IsFalling())
		{
			Jump();
		}
	}
}