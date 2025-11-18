// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_DashComponent.h"

UMP_DashComponent::UMP_DashComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UMP_DashComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UMP_DashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMP_DashComponent::OnDashInputPressed()
{
}

