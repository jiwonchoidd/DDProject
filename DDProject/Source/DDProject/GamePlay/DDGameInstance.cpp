#include "DDGameInstance.h"
#include "DDProject/Manager/DDNetworkManager.h"

void UDDGameInstance::InitSingletons()
{
	Super::InitSingletons();
	Singletons.Emplace(UDDNetworkManager::MakeInstance());
}
