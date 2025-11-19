// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_GlidingComponent.h"

#include "DataAsset/MP_GlideDataAsset.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UMP_GlidingComponent::UMP_GlidingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMP_GlidingComponent::BeginPlay()
{
    Super::BeginPlay();
    if (!GlidingDataAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("Sliding data asset is NULL"));
    }
    
    Character = Cast<ACharacter>(GetOwner());
    // Check if the owner is valid
    if (!ensure(Character.IsValid())) return;
    CharacterMovementComponent = Character->GetCharacterMovement();

    // Bind to jump apex
    Character->OnReachedJumpApex.AddUniqueDynamic(this, &UMP_GlidingComponent::OnReachJumpApex);
}

void UMP_GlidingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Character.IsValid())
        Character->OnReachedJumpApex.RemoveDynamic(this, &UMP_GlidingComponent::OnReachJumpApex);
    
    Super::EndPlay(EndPlayReason);
}

void UMP_GlidingComponent::OnReachJumpApex()
{
    if (!bIsGliding) return;

    OnGliding();
}

void UMP_GlidingComponent::OnGliding()
{
    // Play force feedback if the force feedback is valid
    if (IsValid(ForceFeedbackEffect))
        GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(ForceFeedbackEffect);

    // Check if the CharacterMovementComponent and the GlidingDataAsset is valid.
    if (!CharacterMovementComponent.IsValid() && !IsValid(GlidingDataAsset)) return;

    CharacterMovementComponent->GravityScale = GlidingDataAsset->GravityScale;
    CharacterMovementComponent->AirControl = GlidingDataAsset->AirControl;
    CharacterMovementComponent->RotationRate = GlidingDataAsset->RotationRate;
    
    bIsGliding = true;
}

void UMP_GlidingComponent::StartGliding()
{
    if (bIsGliding) return;
    
    PreviousGravityScale = CharacterMovementComponent->GravityScale;
    PreviousAirControl = CharacterMovementComponent->AirControl;
    PreviousRotationRate = CharacterMovementComponent->RotationRate;
    
    bIsGliding = true;
}

void UMP_GlidingComponent::StopGliding()
{
    if (!bIsGliding) return;
    
    // Check if the CharacterMovementComponent and the GlidindDataAsset is valid.
    if (!CharacterMovementComponent.IsValid() && !IsValid(GlidingDataAsset)) return;

    CharacterMovementComponent->GravityScale = PreviousGravityScale;
    CharacterMovementComponent->AirControl = PreviousAirControl;
    CharacterMovementComponent->RotationRate = PreviousRotationRate;

    bIsGliding = false;
}

bool UMP_GlidingComponent::GetIsGliding()
{
    return bIsGliding;
}
