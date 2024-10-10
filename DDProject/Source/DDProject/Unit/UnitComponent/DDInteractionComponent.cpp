#include "DDInteractionComponent.h"

#include "DDMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "DDProject/Unit/DDPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

namespace InteractComp
{
	const float TraceDistance = 100.f;
}

UDDInteractionComponent::UDDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDDInteractionComponent::OnRegister()
{
	Super::OnRegister();
}

void UDDInteractionComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UDDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//---------------------------------------------------------------------------------------------

void UDDInteractionComponent::Move(const FVector2D& _Input)
{
	ADDPlayer* Owner = Cast<ADDPlayer>(GetOwner());
	if (!IsValid(Owner))
		return;

	if (bClimbable)
	{
		Owner->AddMovementInput(Owner->GetActorUpVector(), _Input.Y);
		Owner->AddMovementInput(Owner->GetActorRightVector(), _Input.X);
	}
	else
	{
		const FRotator Rotation = Owner->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		Owner->AddMovementInput(ForwardDirection, _Input.Y);
		Owner->AddMovementInput(RightDirection, _Input.X);
	}
}

void UDDInteractionComponent::Jump()
{
	ADDPlayer* Owner = Cast<ADDPlayer>(GetOwner());
	if (!IsValid(Owner))
		return;
		
	bool PrevState = bClimbable;
	FVector Temp;
	bClimbable = Cast<UDDMovementComponent>(Owner->GetMovementComponent())->DetectWall(Temp);

	if(PrevState && bClimbable)
	{
		ClimbStopJump(Owner);
	}
	else if(!PrevState && bClimbable)
	{
		Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
		Owner->GetCharacterMovement()->SetMovementMode(MOVE_Custom);
	}
	else if(PrevState && !bClimbable)
	{
		Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
		Owner->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
	else
	{
		if (Owner->CanJump() && !Owner->GetCharacterMovement()->IsFalling())
		{
			Owner->Jump();
		}
	}
}

void UDDInteractionComponent::Look(const FVector2D& _Input) const
{
	ADDPlayer* Owner = Cast<ADDPlayer>(GetOwner());
	if (!IsValid(Owner))
		return;

	const float Sensitivity = 0.5f;

	Owner->AddControllerYawInput(_Input.X * Sensitivity);

	const float MinPitch = -80.0f;
	const float MaxPitch = 80.0f;
	const float NewPitch = FMath::Clamp(_Input.Y * Sensitivity, MinPitch, MaxPitch);

	Owner->AddControllerPitchInput(NewPitch);
}

//---------------------------------------------------------------------------------------------

void UDDInteractionComponent::ClimbStopJump(ADDPlayer* Owner)
{
	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
	bClimbable = false;
}

//---------------------------------------------------------------------------------------------
