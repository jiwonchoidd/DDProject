#include "DDInteractionComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UDDInteractionComponent::UDDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDDInteractionComponent::OnRegister()
{
	Super::OnRegister();

	ACharacter* Owner = Cast<ACharacter>(GetOwner());
	if (IsValid(Owner))
	{
		JumpHeight = Owner->GetCharacterMovement()->GetMaxJumpHeight();
	}
}

void UDDInteractionComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UDDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 임시 테스트
	StartParkour();
}

/*TArray<FHitResult> UDDInteractionComponent::TraceSphere(const FVector& _Start, const FVector& _End,
                                                        float _Radius) const
{
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::SphereTraceMulti(
		this, _Start, _End, _Radius,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), // 콜리전 채널
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		HitResults,
		true
	);

	return HitResults;
}*/

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

FHitResult UDDInteractionComponent::TraceCapsule(const FVector& _Start, const FVector& _End,
                                                 const class UCapsuleComponent* CapsuleComponent) const
{
	FHitResult HitResult;
	UKismetSystemLibrary::CapsuleTraceSingle(
		this, _Start, _End, CapsuleComponent->GetScaledCapsuleRadius(), CapsuleComponent->GetScaledCapsuleHalfHeight(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true
	);

	return HitResult;
}

void UDDInteractionComponent::StartParkour()
{
	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
		return;

	UCapsuleComponent* CapsuleComponent = Owner->FindComponentByClass<UCapsuleComponent>();
	if (!IsValid(CapsuleComponent))
		return;

	FVector ActorLocV = CapsuleComponent->GetComponentLocation();
	FVector ActorForV = CapsuleComponent->GetForwardVector();

	constexpr float TraceDistance = 100.0f;
	FVector End = ActorLocV + (ActorForV * TraceDistance);

	// 1. 앞쪽 오브젝트 검사
	FHitResult WallTest = TraceCapsule(ActorLocV, End, CapsuleComponent);
	if (!WallTest.bBlockingHit)
		return;

	AActor* HitActor = WallTest.GetActor();

	if (!IsValid(HitActor))
		return;

	// 2. 가장자리 탐색
	FVector Origin, Extent;
	HitActor->GetActorBounds(true, Origin, Extent);

	const FVector TopCenter = Origin + FVector(0, 0, Extent.Z);
	const FVector NearestLedge = FVector(FMath::Clamp(ActorLocV.X, Origin.X - Extent.X, Origin.X + Extent.X),
	                                     FMath::Clamp(ActorLocV.Y, Origin.Y - Extent.Y, Origin.Y + Extent.Y),
	                                     TopCenter.Z);

#if WITH_EDITOR
	DrawDebugPoint(GetWorld(), NearestLedge, 10.f, FColor::Yellow, false);
#endif
}
