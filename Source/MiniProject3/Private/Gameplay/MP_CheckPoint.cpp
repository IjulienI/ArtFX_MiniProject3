#include "Gameplay/MP_CheckPoint.h"
#include "Components/BoxComponent.h"
#include "Gameplay/MP_RespawnComponent.h"

AMP_CheckPoint::AMP_CheckPoint(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	// Create the collision box
	BoxComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UBoxComponent>(this, TEXT("BoxComponent"));
	if (BoxComponent)
	{
		SetRootComponent(BoxComponent);
	}
}

void AMP_CheckPoint::BeginPlay()
{
	Super::BeginPlay();

	if (BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMP_CheckPoint::OnCheckpointOverlap);
	}
}

void AMP_CheckPoint::OnCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto RespawnComponent = OtherActor->FindComponentByClass<UMP_RespawnComponent>();
	if (!RespawnComponent)
	{
		return;
	}
	FTransform WorldRespawnTransform = RespawnTransform * GetActorTransform();

	RespawnComponent->SetRespawnPoint(WorldRespawnTransform);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Respawn Transform : {%f, %f, %f}"), RespawnTransform.GetLocation().X, RespawnTransform.GetLocation().Y, RespawnTransform.GetLocation().Z));

}

