#include "DDInteractionComponent.h"

namespace InteractComp
{
	const float TraceDistance = 100.f;
}

UDDInteractionComponent::UDDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDDInteractionComponent::OnRegister()
{
	Super::OnRegister();
}

void UDDInteractionComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UDDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//---------------------------------------------------------------------------------------------

