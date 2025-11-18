// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_WallRunController.generated.h"


UCLASS( Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIPROJECT3_API UMP_WallRunController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMP_WallRunController();

	// setup
public:
	void SetupInputComponentGravityGun(TObjectPtr<class UInputComponent> InputComponent, class APawn* InPawn);

	// overrides
protected:
	virtual void BeginPlay() override;

	// wall run component
protected:
	TWeakObjectPtr<class UMP_WallRunComponent> WallRunComponent{ nullptr };
	
	// inputs
protected:
	UPROPERTY(EditDefaultsOnly, Category = "WallRun|Enhanced Input")
	TObjectPtr<class UInputAction> InputActionJumpOfWall{ nullptr };

protected:
	void JumpOfWall();
};
