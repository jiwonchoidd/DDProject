// Fill out your copyright notice in the Description page of Project Settings.


#include "DDCameraActor.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADDCameraActor::ADDCameraActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SA_Cam"));
	SpringArm->SetupAttachment(RootComponent);


	SpringArm->TargetArmLength = 500.f;

	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 25.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	BaseCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	BaseCamera->SetupAttachment(SpringArm);
	BaseCamera->SetFieldOfView(90.f);
	BaseCamera->bConstrainAspectRatio = true;
	BaseCamera->AspectRatio = 1.777778f;
}

void ADDCameraActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADDCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

