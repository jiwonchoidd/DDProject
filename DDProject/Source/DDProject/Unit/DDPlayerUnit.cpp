#include "DDPlayerUnit.h"

#include "UnitFunction/DDInteractionController.h"

bool UDDPlayerUnit::CreateUnit(int32 _Handle, const FDDSpawnCommand& _Command)
{
	const bool bCreate = Super::CreateUnit(_Handle, _Command);

	InteractController = NewObject<UDDInteractionController>(this);
	InteractController->AddToRoot();
	InteractController->Initialize();
	
	return bCreate;
}

bool UDDPlayerUnit::DestroyUnit()
{
	if(IsValid(InteractController))
	{
		InteractController->Finalize();
		InteractController->RemoveFromRoot();
		InteractController->MarkAsGarbage();
		InteractController = nullptr;
	}
	
	return Super::DestroyUnit();
}
