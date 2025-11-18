// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Controller/MP_Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Controller/MP_WallRunController.h"
#include "Controller/MP_DashController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/MP_WallRunComponent.h"
#include "MiniProject3/Public/Gameplay/MP_BaseCharacter.h"


void AMP_Controller::SetupInputComponent()
{
    Super::SetupInputComponent();

    auto* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (!ensure(IsValid(EnhancedInputSubsystem))) return;

    EnhancedInputSubsystem->ClearAllMappings();
    EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);

    auto* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (!ensure(IsValid(EnhancedInputComponent))) return;

    // Base movements
    EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AMP_Controller::MovePlayer);
    EnhancedInputComponent->BindAction(InputActionTurn, ETriggerEvent::Triggered, this, &AMP_Controller::TurnPlayer);
    EnhancedInputComponent->BindAction(InputActionSprint, ETriggerEvent::Started, this, &AMP_Controller::StartSprintPlayer);
    EnhancedInputComponent->BindAction(InputActionSprint, ETriggerEvent::Completed, this, &AMP_Controller::StopSprintPlayer);
    EnhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Started, this, &AMP_Controller::StartJumpPlayer);
    EnhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Completed, this, &AMP_Controller::StopJumpPlayer);
}

void AMP_Controller::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    Super::SetPawn(InPawn);
    if (Character.IsValid()) return;
    
    Character = Cast<AMP_BaseCharacter>(InPawn);

    if (!ensure(Character.IsValid())) return;
    CharacterMovementComponent = Character->GetCharacterMovement();

    WallRunController = FindComponentByClass<UMP_WallRunController>();
    if (WallRunController.IsValid())
    {
        WallRunController->SetupInputComponentGravityGun(InputComponent, InPawn);
    }

    DashController = FindComponentByClass<UMP_DashController>();
    if (DashController.IsValid())
    {
        DashController->SetupInputComponentDash(InputComponent, InPawn);
    }
    // Exemple : 
    // GravityGunController = FindComponentByClass<UCC_GravityGunController>();
    // if (GravityGunController.IsValid())
    //     GravityGunController->SetupInputComponentGravityGun(InputComponent, InPawn);

}

void AMP_Controller::MovePlayer(const FInputActionValue& Value)
{
    if (!ensure(Character.IsValid())) return;

    const auto MoveValue = Value.Get<FVector2D>();
    
    if (MoveValue.X)
    {
        Character->AddMovementInput(Character->GetActorRightVector(),MoveValue.X);
    }
    if (MoveValue.Y)
    {
        Character->AddMovementInput(Character->GetActorForwardVector(),MoveValue.Y);
    }
}

void AMP_Controller::TurnPlayer(const FInputActionValue& Value)
{
    if (!ensure(Character.IsValid())) return;

    const auto TurnValue = Value.Get<FVector2D>();

    if (TurnValue.X)
    {
        Character->AddControllerYawInput(TurnValue.X);
    }
    if (TurnValue.Y)
    {
        Character->AddControllerPitchInput(-TurnValue.Y);
    }

}

void AMP_Controller::StartSprintPlayer(const FInputActionValue& Value)
{
    // Todo : Bind data asset for speed
    if (!ensure(CharacterMovementComponent.IsValid())) return;

    CharacterMovementComponent->MaxWalkSpeed = 800.0f;

}

void AMP_Controller::StopSprintPlayer(const FInputActionValue& Value)
{
    // Todo : Bind data asset for speed
    if (!ensure(CharacterMovementComponent.IsValid())) return;

    CharacterMovementComponent->MaxWalkSpeed = 600.0f;
}

void AMP_Controller::StartJumpPlayer(const FInputActionValue& Value)
{
    if (!ensure(Character.IsValid())) return;

    Character->Jump();
}

void AMP_Controller::StopJumpPlayer(const FInputActionValue& Value)
{
    if (!ensure(Character.IsValid())) return;

    Character->StopJumping();
}

void AMP_Controller::AddPitchInput(float Val)
{
    Super::AddPitchInput(Val * SensitivityY);
}

void AMP_Controller::AddYawInput(float Val)
{
    Super::AddYawInput(Val * SensitivityX);
}