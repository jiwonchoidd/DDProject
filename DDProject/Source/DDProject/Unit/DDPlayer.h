#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Unit/DDBaseCharacter.h"
#include "DDPlayer.generated.h"

class UDDStateMachine;

UCLASS()
class DDPROJECT_API ADDPlayer : public ADDBaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void Initialize(DDHandle _Handle) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Finalize() override;
private:
	UPROPERTY(BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent>		PlayerCamera = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent>	SpringArm = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = Interact, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDDInteractionComponent>	InteractionComp = nullptr;

	UPROPERTY()
	UDDStateMachine* State = nullptr;
public:
	ADDPlayer();
};