// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Controller/MP_SlidingController.h"

#include "EnhancedInputComponent.h"
#include "MiniProject3/Public/Gameplay/MP_SlidingComponent.h"


UMP_SlidingController::UMP_SlidingController()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMP_SlidingController::SetupInputComponentSliding(TObjectPtr<UInputComponent> InputComponent, APawn* InPawn)
{
    if (IsValid(InPawn))
        SlidingComponent = InPawn->FindComponentByClass<UMP_SlidingComponent>();

    // The player need to have an AC_SlidingComponent
    if (!ensure(SlidingComponent.IsValid())) return;

    
    if (!InputComponent) return;

    auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    if (!EnhancedInputComponent) return;

    // You need to put an input in the AC_SlidingController !!
    if (InputActionSliding)
    {
        EnhancedInputComponent->BindAction(InputActionSliding, ETriggerEvent::Started, this, &UMP_SlidingController::StartSliding);
        EnhancedInputComponent->BindAction(InputActionSliding, ETriggerEvent::Completed, this, &UMP_SlidingController::StopSliding);
    }
}

void UMP_SlidingController::StartSliding(const FInputActionValue& Value)
{
    if (ensure(SlidingComponent.IsValid()))
        SlidingComponent->StartSliding();
}

void UMP_SlidingController::StopSliding(const FInputActionValue& Value)
{
    if (ensure(SlidingComponent.IsValid()))
        SlidingComponent->StopSliding();
}
