#include "DDPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

ADDPlayerController::ADDPlayerController()
{
	const FString Path = TEXT("InputMappingContext'/Game/Input/MyInputMappingContext.MyInputMappingContext'";
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCFinder(*Path));
	if (IMCFinder.Succeeded())
	{
		MappingContext = IMCFinder.Object;
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

void ADDPlayerController::BindingInputAction(UInputComponent* _InputComponent) const
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(_InputComponent))
	{
		for(const UInputAction* InputAction : InputActions)
		{
			if(InputAction == nullptr)
				continue;
			
			EnhancedInputComponent->BindActionValue(InputAction);
		}
	}
}
