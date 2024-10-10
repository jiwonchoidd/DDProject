#pragma once

#include "CoreMinimal.h"
#include "DDFundamental/Unit/DDBaseCharacter.h"
#include "DDProject/GamePlay/GameDefine.h"
#include "DDPlayer.generated.h"

enum class EPlayerMove : uint8;
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
	virtual void TryLook(const FVector2D& _Input) override;
	virtual void TryMove(const FVector2D& _Input) override;
	virtual void TryJump() override;
private:
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent>		PlayerCamera = nullptr;
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent>	SpringArm = nullptr;
	UPROPERTY(EditAnywhere, Category = Interact, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDDInteractionComponent>	Interaction = nullptr;
public:
	ADDPlayer(const FObjectInitializer& ObjectInitializer);
};