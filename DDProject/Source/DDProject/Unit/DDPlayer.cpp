// Fill out your copyright notice in the Description page of Project Settings.


#include "DDPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "DDFundamental/Struct/DDStateMachine.h"
#include "DDProject/GamePlay/GameDefine.h"
#include "GameFramework/SpringArmComponent.h"
#include "UnitComponent/DDInteractionComponent.h"
#include "UnitState/PlayerClimbState.h"

ADDPlayer::ADDPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<UDDInteractionComponent>(TEXT("Interaction"));
	InteractionComp->SetupAttachment(RootComponent);
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SA_Cam"));
	SpringArm->SetupAttachment(RootComponent, NAME_None);
	SpringArm->TargetArmLength = 500.f;

	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 25.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	PlayerCamera->SetupAttachment(SpringArm, NAME_None);
	PlayerCamera->SetFieldOfView(90.f);
}

void ADDPlayer::Initialize(DDHandle _Handle)
{
	Super::Initialize(_Handle);

	if(State == nullptr)
	{
		State = NewObject<UDDStateMachine>(this);
		State->AddToRoot();

		State->Create();
		State->AddState(EPlayerState::Default, UPlayerClimbState::StaticClass(), this);
		State->AddState(EPlayerState::Climb, UPlayerClimbState::StaticClass(), this);
	}
}

void ADDPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(State)
	{
		State->Tick(DeltaSeconds);
	}
}

void ADDPlayer::Finalize()
{
	if(State)
	{
		State->Destroy();
		State->RemoveFromRoot();
		State = nullptr;
	}
	Super::Finalize();
}
