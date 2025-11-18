// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_WallRunComponent.h"

UMP_WallRunComponent::UMP_WallRunComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMP_WallRunComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UMP_WallRunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMP_WallRunComponent::JumpOfWall()
{
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, "Jump of Wall");
}

