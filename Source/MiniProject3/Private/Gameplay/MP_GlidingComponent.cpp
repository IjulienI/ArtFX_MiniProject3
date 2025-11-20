// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_GlidingComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
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

    NiagaraSceneComponent = Cast<USceneComponent>(Character->FindComponentByTag(USceneComponent::StaticClass(),
        GlidingDataAsset->NiagaraComponentTag));
    
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

    if (IsValid(GlidingDataAsset) && IsValid(GlidingDataAsset->ForceFeedbackGlideLoop))
        GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(GlidingDataAsset->ForceFeedbackGlideLoop);

    // Get Velocity and direction infos
    const FVector Velocity = CharacterMovementComponent->Velocity;
    const FVector Direction = Velocity.GetSafeNormal();
    
    float TargetVelocityZ = -GlidingDataAsset->VelocityZ;
    if (Velocity.Z < TargetVelocityZ)
    {
        float NewVelocityZ = FMath::FInterpTo(Velocity.Z, TargetVelocityZ, DeltaTime, GlidingDataAsset->DecelerationZ);
        CharacterMovementComponent->Velocity.Z = NewVelocityZ;
        
        const FVector OwnerLocation = Character->GetActorLocation();
        
        //Character->GetMesh()->SetRelativeRotation(FRotationMatrix::MakeFromX(OwnerVelocityNormalized).Rotator() + FRotator(0.0f, 0.0f, -90.0f));
        if (bDrawDebug)
            DrawDebugDirectionalArrow(GetWorld(), OwnerLocation, Direction * 100 + OwnerLocation, 1, FColor::Blue, false, -1);
    }

    // Clamp Velocity
    const FVector TargetSpeed = Direction * GlidingDataAsset->Speed;
    
    FVector NewVelocity = FMath::VInterpTo(Velocity, TargetSpeed, DeltaTime, GlidingDataAsset->DecelerationZ);
    CharacterMovementComponent->Velocity.X = NewVelocity.X;
    CharacterMovementComponent->Velocity.Y = NewVelocity.Y;

    if (DetectWallRunCollision()) StopGliding();
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
    if (bIsGliding) StopGliding();
}

void UMP_GlidingComponent::StartGliding()
{
    if (CharacterMovementComponent.IsValid() && !CharacterMovementComponent->IsFalling()) return;
    if (bIsGliding) return;

    if (DetectWallRunCollision()) return;
    
    PreviousGravityScale = CharacterMovementComponent->GravityScale;
    PreviousAirControl = CharacterMovementComponent->AirControl;
    PreviousRotationRate = CharacterMovementComponent->RotationRate;
    
    if (!bHasJump) OnGliding();

    bAskGlide = true;
}

void UMP_GlidingComponent::OnGliding()
{
    // Play force feedback if the force feedback is valid
    if (IsValid(GlidingDataAsset) && IsValid(GlidingDataAsset->ForceFeedbackStartGlide))
        GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(GlidingDataAsset->ForceFeedbackStartGlide);

    // Check if the CharacterMovementComponent and the GlidingDataAsset is valid.
    if (!CharacterMovementComponent.IsValid() && !IsValid(GlidingDataAsset)) return;
    
    CharacterMovementComponent->GravityScale = GlidingDataAsset->GravityScale;
    CharacterMovementComponent->AirControl = GlidingDataAsset->AirControl;
    CharacterMovementComponent->RotationRate = GlidingDataAsset->RotationRate;

    // ResetJump
    Character->JumpCurrentCount = 2;

    if (IsValid(GlidingDataAsset) && IsValid(GlidingDataAsset->NiagaraEffect) && !IsValid(NiagaraComponent))
    {        
        if(NiagaraSceneComponent.IsValid())
        {
            FFXSystemSpawnParameters SpawnParams;
            SpawnParams.SystemTemplate = GlidingDataAsset->NiagaraEffect;
            SpawnParams.AttachToComponent = NiagaraSceneComponent.Get();
            SpawnParams.bAutoDestroy = false;
            SpawnParams.LocationType = EAttachLocation::SnapToTarget;
            
            NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttachedWithParams(SpawnParams);
        }
    }

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

    if (NiagaraComponent)
    {
        NiagaraComponent->DeactivateImmediate();
        NiagaraComponent->DestroyComponent();
    }

    if (IsValid(GlidingDataAsset) && IsValid(GlidingDataAsset->ForceFeedbackGlideLoop))
        GetWorld()->GetFirstPlayerController()->ClientStopForceFeedback(GlidingDataAsset->ForceFeedbackGlideLoop, NAME_None);
    
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

bool UMP_GlidingComponent::DetectWallRunCollision()
{
    // Trace to detect Wall Run
    const auto* World =  GetWorld();
    
    const FVector StartTrace = GetOwner()->GetActorLocation();
    const FCollisionShape SphereShape = FCollisionShape::MakeSphere(TraceRadius);
    
    FCollisionQueryParams Params(SCENE_QUERY_STAT(TraceForwardSingle), false, GetOwner());
    Params.bReturnPhysicalMaterial = false;

    FHitResult OutHit;
    const bool bHit = World->SweepSingleByChannel(
        OutHit,
        StartTrace,
        StartTrace,
        FQuat::Identity,
        WallRunCollisionChannel,
        SphereShape,
        Params
    );

    if (bDrawDebug)
    {
        const FColor Color = bHit ? FColor::Red : FColor::Green;
        DrawDebugLine(World, StartTrace, StartTrace, Color, false, -1.0f, 0, 1.0f);
        DrawDebugSphere(World, StartTrace, TraceRadius, 12, Color, false, -1.0f);
        if (bHit)
        {
            DrawDebugSphere(World, OutHit.ImpactPoint, TraceRadius * 0.5f, 12, FColor::Yellow, false, 1.2f);
        }
    }
    return bHit;
}