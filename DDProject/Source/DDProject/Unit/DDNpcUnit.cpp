// Fill out your copyright notice in the Description page of Project Settings.


#include "DDNpcUnit.h"

bool UDDNpcUnit::CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command)
{
	const bool bCreate = Super::CreateUnit(_Handle, _Command);
	
	return bCreate;
}

bool UDDNpcUnit::DestroyUnit()
{
	return Super::DestroyUnit();
}
