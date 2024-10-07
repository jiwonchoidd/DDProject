#include "DDInteractionComponent.h"

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

	ACharacter* OwnCharacter = Cast<ACharacter>(GetOwner());
	if (!IsValid(OwnCharacter))
		return;
	
	OwnCharacter->GetCharacterMovement()->MaxFlySpeed = 120.f;
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

FHitResult UDDInteractionComponent::TraceSingleLine(const FVector& _Start, const FVector& _End) const
{
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(
		this, _Start, _End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true
	);

	return HitResult;
}

FHitResult UDDInteractionComponent::TraceSphereSingle(const FVector& _Start, const FVector& _End,
                                                      float _Radius, AActor* _IgnoreActor) const
{
	TArray<AActor*> IgnoreActors;
	if(_IgnoreActor)
	{
		IgnoreActors.Emplace(_IgnoreActor);
	}
	
	FHitResult HitResult;
	UKismetSystemLibrary::SphereTraceSingle(
		this, _Start, _End, _Radius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		IgnoreActors,
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true
	);

	return HitResult;
}

FHitResult UDDInteractionComponent::TraceCapsuleSingle(const FVector& _Start, const FVector& _End, float _Radius,
	float _Height) const
{
	FHitResult HitResult;
	UKismetSystemLibrary::CapsuleTraceSingle(
		this, _Start, _End, _Radius, _Height,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true
	);

	return HitResult;
}

bool UDDInteractionComponent::QueryDetectWall()
{
	ACharacter* OwnCharacter = Cast<ACharacter>(GetOwner());
	if (!IsValid(OwnCharacter))
		return false;

	UCapsuleComponent* CapsuleComponent = OwnCharacter->FindComponentByClass<UCapsuleComponent>();
	if (!IsValid(CapsuleComponent))
		return false;

	FVector CapsuleLoc = CapsuleComponent->GetComponentLocation();

	// 1. 앞쪽 오브젝트 검사
	float CapRadius = CapsuleComponent->GetScaledCapsuleRadius();

	TArray<FVector> Directions;
	const FVector ForwardDir = CapsuleComponent->GetForwardVector();
	const FVector LeftDir = FVector::CrossProduct(FVector::UpVector, ForwardDir).GetSafeNormal();
	const FVector RightDir = FVector::CrossProduct(ForwardDir, FVector::UpVector).GetSafeNormal();
	Directions.Emplace(FVector(0,0,0));
	Directions.Emplace(LeftDir);
	Directions.Emplace(RightDir);
	
	for(int32 i = 0; i < Directions.Num(); i++)
	{
		FVector StartV = CapsuleLoc + Directions[i] * CapRadius; 
		FHitResult Result = TraceSingleLine( StartV, StartV + ForwardDir * InteractComp::TraceDistance);

		if(!Result.bBlockingHit)
			return false;

		WallHits[i] = Result;
	}

	//2. 붙잡을 수 있는지 검사
	FVector WallNormal = WallHits[0].Normal;
#if WITH_EDITOR
	DrawDebugLine(GetWorld(), WallHits[0].Location, WallHits[0].Location + WallNormal * 100.f, FColor::Black, false);
#endif
	if (FMath::Abs(WallNormal.Z) > 0.5f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wall Normal is negative"));
		return false;
	}
	
	return true;	
}

void UDDInteractionComponent::ClimbStopJump(ADDPlayer* Owner)
{
	FVector JumpDirection = Owner->GetActorForwardVector() * -1.5f + FVector(0, 0, 100);
	Owner->LaunchCharacter(JumpDirection, true, true);

	// Climbable 해제 및 회전 방향 설정
	bClimbable = false;
	Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void UDDInteractionComponent::Move(const FVector2D& _Input)
{
	ADDPlayer* Owner = Cast<ADDPlayer>(GetOwner());
	if (!IsValid(Owner))
		return;

	if(bClimbable)
	{
		if(QueryDetectWall())
		{
			FRotator WallRotation = WallHits[0].Normal.Rotation();

			const FVector UpDirection = FVector(0, 0, 1);
			const FVector RightDirection = FRotationMatrix(WallRotation).GetUnitAxis(EAxis::Y);

			// 입력에 따라 캐릭터를 이동
			Owner->AddMovementInput(UpDirection, _Input.Y); // 위아래 이동
			Owner->AddMovementInput(RightDirection, _Input.X); // 좌우 이동
		}
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
	if (!IsValid(Owner) || !Owner->CanJump() || Owner->GetCharacterMovement()->IsFalling())
		return;

	if (bClimbable)
	{
		ClimbStopJump(Owner);
		return;
	}

	Owner->Jump();
	bClimbable = QueryDetectWall();

	if(bClimbable)
	{
		UCapsuleComponent* CapsuleComponent = Owner->GetCapsuleComponent();
		FRotator Rot = UKismetMathLibrary::MakeRotFromX(WallHits[0].Normal * -1.0f);
		FVector Pos = WallHits[0].Normal * CapsuleComponent->GetScaledCapsuleRadius() + WallHits[0].Normal;
		CapsuleComponent->MoveComponent(Pos,Rot,false);
		
		Owner->GetCharacterMovement()->bOrientRotationToMovement = false;
		Owner->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
	else
	{
		Owner->GetCharacterMovement()->bOrientRotationToMovement = true;
		Owner->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
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
