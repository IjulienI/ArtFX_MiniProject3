// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_DashComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Gameplay/MP_BaseCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Curves/CurveFloat.h"

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
}

void UMP_DashComponent::OnDashInputPressed()
{
	if (!Character.IsValid() || DashDataAsset == nullptr || !bCanDash)
	{
		return;
	}

	// Dash cooldown Get Timer
	float TimeToDashCooldown = DashDataAsset->DashCooldown;

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(DashCooldownTimerHangle);
	TimerManager.SetTimer(DashCooldownTimerHangle, this, &UMP_DashComponent::ResetCooldown, TimeToDashCooldown, false);

	//Compute raycast
	RaycastStart = Character->GetActorLocation();
	RaycastEnd = RaycastStart + (Character->GetActorForwardVector() * DashDataAsset->DashDistance);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character.Get());
	FHitResult HitResult;

	//Lauch raycast
	const bool bHit = GetWorld()->SweepSingleByChannel(HitResult, RaycastStart, RaycastEnd, FQuat::Identity, DashCollisionChannel, FCollisionShape::MakeCapsule({ 1,1,1 }), Params);
		
	if(bHit)
	{
		RaycastEnd = HitResult.ImpactPoint;
	}

	ActualDashTime = 0;
	bCanDash = false;
}

void UMP_DashComponent::ResetCooldown()
{
	bCanDash = true;

	//Clear Timer
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(DashCooldownTimerHangle);
}

void UMP_DashComponent::ActualiseDashTimeline()
{
	ActualDashTime += GetWorld()->GetDeltaSeconds();

	if (DashDataAsset->bUseSpeedCurve && DashDataAsset->DashSpeedCurve != nullptr && ActualDashTime * DashDataAsset->DashPlayRate < 1)
	{		
		// Dash whith speed curve
		float alfa = DashDataAsset->DashSpeedCurve->GetFloatValue(ActualDashTime * DashDataAsset->DashPlayRate / 1);
		Character->SetActorLocation(FVector{ FMath::Lerp(RaycastStart.X, RaycastEnd.X, alfa)
											,FMath::Lerp(RaycastStart.Y, RaycastEnd.Y, alfa)
											,FMath::Lerp(RaycastStart.Z, RaycastEnd.Z, alfa) });
	}
	else if (ActualDashTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed) < 1)
	{
		// Dash whith linear speed 
		float alfa = ActualDashTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed);
		Character->SetActorLocation(FVector{ FMath::Lerp(RaycastStart.X, RaycastEnd.X, alfa)
											,FMath::Lerp(RaycastStart.Y, RaycastEnd.Y, alfa)
											,FMath::Lerp(RaycastStart.Z, RaycastEnd.Z, alfa) });
	}
}