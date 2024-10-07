// Fill out your copyright notice in the Description page of Project Settings.


#include "DDPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "DDFundamental/Struct/DDStateMachine.h"
#include "DDProject/GamePlay/GameDefine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UnitComponent/DDInteractionComponent.h"
#include "UnitState/PlayerClimbState.h"

// ---------------------------------------------------------------

ADDPlayer::ADDPlayer()
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
	if(Interaction)
	{
		Interaction->Look(_Input);
	}
}

void ADDPlayer::TryMove(const FVector2D& _Input)
{
	if(Interaction)
	{
		Interaction->Move(_Input);
	}
}

void ADDPlayer::TryJump()
{
	if(Interaction)
	{
		Interaction->Jump();
	}
}
