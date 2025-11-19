// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_GlidingComponent.h"

#include "DataAsset/MP_GlideDataAsset.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UMP_GlidingComponent::UMP_GlidingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
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
    if (!Character.IsValid()) return;
    
    CharacterMovementComponent = Character->GetCharacterMovement();
    
    // Bind to jump apex
    Character->OnReachedJumpApex.AddUniqueDynamic(this, &UMP_GlidingComponent::OnReachJumpApex);
    Character->LandedDelegate.AddUniqueDynamic(this, &UMP_GlidingComponent::OnLandedDelegate);
}

void UMP_GlidingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Character.IsValid())
    {
        Character->OnReachedJumpApex.RemoveDynamic(this, &UMP_GlidingComponent::OnReachJumpApex);
        Character->LandedDelegate.RemoveDynamic(this, &UMP_GlidingComponent::OnLandedDelegate);
    }    
    Super::EndPlay(EndPlayReason);
}

void UMP_GlidingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bIsGliding) return;
    if (!IsValid(GlidingDataAsset) && !CharacterMovementComponent.IsValid()) return;
    
    float TargetVelocityZ = -GlidingDataAsset->VelocityZ;
    if (CharacterMovementComponent->Velocity.Z < TargetVelocityZ)
    {
        float NewVelocityZ = FMath::FInterpTo(CharacterMovementComponent->Velocity.Z, TargetVelocityZ, DeltaTime, GlidingDataAsset->Deceleration);
        CharacterMovementComponent->Velocity.Z = NewVelocityZ;
        
        const FVector OwnerLocation = Character->GetActorLocation();
        FVector OwnerVelocityNormalized = CharacterMovementComponent->Velocity;
        OwnerVelocityNormalized.Normalize();
        
        //Character->GetMesh()->SetRelativeRotation(FRotationMatrix::MakeFromX(OwnerVelocityNormalized).Rotator() + FRotator(0.0f, 0.0f, -90.0f));
        
        DrawDebugDirectionalArrow(GetWorld(), OwnerLocation, OwnerVelocityNormalized * 100 + OwnerLocation, 1, FColor::Blue, false, -1);
    }
}

void UMP_GlidingComponent::OnReachJumpApex()
{
    bHasJump = false;
    if (!bAskGlide) return;
    
    OnGliding();
}

void UMP_GlidingComponent::OnLandedDelegate(const FHitResult& Hit)
{
    bHasJump = false;
}

void UMP_GlidingComponent::StartGliding()
{
    if (CharacterMovementComponent.IsValid() && !CharacterMovementComponent->IsFalling()) return;
    if (bIsGliding) return;
    
    PreviousGravityScale = CharacterMovementComponent->GravityScale;
    PreviousAirControl = CharacterMovementComponent->AirControl;
    PreviousRotationRate = CharacterMovementComponent->RotationRate;
    
    if (!bHasJump) OnGliding();

    bAskGlide = true;
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
    // Character->bUseControllerRotationYaw = false;
    // CharacterMovementComponent->bOrientRotationToMovement = true;
    Character->JumpCurrentCount = 2;

    bIsGliding = true;
    bAskGlide = false;
}

void UMP_GlidingComponent::StopGliding()
{
    bAskGlide = false;
    if (!bIsGliding) return;
    
    // Check if the CharacterMovementComponent and the GlidindDataAsset is valid.
    if (!CharacterMovementComponent.IsValid() && !IsValid(GlidingDataAsset)) return;

    CharacterMovementComponent->GravityScale = PreviousGravityScale;
    CharacterMovementComponent->AirControl = PreviousAirControl;
    CharacterMovementComponent->RotationRate = PreviousRotationRate;
    // CharacterMovementComponent->bOrientRotationToMovement = false;
    // Character->bUseControllerRotationYaw = true;
    
    bIsGliding = false;
}

bool UMP_GlidingComponent::GetIsGliding()
{
    return bIsGliding;
}

void UMP_GlidingComponent::SetHasJump(bool bInHasJump)
{
    bHasJump = bInHasJump;
}
