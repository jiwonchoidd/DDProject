// Fill out your copyright notice in the Description page of Project Settings.


#include "DDDefaultUnit.h"

bool UDDDefaultUnit::CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command)
{
	const bool bCreate = Super::CreateUnit(_Handle, _Command);

	return bCreate;
}
