// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_DashComponent.h"

#include "CollisionDebugDrawingPublic.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Gameplay/MP_BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"
#include "GameFramework/CharacterMovementComponent.h"

UMP_DashComponent::UMP_DashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMP_DashComponent::BeginPlay()
{
	Super::BeginPlay();

	//Get Character
	Character = Cast<AMP_BaseCharacter>(GetOwner());

	//Convert collision Channel
	DashCollisionChannel = UEngineTypes::ConvertToCollisionChannel(DashTraceChannel);

}

void UMP_DashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bCanDash)
	{
		ActualiseDashTimeline();
	}

	if (bDashInAir && Character->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking) 
	{
		bDashInAir = false;
		ResetCooldown();
	}
}

void UMP_DashComponent::OnDashInputPressed()
{
	if (!Character.IsValid() || DashDataAsset == nullptr || !bCanDash)
	{
		return;
	}

	// Dash cooldown Get Timer
	float TimeToDashCooldown = DashDataAsset->DashCooldown;

	if(Character->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("Start timer"));*/
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.ClearTimer(DashCooldownTimerHangle);
		TimerManager.SetTimer(DashCooldownTimerHangle, this, &UMP_DashComponent::ResetCooldown, TimeToDashCooldown, false);
	}
	else 
	{
		bDashInAir = true;
	}

	//Compute raycast
	RaycastStart = Character->GetActorLocation();
	Character->GetCharacterMovement()->Velocity = Character->GetCharacterMovement()->Velocity * FVector(1, 1, 0);
	FVector NormalizeVelocity = Character->GetCharacterMovement()->Velocity.GetSafeNormal();
	if (NormalizeVelocity.Length() == 0) 
	{
		NormalizeVelocity = Character->GetActorForwardVector();
		Character->GetCharacterMovement()->Velocity = Character->GetActorForwardVector() * Character->GetCharacterMovement()->GetMaxSpeed();
	}
	RaycastEnd = RaycastStart + (NormalizeVelocity * FVector(1, 1, 0) * DashDataAsset->DashDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character.Get());
	FHitResult HitResult;

	const float CapsuleHeigth = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const float CapsuleRadius = Character->GetCapsuleComponent()->GetScaledCapsuleRadius() * 1.1f;

	const FCollisionShape Caspule = FCollisionShape::MakeCapsule(FVector( CapsuleRadius,CapsuleRadius,CapsuleHeigth ));

	//Lauch raycast
	const bool bHit = GetWorld()->SweepSingleByChannel(HitResult, RaycastStart, RaycastEnd, FQuat::Identity, DashCollisionChannel, Caspule, Params);

	DrawDebugCapsule(GetWorld(), RaycastStart, CapsuleHeigth, CapsuleRadius, FQuat::Identity, FColor::Red, false, 2.0f);
	if (HitResult.bBlockingHit)
	{
		DrawDebugCapsule(GetWorld(), HitResult.Location, CapsuleHeigth, CapsuleRadius, FQuat::Identity, FColor::Yellow, false, 2.0f);
	}
	DrawDebugLine(GetWorld(), RaycastStart, RaycastEnd, FColor::Black, false, 2.0f);
	DrawDebugCapsule(GetWorld(), RaycastEnd, CapsuleHeigth, CapsuleRadius, FQuat::Identity, FColor::Red, false, 2.0f);
		
	if(bHit)
	{
		RaycastEnd = HitResult.ImpactPoint;
	}

	ActualDashTime = 0;
	bCanDash = false;
	bInDash = true;
	LastVelocity = Character->GetCharacterMovement()->Velocity;
	Character->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	Character->GetCharacterMovement()->StopMovementImmediately();
}

void UMP_DashComponent::StopDash()
{
	ActualDashTime = 0;
	bDashInAir = false;
	ResetCooldown();
	Character->GetCharacterMovement()->Velocity = FVector::ZeroVector;
}

void UMP_DashComponent::ResetCooldown()
{
	bCanDash = true;

	//Clear Timer
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(DashCooldownTimerHangle);
	bInDash = false;
}

void UMP_DashComponent::ActualiseDashTimeline()
{
	ActualDashTime += GetWorld()->GetDeltaSeconds();

	if (DashDataAsset->bUseSpeedCurve && DashDataAsset->DashSpeedCurve != nullptr && ActualDashTime * DashDataAsset->DashPlayRate < 0.9)
	{		
		// Dash whith speed curve
		float alfa = DashDataAsset->DashSpeedCurve->GetFloatValue(ActualDashTime * DashDataAsset->DashPlayRate / 1);
		Character->SetActorLocation(FVector{ FMath::Lerp(RaycastStart.X, RaycastEnd.X, alfa)
											,FMath::Lerp(RaycastStart.Y, RaycastEnd.Y, alfa)
											,FMath::Lerp(RaycastStart.Z, RaycastEnd.Z, alfa) }, true);

		Character->GetCharacterMovement()->Velocity = LastVelocity * DashDataAsset->FallDistanceFactorAfterDash * FVector(1, 1, 0);
	}
	else if (ActualDashTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed) < 0.9)
	{
		// Dash whith linear speed 
		float alfa = ActualDashTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed);
		Character->SetActorLocation(FVector{ FMath::Lerp(RaycastStart.X, RaycastEnd.X, alfa)
											,FMath::Lerp(RaycastStart.Y, RaycastEnd.Y, alfa)
											,FMath::Lerp(RaycastStart.Z, RaycastEnd.Z, alfa) }, true);

		Character->GetCharacterMovement()->Velocity = LastVelocity * DashDataAsset->FallDistanceFactorAfterDash * FVector(1, 1, 0);
	}
	else 
	{
		bInDash = false;
	}
}