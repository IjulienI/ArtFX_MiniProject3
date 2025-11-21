// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MP_WallRunComponent.h"

#include "DataAsset/MP_WallRunDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/MP_BaseCharacter.h"

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

void UMP_WallRunComponent::StartJumpHeight()
{
	auto Owner = GetOwner();
	if (!Owner) return;
	auto Character = Cast<AMP_BaseCharacter>(Owner);
	if (!Character) return;
	if (Character->JumpCurrentCount == 0)
	{
		StartJumpFromGroundHeight = GetOwner()->GetActorLocation().Z;
	}
	if (Character->JumpCurrentCount == 1 && Character->CharacterMovement->Velocity.Z < 0)
	{
		BypassJumpHeight();
	}

}

void UMP_WallRunComponent::BypassJumpHeight()
{
	StartJumpFromGroundHeight = GetOwner()->GetActorLocation().Z - WallRunDataAsset->HeightBeforeWallRun;
}

void UMP_WallRunComponent::ResetJumpCount()
{
	auto Owner = GetOwner();
	if (!Owner) return;
	auto Character = Cast<AMP_BaseCharacter>(Owner);
	if (!Character) return;
	Character->ResetJumpState();
	Character->JumpCurrentCount = 0;
	Character->JumpCurrentCountPreJump = 0;
}


