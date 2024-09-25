#pragma once
#include "CoreMinimal.h"
#include "DDFundamental/Unit/DDUnitBase.h"
#include "DDPlayerUnit.generated.h"

UCLASS()
class DDPROJECT_API UDDPlayerUnit : public UDDUnitBase
{
	GENERATED_BODY()

private:
	virtual bool CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command) override;
	virtual bool DestroyUnit() override;
private:
	// TODO : 상태, 스킬 등 독립적인 유닛 관련 컴포넌트 제작
	TObjectPtr<class UDDInteractionController> InteractController = nullptr;
};
