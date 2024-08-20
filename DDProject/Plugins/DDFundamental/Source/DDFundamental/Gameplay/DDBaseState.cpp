// Fill out your copyright notice in the Description page of Project Settings.
#include "DDBaseState.h"

void UDDBaseState::Initialize(uint8 _nIndex)
{
	StateIndex = _nIndex;
}

void UDDBaseState::Finalize()
{
	StateIndex = -1;
}

void UDDBaseState::OnBeginState()
{
	Begin();
}

void UDDBaseState::OnTickState(const float& Deltatime)
{
	Tick(Deltatime);
}

void UDDBaseState::OnExitState()
{
	Exit();
}
