// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_RespawnComponent.generated.h"


UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIPROJECT3_API UMP_RespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMP_RespawnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void Respawn();
	void SetRespawnPoint(const FTransform& Transform);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Respawn")
	FTransform CurrentRespawnTransform;
};
