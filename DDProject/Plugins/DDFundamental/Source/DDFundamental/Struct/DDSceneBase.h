#pragma once
#pragma once
#include "CoreMinimal.h"
#include "DDStateBase.h"
#include "DDSceneBase.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FDDLoadingProcessFunc, float);

UCLASS()
class DDFUNDAMENTAL_API UDDSceneBase : public UDDStateBase
{
	GENERATED_BODY()
	
public:
	virtual void Begin() override;
	virtual void Tick(float _fDeltaTime) override;
	virtual void Exit() override;

	void TickLoading(float _fDelta);
	bool IsCompleteLoading() const;

	/**
	 @brief OpenLevel후 레벨로드 완료시 호출받는 함수 
	 */
	virtual void LevelLoadComplete() {};
	virtual void AdditionalLevel_LoadComplete() {};
protected:
	bool OpenLevel(const FName& _LevelPath) const;
	virtual bool LoadingProcess(float _fDeltaTime) { return true; }

private:
	FDDLoadingProcessFunc LoadingProcessFuncs;
};
