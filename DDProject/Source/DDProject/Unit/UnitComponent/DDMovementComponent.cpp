// Fill out your copyright notice in the Description page of Project Settings.


#include "DDMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PhysicsVolume.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

UDDMovementComponent::UDDMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDDMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}

	RestorePreAdditiveRootMotionVelocity();

	if (CustomMovementMode == 0)
	{
		if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
		{
			const float Friction = 0.5f * GetPhysicsVolume()->FluidFriction;
			CalcVelocity(deltaTime, Friction, true, BrakingDecelerationWalking);
		}

		ApplyRootMotionToVelocity(deltaTime);

		Iterations++;
		bJustTeleported = false;

		FVector OldLocation = UpdatedComponent->GetComponentLocation();

		FHitResult Hit(1.f);

		FVector Adjusted = Velocity * deltaTime;
		
		if (!Adjusted.IsNearlyZero())
		{
			uint8 DetectResult = QueryDetectWall();

			// 벽 탐지 결과로 갈 수 없는 벽 예외처리
			const bool LDetected = DetectResult & (1 << 1);
			const bool RDetected = DetectResult & (1 << 2);
			if( (!LDetected && Adjusted.Y > 0.0f) || (!RDetected && Adjusted.Y < 0.0f))
			{
				Adjusted.Y = 0.0f;
				Velocity.Y = 0.0f;
			}
			
			if(DetectResult > 0)
			{
				FVector ProjectedVelocity = FVector::VectorPlaneProject(Velocity, DetectedWallHits[0].Normal);
				FVector WallOffset = DetectedWallHits[0].Normal * -5.0f;

				FVector PlaneVelocity = ProjectedVelocity * deltaTime + WallOffset;
				// 회전 보간
				FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
				FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(DetectedWallHits[0].Normal * -1.0f);
				FRotator InterpolatedRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, deltaTime, 5.0f);
				SafeMoveUpdatedComponent(PlaneVelocity, InterpolatedRotation, true, Hit);
			}
		}

		HandleImpact(Hit, deltaTime, Adjusted);
		SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);

		if (!bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
		{
			Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
		}
	}
	else
	{
		Super::PhysCustom(deltaTime, Iterations);
	}
}

//------------------------------------------------------------------------------------------------------------

uint8 UDDMovementComponent::QueryDetectWall()
{
	uint8 DetectResult = 0;
	
	ACharacter* OwnCharacter = Cast<ACharacter>(GetOwner());
	if (IsValid(OwnCharacter))
	{
		UCapsuleComponent* CapsuleComponent = OwnCharacter->FindComponentByClass<UCapsuleComponent>();
		if (IsValid(CapsuleComponent))
		{
			FVector CapsuleLoc = CapsuleComponent->GetComponentLocation();

			// 1. 앞쪽 오브젝트 검사
			TArray<FVector> Directions;
			const FVector ForwardDir = CapsuleComponent->GetForwardVector();
			const FVector LeftDir = FVector::CrossProduct(ForwardDir, FVector::UpVector).GetSafeNormal();
			const FVector RightDir = FVector::CrossProduct(FVector::UpVector, ForwardDir).GetSafeNormal();
			
			Directions.Emplace(0,0,0);
			Directions.Emplace(LeftDir);
			Directions.Emplace(RightDir);

			float CapRadius = CapsuleComponent->GetScaledCapsuleRadius();

			EDrawDebugTrace::Type TraceDebugType = EDrawDebugTrace::None;
#if WITH_EDITOR
			TraceDebugType = EDrawDebugTrace::ForOneFrame;
#endif
			for (int32 i = 0; i < Directions.Num(); i++)
			{
				FVector StartV = CapsuleLoc + Directions[i] * CapRadius;

				FHitResult HitResult;
				UKismetSystemLibrary::LineTraceSingle(
					this, StartV, StartV + ForwardDir * 100.f,
					UEngineTypes::ConvertToTraceType(ECC_Visibility),
					false,
					TArray<AActor*>(),
					TraceDebugType,
					HitResult,
					true
				);

				//2. 붙잡을 수 있는지 검사 벽 탐지 및 노말 검사
				if (HitResult.bBlockingHit && FMath::Abs(HitResult.Normal.Z) < 0.5f)
				{
					DetectResult |= (1 << i);
				}

				DetectedWallHits[i] = HitResult;
			}
		}
	}
	return DetectResult;
}
