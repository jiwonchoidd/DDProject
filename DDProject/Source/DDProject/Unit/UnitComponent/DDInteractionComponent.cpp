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

void UDDInteractionComponent::StartParkour() const
{
	AActor* Owner = GetOwner();
	if (!IsValid(Owner))
		return;

	UCapsuleComponent* CapsuleComponent = Owner->FindComponentByClass<UCapsuleComponent>();
	if (!IsValid(CapsuleComponent))
		return;

	constexpr float TraceDistance = 40.0f;
	constexpr float ParkourMaxDistance = 60.0f;
	FVector CapsuleLoc = CapsuleComponent->GetComponentLocation();

	// 1. 머리 위 오브젝트 검사
	FVector HeadPos = CapsuleLoc + FVector(0, 0, CapsuleComponent->GetScaledCapsuleHalfHeight());
	FVector HeadSafety = HeadPos + FVector(0, 0, ParkourMaxDistance); // 슈퍼마리오 X
	FHitResult UpperTest = TraceSphereSingle(HeadPos, HeadSafety, CapsuleComponent->GetScaledCapsuleRadius());
	if (UpperTest.bBlockingHit)
		return;
	
	// 2. 앞쪽 오브젝트 검사
	FVector TraceOffset = CapsuleComponent->GetForwardVector() * TraceDistance;

	FVector FrontStart = CapsuleLoc + TraceOffset;
	FVector FrontEnd = FrontStart + FVector(0, 0, ParkourMaxDistance);;
	
	FHitResult WallTest = TraceSphereSingle(FrontStart, FrontEnd, CapsuleComponent->GetScaledCapsuleRadius());
	AActor* TestedWall = WallTest.GetActor();
	if (!IsValid(TestedWall))
		return;
	
	// 3. 감지된 오브젝트 위에서 설 수 있는 지 판단
	FVector WallLoc = WallTest.ImpactPoint + TraceOffset;
	FVector TopLoc = FVector(WallLoc.X, WallLoc.Y, HeadSafety.Z);

	FHitResult LedgeTest = TraceSingleLine(TopLoc, WallLoc);
	if (!LedgeTest.bBlockingHit)
		return;

	FVector GroundNormal = LedgeTest.Normal;
	if (FVector::DotProduct(GroundNormal, FVector(0, 0, 1)) < 0.7f)
	{
		// 평평하지 않음!
		return;
	}

	// 4. 올라설 오브젝트에 이외 다른 오브젝트가 있는지 탐색
	FHitResult CanStepOnTest = TraceSphereSingle(LedgeTest.ImpactPoint,
		LedgeTest.ImpactPoint, CapsuleComponent->GetScaledCapsuleRadius(), TestedWall);

	if (CanStepOnTest.bBlockingHit)
		return;

	
#if WITH_EDITOR
	DrawDebugPoint(GetWorld(), LedgeTest.Location, 24.f, FColor::Blue, false);
#endif
}
