// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MP_GlidingController.h"

#include "EnhancedInputComponent.h"
#include "Gameplay/MP_GlidingComponent.h"


UMP_GlidingController::UMP_GlidingController()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMP_GlidingController::SetupInputComponentGliding(TObjectPtr<UInputComponent> InputComponent, APawn* InPawn)
{
    if (IsValid(InPawn))
        GlidingComponent = InPawn->FindComponentByClass<UMP_GlidingComponent>();

    // The player need to have an AC_GlidingComponent
    if (!ensure(GlidingComponent.IsValid())) return;

    
    if (!InputComponent) return;

    auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    if (!EnhancedInputComponent) return;

    // You need to put an input in the AC_GlidingController !!
    if (InputActionGliding)
    {
        EnhancedInputComponent->BindAction(InputActionGliding, ETriggerEvent::Started, this, &UMP_GlidingController::StartGliding);
        EnhancedInputComponent->BindAction(InputActionGliding, ETriggerEvent::Completed, this, &UMP_GlidingController::StopGliding);
    }
}

void UMP_GlidingController::StartGliding(const FInputActionValue& Value)
{
    if (ensure(GlidingComponent.IsValid()))
        GlidingComponent->StartGliding();
}

void UMP_GlidingController::StopGliding(const FInputActionValue& Value)
{
    if (ensure(GlidingComponent.IsValid()))
        GlidingComponent->StopGliding();
}
