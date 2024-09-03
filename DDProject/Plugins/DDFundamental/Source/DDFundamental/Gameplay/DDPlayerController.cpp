#include "DDPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "DDFundamental/Unit/DDCharacterBase.h"
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

	APawn* OwnerPawn = GetPawn();
	if(!IsValid(OwnerPawn))
		return;
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	OwnerPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
	OwnerPawn->AddMovementInput(RightDirection, MovementVector.X);
}

void ADDPlayerController::BaseLook(const FInputActionValue& _Value)
{
	const FVector2D& LookAxisVector = _Value.Get<FVector2D>();

	APawn* OwnerPawn = GetPawn();
	if(!IsValid(OwnerPawn))
		return;
	
	OwnerPawn->AddControllerYawInput(LookAxisVector.X);
	OwnerPawn->AddControllerPitchInput(LookAxisVector.Y);
}

void ADDPlayerController::BaseJump(const FInputActionValue& _Value)
{
	//const bool& Jump = _Value.Get<bool>();
	ACharacter* OwnerPawn = GetCharacter();
	if(!IsValid(OwnerPawn))
		return;

	if(!OwnerPawn->CanJump())
		return;

	OwnerPawn->Jump();
}

void ADDPlayerController::BaseAiming(const FInputActionValue& _Value)
{
	ADDCharacterBase* BaseChar = Cast<ADDCharacterBase>(GetCharacter());

	if(!IsValid(BaseChar))
		return;

	BaseChar->TryAiming();
}

void ADDPlayerController::BaseAttack(const FInputActionValue& _Value)
{
	ADDCharacterBase* BaseChar = Cast<ADDCharacterBase>(GetCharacter());

	if(!IsValid(BaseChar))
		return;

	BaseChar->TryAttack();
}
