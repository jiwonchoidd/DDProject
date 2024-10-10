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
        FHitResult WallResult;
        if (DetectWall(WallResult))
        {
            if( !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
            {
                const float Friction = 0.5f * GetPhysicsVolume()->FluidFriction;
                CalcVelocity(deltaTime, Friction, true, BrakingDecelerationWalking);
            }

            ApplyRootMotionToVelocity(deltaTime);

            Iterations++;
            bJustTeleported = false;

            FVector OldLocation = UpdatedComponent->GetComponentLocation();
            const FVector Adjusted = Velocity * deltaTime;

            FHitResult Hit(1.f);
            if(!Adjusted.IsNearlyZero())
            {
                FVector ProjectedVelocity = FVector::VectorPlaneProject(Velocity, WallResult.Normal);
                FVector WallOffset = WallResult.Normal * -5.0f;

                FVector PlaneVelocity = ProjectedVelocity * deltaTime + WallOffset;
                FRotator Rot = UKismetMathLibrary::MakeRotFromX(WallResult.Normal * -1.0f);

                SafeMoveUpdatedComponent(PlaneVelocity, Rot, true, Hit);
            }
            
            HandleImpact(Hit, deltaTime, Adjusted);
            SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
            
            if( !bJustTeleported && !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
            {
                Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
            }
        }
        else
        {
            Velocity = FVector::ZeroVector;
        }
    }
    else
    {
        Super::PhysCustom(deltaTime, Iterations);
    }
}


bool UDDMovementComponent::DetectWall(FHitResult& OutWall) const
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

    Directions.Emplace(FVector(0, 0, 0));
    Directions.Emplace(LeftDir);
    Directions.Emplace(RightDir);

    TStaticArray<FHitResult, 3> TempWallHits;
    for (int32 i = 0; i < Directions.Num(); i++)
    {
        FVector StartV = CapsuleLoc + Directions[i] * CapRadius;

        FHitResult HitResult;
        UKismetSystemLibrary::LineTraceSingle(
            this, StartV, StartV + ForwardDir * 100.f,
            UEngineTypes::ConvertToTraceType(ECC_Visibility),
            false,
            TArray<AActor*>(),
            EDrawDebugTrace::ForOneFrame,
            HitResult,
            true
        );
        
        if (!HitResult.bBlockingHit)
            return false;

        TempWallHits[i] = HitResult;
    }

    //2. 붙잡을 수 있는지 검사
    FVector WallNormal = TempWallHits[0].Normal;
#if WITH_EDITOR
    DrawDebugLine(GetWorld(), TempWallHits[0].Location, TempWallHits[0].Location + WallNormal * 100.f, FColor::Black,
                  false);
#endif
    if (FMath::Abs(WallNormal.Z) > 0.5f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Wall Normal is negative"));
        return false;
    }
    OutWall = TempWallHits[0];
    return true;
}
