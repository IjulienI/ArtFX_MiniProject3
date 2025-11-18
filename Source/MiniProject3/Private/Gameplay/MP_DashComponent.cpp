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

}

void UMP_DashComponent::OnDashInputPressed()
{
	if (!Character.IsValid() || DashDataAsset == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("It's work"));

	//dash logic
}

