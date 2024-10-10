// Fill out your copyright notice in the Description page of Project Settings.


#include "DDMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PhysicsVolume.h"
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

    // 커스텀 이동 모드가 벽을 타는 모드인지 확인 (CustomMovementMode == 0)
    if (CustomMovementMode == 0)
    {
        FVector WallNormal = FVector::ZeroVector;

        if (DetectWall(WallNormal))
        {
            // 벽이 감지되었을 때만 움직임 처리
            if (!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity())
            {
                const float Friction = 0.5f * GetPhysicsVolume()->FluidFriction;
                CalcVelocity(deltaTime, Friction, true, MaxAcceleration);
            }

            ApplyRootMotionToVelocity(deltaTime);

            bJustTeleported = false;

            FVector OldLocation = UpdatedComponent->GetComponentLocation();
            const FVector Adjusted = Velocity * deltaTime;
            FHitResult Hit(1.f);

            SafeMoveUpdatedComponent(Adjusted, UpdatedComponent->GetComponentQuat(), true, Hit);

            if (Hit.Time < 1.f)
            {
                const FVector GravDir = FVector(0.f, 0.f, -1.f);
                const FVector VelDir = Velocity.GetSafeNormal();
                const float UpDown = GravDir | VelDir;

                bool bSteppedUp = false;
                if ((FMath::Abs(Hit.ImpactNormal.Z) < 0.2f) && (UpDown < 0.5f) && (UpDown > -0.2f) && CanStepUp(Hit))
                {
                    float stepZ = UpdatedComponent->GetComponentLocation().Z;
                    bSteppedUp = StepUp(GravDir, Adjusted * (1.f - Hit.Time), Hit);
                    if (bSteppedUp)
                    {
                        OldLocation.Z = UpdatedComponent->GetComponentLocation().Z + (OldLocation.Z - stepZ);
                    }
                }

                if (!bSteppedUp)
                {
                    HandleImpact(Hit, deltaTime, Adjusted);
                    SlideAlongSurface(Adjusted, (1.f - Hit.Time), WallNormal, Hit, true);
                }
            }
        }
        else
        {
            // 벽이 없으면 속도를 0으로 설정하여 움직임을 멈추게 함
            Velocity = FVector::ZeroVector;
        }
    }
    else
    {
        Super::PhysCustom(deltaTime, Iterations);
    }
}

bool UDDMovementComponent::DetectWall(FVector& OutWallNormal) const
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
    OutWallNormal = WallNormal;
    return true;
}
