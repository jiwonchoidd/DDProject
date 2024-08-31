#include "DDGameInstance.h"
#include "DDProject/Manager/DDNetworkManager.h"

void UDDGameInstance::InitSingletons()
{
	Super::InitSingletons();
	Singletons.Emplace(UDDNetworkManager::MakeInstance());
}

void UDDGameInstance::ShutdownSingletons()
{
	Super::ShutdownSingletons();
	UDDNetworkManager::RemoveInstance();
}
