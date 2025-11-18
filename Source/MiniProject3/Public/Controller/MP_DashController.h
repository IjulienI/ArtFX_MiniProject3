// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_DashController.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIPROJECT3_API UMP_DashController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMP_DashController();
	void SetupInputComponentDash(TObjectPtr<class UInputComponent> InputComponent, class APawn* InPawn);

protected:
	TWeakObjectPtr<class UMP_DashComponent> DashComponent = nullptr;

	//Inputs
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input");
	TObjectPtr<UInputAction> InputActionDash = nullptr;

protected:
	void StartDashPlayer();
	//End of inputs
		
};
