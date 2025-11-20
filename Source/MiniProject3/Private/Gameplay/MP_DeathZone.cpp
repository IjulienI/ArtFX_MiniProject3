#include "Gameplay/MP_DeathZone.h"
#include "Components/BoxComponent.h"
#include "Gameplay/MP_RespawnComponent.h"

AMP_DeathZone::AMP_DeathZone(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	// Create the collision box
	BoxComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UBoxComponent>(this, TEXT("BoxComponent"));
	if (BoxComponent)
	{
		SetRootComponent(BoxComponent);
	}
}

void AMP_DeathZone::BeginPlay()
{
	Super::BeginPlay();
	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMP_DeathZone::OnDeathZoneOverlap);
	}
}

void AMP_DeathZone::OnDeathZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto RespawnComponent = OtherActor->FindComponentByClass<UMP_RespawnComponent>();
	if (!RespawnComponent)
	{
		return;
	}
	RespawnComponent->Respawn();
}


