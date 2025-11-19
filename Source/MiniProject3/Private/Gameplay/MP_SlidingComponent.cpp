// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Gameplay/MP_SlidingComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MiniProject3/Public/DataAsset/MP_SlideDataAsset.h"


UMP_SlidingComponent::UMP_SlidingComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMP_SlidingComponent::StartSliding()
{
    //  GetWorld()->GetFirstPlayerController()->ClientStopCameraShake()
    if (!SlidingDataAsset) return;
    
    if (CharacterMovementComponent->IsFalling() && bIsSliding && !bCanSlide) return;
    bCanSlide = false;
    bIsSliding = true;
    bJustChangedState = true;
    
    CharacterMovementComponent->BrakingDecelerationWalking = 0;
    CharacterMovementComponent->BrakingFrictionFactor = SlidingDataAsset->SlideBrakingFactor;
    TargetCapsuleHeigth = SlidingDataAsset->SlideCapsuleHeight;

    const FVector OwnerForward = Character->GetActorForwardVector();
    const float OwnerVelocityLength = Character->GetVelocity().Size();
    const float ImpulseAmount = FMath::GetMappedRangeValueClamped(FVector2f(600.0f, 800.0f), FVector2f(0.0f, 1.0f), OwnerVelocityLength); // todo : 600/800 = Player speed from DataAsset
    const FVector SlidingImpulse = OwnerForward * ImpulseAmount * SlidingDataAsset->SlideForce;

    CharacterMovementComponent->AddImpulse(SlidingImpulse, true);

    Velocity = Character->GetVelocity().GetClampedToSize(0, SlidingDataAsset->SlideForce);

    auto& TimerManager = GetWorld()->GetTimerManager();
    TimerManager.SetTimer(ResetCanSlideTimerHandle, this, &UMP_SlidingComponent::ResetCanSlide, SlidingDataAsset->SlideCooldown, false);
    TimerManager.SetTimer(CheckSpeedTimerHandle, this, &UMP_SlidingComponent::CheckSpeed, 0.2f, true);
    TimerManager.SetTimer(CheckIfFallingTimerHandle, this, &UMP_SlidingComponent::CheckIfFalling, 0.1f, true);
}

void UMP_SlidingComponent::StopSliding()
{
    if (!SlidingDataAsset) return;
    
    bIsSliding = false;

    CharacterMovementComponent->BrakingDecelerationWalking = BaseBrakingDecelerationWalking;
    CharacterMovementComponent->BrakingFrictionFactor = BaseBrakingFrictionFactor;
    TargetCapsuleHeigth = BaseCapsuleHeight;

    auto& TimerManager = GetWorld()->GetTimerManager();
    
    TimerManager.ClearTimer(CheckSpeedTimerHandle);
    TimerManager.ClearTimer(CheckIfFallingTimerHandle);
}

bool UMP_SlidingComponent::GetIsSliding()
{
    return bIsSliding;
}

void UMP_SlidingComponent::BeginPlay()
{
    Super::BeginPlay();
    if (!SlidingDataAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("Sliding data asset is NULL"));
    }
    
    Character = Cast<ACharacter>(GetOwner());
    // Check if the owner is valid
    if (!ensure(Character.IsValid())) return;
    CharacterMovementComponent = Character->GetCharacterMovement();

    BaseCapsuleHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

    BaseBrakingDecelerationWalking = CharacterMovementComponent->BrakingDecelerationWalking;
    BaseBrakingFrictionFactor = CharacterMovementComponent->BrakingFrictionFactor;
}

void UMP_SlidingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!SlidingDataAsset) return;
    
    if (!bJustChangedState) return;

    const float CurrentCapsuleHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    const float NewCapsuleHeight = FMath::FInterpTo(CurrentCapsuleHeight, TargetCapsuleHeigth, DeltaTime, 15.0f);

    Character->GetCapsuleComponent()->SetCapsuleSize(Character->GetCapsuleComponent()->GetScaledCapsuleRadius(), NewCapsuleHeight);

    if (FMath::IsNearlyEqual(TargetCapsuleHeigth, SlidingDataAsset->SlideCapsuleHeight))
    {
        bJustChangedState = false;
    }
}

void UMP_SlidingComponent::ResetCanSlide()
{
    bCanSlide = true;
}

void UMP_SlidingComponent::CheckSpeed()
{
    if (!SlidingDataAsset) return;
    
    const float OwnerVelocityLength = Character->GetVelocity().Size();
    if (OwnerVelocityLength <= SlidingDataAsset->SlideMinimumVelocity) StopSliding();
}

void UMP_SlidingComponent::CheckIfFalling()
{
    if (!SlidingDataAsset) return;
    
    const FVector OwnerLocation = GetOwner()->GetActorLocation();
    const FVector OwnerUp = Character->GetActorUpVector();
    const  float FloorDetectionDistance = SlidingDataAsset->SlideFloorDetectionLenght * -1.0f;
    const FVector EndTrace = OwnerLocation + OwnerUp * FloorDetectionDistance;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    
    FHitResult Hit;
    GetWorld()->LineTraceSingleByChannel(Hit, OwnerLocation, EndTrace, TraceCollisionChannel, Params);

    #if !UE_BUILD_SHIPPING
    DrawDebugLine(GetWorld(), OwnerLocation, EndTrace, FColor::Red, false, 0.1f);

    if (Hit.GetActor())
        DrawDebugBox(GetWorld(), Hit.Location, FVector(10.0f), FColor::Orange, false, 0.1f);

    #endif
    
    if (!Hit.GetActor()) StopSliding();

    FVector HitNormal = Hit.Normal;

    const float FloorAlignment = HitNormal.Dot(FVector::UpVector);
    const float FloorAlignmentInverse = 1.0f - FloorAlignment;
    const FVector OwnerVelocity = GetOwner()->GetVelocity();
    const float VelocityAlignment = OwnerVelocity.Dot(HitNormal);

    if (FloorAlignmentInverse > 0.0f && VelocityAlignment > 0.0f)
    {
        FVector VelocityNormalized = OwnerVelocity;
        VelocityNormalized.Normalize();
        
        CharacterMovementComponent->AddImpulse(VelocityNormalized * FMath::Lerp(0.0f, SlidingDataAsset->SlideSlopeAcceleration, FloorAlignmentInverse));
    }
}
