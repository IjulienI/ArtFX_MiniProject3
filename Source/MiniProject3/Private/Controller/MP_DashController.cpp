// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MP_DashController.h"
#include "GameFramework/PlayerController.h"

// Inputs
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

//Gameplay
#include "Gameplay/MP_DashComponent.h"

UMP_DashController::UMP_DashController()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMP_DashController::SetupInputComponentDash(TObjectPtr<class UInputComponent> InputComponent, APawn* InPawn)
{
	if (InPawn)
	{
		DashComponent = InPawn->FindComponentByClass<UMP_DashComponent>();
	}

	if (!InputComponent)
	{
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (!EnhancedInputComponent)
	{
		return;
	}

	if (InputActionDash)
	{
		EnhancedInputComponent->BindAction(InputActionDash, ETriggerEvent::Started, this, &UMP_DashController::StartDashPlayer);
	}
}

void UMP_DashController::StartDashPlayer()
{
	if (DashComponent.IsValid())
	{
		DashComponent->OnDashInputPressed();
	}
}


