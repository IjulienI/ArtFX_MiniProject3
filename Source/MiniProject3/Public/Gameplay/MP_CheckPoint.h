// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_CheckPoint.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckPointEnter);

UCLASS(Abstract)
class MINIPROJECT3_API AMP_CheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMP_CheckPoint(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxComponent { nullptr };

public:
	FOnCheckPointEnter OnCheckPointEnter;
	
protected:
	UFUNCTION()
	void OnCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn", Meta = (MakeEditWidget = true))
	FTransform RespawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	FVector BoxExtents = FVector(100,100,100);
};
