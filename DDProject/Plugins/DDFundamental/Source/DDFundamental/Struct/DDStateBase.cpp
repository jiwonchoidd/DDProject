// Fill out your copyright notice in the Description page of Project Settings.
#include "DDStateBase.h"

void UDDStateBase::Initialize(uint8 _nIndex)
{
	StateIndex = _nIndex;
}

void UDDStateBase::Finalize()
{
	StateIndex = -1;
}

void UDDStateBase::OnBeginState()
{
	Begin();
}

void UDDStateBase::OnTickState(const float& Deltatime)
{
	Tick(Deltatime);
}

void UDDStateBase::OnExitState()
{
	Exit();
}
