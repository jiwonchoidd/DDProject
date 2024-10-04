// Fill out your copyright notice in the Description page of Project Settings.
#include "DDSceneBase.h"

#include "DDFundamental/Manangers/DDSceneManager.h"
#include "DDFundamental/Manangers/DDUnitManager.h"

void UDDSceneBase::Begin()
{
	Super::Begin();

	LoadingProcessFuncs.Unbind();
	LoadingProcessFuncs.BindUObject(this, &UDDSceneBase::LoadingProcess);
}

void UDDSceneBase::Tick(float _fDeltaTime)
{
	Super::Tick(_fDeltaTime);
}

void UDDSceneBase::Exit()
{
	Super::Exit();
}

void UDDSceneBase::TickLoading(float _fDelta)
{
	if(LoadingProcessFuncs.IsBound())
	{
		if(LoadingProcessFuncs.Execute(_fDelta))
		{
			LoadingProcessFuncs.Unbind();
		}
	}
}

bool UDDSceneBase::IsCompleteLoading() const
{
	return !LoadingProcessFuncs.IsBound();
}

bool UDDSceneBase::OpenLevel(const FName& _LevelPath) const
{
	gUnitMng.ClearAllUnit();
	return gSceneMng.OpenLevel(_LevelPath);
}
