#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_DeathZone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathZoneEnter);

UCLASS(Abstract)
class MINIPROJECT3_API AMP_DeathZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AMP_DeathZone(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxComponent { nullptr };

public:
	FOnDeathZoneEnter OnDeathZoneEnter;
	
protected:
	UFUNCTION()
	void OnDeathZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector BoxExtents = FVector(100,100,100);
};
