#include "DDPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "DDFundamental/Unit/DDBaseCharacter.h"
#include "GameFramework/Character.h"

ADDPlayerController::ADDPlayerController()
{
	const FString IMCPath = TEXT("/Script/EnhancedInput.InputMappingContext'/DDFundamental/Control/IMC_Default.IMC_Default'";
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder(*IMCPath));
	if (IMCFinder.Succeeded())
	{
		MappingContext = IMCFinder.Object;
	}

	FString IAPath = TEXT("/Script/EnhancedInput.InputAction'/DDFundamental/Control/IA_Move.IA_Move'";
	static ConstructorHelpers::FObjectFinder<UInputAction> MoveIAFinder(*IAPath));
	if (MoveIAFinder.Succeeded())
	{
		InputMove = MoveIAFinder.Object;
	}

	IAPath = TEXT("/Script/EnhancedInput.InputAction'/DDFundamental/Control/IA_Look.IA_Look'";
	static ConstructorHelpers::FObjectFinder<UInputAction> LookIAFinder(*IAPath));
	if (LookIAFinder.Succeeded())
	{
		InputLook = LookIAFinder.Object;
	}
	
	IAPath = TEXT("/Script/EnhancedInput.InputAction'/DDFundamental/Control/IA_Jump.IA_Jump'";
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpIAFinder(*IAPath));
	if (JumpIAFinder.Succeeded())
	{
		InputJump = JumpIAFinder.Object;
	}

	IAPath = TEXT("/Script/EnhancedInput.InputAction'/DDFundamental/Control/IA_Aiming.IA_Aiming'";
	static ConstructorHelpers::FObjectFinder<UInputAction> AimIAFinder(*IAPath));
	if (AimIAFinder.Succeeded())
	{
		InputAiming = AimIAFinder.Object;
	}

	IAPath = TEXT("/Script/EnhancedInput.InputAction'/DDFundamental/Control/IA_Attack.IA_Attack'";
	static ConstructorHelpers::FObjectFinder<UInputAction> AttackIAFinder(*IAPath));
	if (AttackIAFinder.Succeeded())
	{
		InputAttack = AttackIAFinder.Object;
	}

	// OnPossess 시 자동 액터 카메라 활성화
	bAutoManageActiveCameraTarget = true;
}

void ADDPlayerController::OnPossess(APawn* _Pawn)
{
	Super::OnPossess(_Pawn);
}

void ADDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(MappingContext, 0);
	}
}

void ADDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this,
										   &ThisClass::BaseMove);
		EnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Triggered, this,
										   &ThisClass::BaseLook);
		EnhancedInputComponent->BindAction(InputJump, ETriggerEvent::Triggered, this,
										   &ThisClass::BaseJump);

		EnhancedInputComponent->BindAction(InputAiming, ETriggerEvent::Triggered, this,
										   &ThisClass::BaseAiming);
		EnhancedInputComponent->BindAction(InputAttack, ETriggerEvent::Triggered, this,
										   &ThisClass::BaseAttack);
	}
}

void ADDPlayerController::BaseMove(const FInputActionValue& _Value)
{
	const FVector2D& MovementVector = _Value.Get<FVector2D>();

	ADDBaseCharacter* BaseCharacter = Cast<ADDBaseCharacter>(GetPawn());
	if(!IsValid(BaseCharacter))
		return;

	BaseCharacter->TryMove(MovementVector);
}

void ADDPlayerController::BaseLook(const FInputActionValue& _Value)
{
	const FVector2D& LookAxisVector = _Value.Get<FVector2D>();

	ADDBaseCharacter* BaseCharacter = Cast<ADDBaseCharacter>(GetPawn());
	if(!IsValid(BaseCharacter))
		return;

	BaseCharacter->TryLook(LookAxisVector);
}

void ADDPlayerController::BaseJump(const FInputActionValue& _Value)
{
	ADDBaseCharacter* BaseCharacter = Cast<ADDBaseCharacter>(GetCharacter());
	if(!IsValid(BaseCharacter))
		return;

	BaseCharacter->TryJump();
}

void ADDPlayerController::BaseAiming(const FInputActionValue& _Value)
{
	const ADDBaseCharacter* BaseCharacter = Cast<ADDBaseCharacter>(GetCharacter());
	if(!IsValid(BaseCharacter))
		return;
	
	//BaseCharacter->GetSourceObject()->TryAiming();
}

void ADDPlayerController::BaseAttack(const FInputActionValue& _Value)
{
	const ADDBaseCharacter* BaseCharacter = Cast<ADDBaseCharacter>(GetCharacter());
	if(!IsValid(BaseCharacter))
		return;
	
	//UnitBase->TryAttack();
}
