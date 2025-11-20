#include "Gameplay/MP_RespawnComponent.h"

UMP_RespawnComponent::UMP_RespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMP_RespawnComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentRespawnTransform = GetOwner()->GetActorTransform();
}

void UMP_RespawnComponent::SetRespawnPoint(const FTransform& Transform)
{
	CurrentRespawnTransform = Transform;
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Red,  FString::Printf(TEXT("Transform : %f, %f, %f"), CurrentRespawnTransform.GetLocation().X, CurrentRespawnTransform.GetLocation().Y, CurrentRespawnTransform.GetLocation().Z));
}



