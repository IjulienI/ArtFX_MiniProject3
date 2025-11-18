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

	UE_LOG(LogTemp, Warning, TEXT("Dash"));

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
		UE_LOG(LogTemp, Warning, TEXT("YES"));
		RaycastEnd = HitResult.ImpactPoint;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("FALSE"));
	}
	ActualTime = 0;
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
	ActualTime += GetWorld()->GetDeltaSeconds();

	if (DashDataAsset->bUseSpeedCurve && DashDataAsset->DashSpeedCurve != nullptr)
	{
		//Character->SetActorLocation(FVector{ FMath::Lerp(0, 1, ActualTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed)),1.f,1.f });
		// Dash whith speed curve
	}
	else if (ActualTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed) < 1)
	{
		Character->SetActorLocation(FVector{ FMath::Lerp(RaycastStart.X, RaycastEnd.X, ActualTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed))
											,FMath::Lerp(RaycastStart.Y, RaycastEnd.Y, ActualTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed))
											,FMath::Lerp(RaycastStart.Z, RaycastEnd.Z, ActualTime / (DashDataAsset->DashDistance / DashDataAsset->DashLinearSpeed)) });
		// Dash whith linear speed 
	}
}

