// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MP_WallRunController.h"

#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/MP_WallRunComponent.h"
#include "Kismet/GameplayStatics.h"

UMP_WallRunController::UMP_WallRunController()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMP_WallRunController::SetupInputComponentGravityGun(TObjectPtr<class UInputComponent> InputComponent,
	class APawn* InPawn)
{
	// Get the Gravity gun component
	if (InPawn)
	{
		WallRunComponent = InPawn->FindComponentByClass<UMP_WallRunComponent>();
	}
	// Cast the old InputComponent to its enhanced version
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (!EnhancedInputComponent)
	{
		return;
	}
	if (InputActionJumpOfWall)
	{
		EnhancedInputComponent->BindAction(InputActionJumpOfWall, ETriggerEvent::Triggered, this, &UMP_WallRunController::JumpOfWall);
	}
}


void UMP_WallRunController::BeginPlay()
{
	Super::BeginPlay();
}

void UMP_WallRunController::JumpOfWall()
{
	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetCharacterMovement()->IsMovingOnGround())
	{
		WallRunComponent->StartJumpHeight();
	}
	WallRunComponent->JumpOfWall();
}
