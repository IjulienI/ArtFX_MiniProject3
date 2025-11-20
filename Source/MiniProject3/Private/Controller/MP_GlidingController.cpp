// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MP_GlidingController.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/MP_GlidingComponent.h"


UMP_GlidingController::UMP_GlidingController()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMP_GlidingController::SetupInputComponentGliding(TObjectPtr<UInputComponent> InputComponent, APawn* InPawn)
{
    if (!IsValid(InPawn)) return;

    GlidingComponent = InPawn->FindComponentByClass<UMP_GlidingComponent>();
    CharacterMovementComponent = InPawn->FindComponentByClass<UCharacterMovementComponent>();

    // The player need to have an AC_GlidingComponent
    if (!GlidingComponent.IsValid()) return;

    
    if (!InputComponent) return;

    auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

    if (!EnhancedInputComponent) return;

    // You need to put an input in the AC_GlidingController !!
    if (InputActionGliding)
    {
        EnhancedInputComponent->BindAction(InputActionGliding, ETriggerEvent::Started, this, &UMP_GlidingController::StartGliding);
        EnhancedInputComponent->BindAction(InputActionGliding, ETriggerEvent::Completed, this, &UMP_GlidingController::StopGliding);
    }
    if (InputActionJump)
    {
        EnhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Started, this, &UMP_GlidingController::StartJump);
    }
}

void UMP_GlidingController::StartGliding()
{
    if (GlidingComponent.IsValid())
        GlidingComponent->StartGliding();
}

void UMP_GlidingController::StopGliding()
{
    if (GlidingComponent.IsValid())
        GlidingComponent->StopGliding();
}

void UMP_GlidingController::StartJump()
{
    if (!GlidingComponent.IsValid()) return;

    if (CharacterMovementComponent.IsValid() && !CharacterMovementComponent->IsFalling())
        GlidingComponent->SetHasJump(true);
}
