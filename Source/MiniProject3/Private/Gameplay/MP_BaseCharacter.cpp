// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Gameplay/MP_BaseCharacter.h"

#include "Gameplay/MP_GlidingComponent.h"


AMP_BaseCharacter::AMP_BaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMP_BaseCharacter::Jump()
{
    if (JumpCount < NewMaxJumpCount)
    {
        Super::Jump();
        JumpCount++;
    }
}

void AMP_BaseCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    if (GlidingComponent && GlidingComponent->GetIsGliding())
        GlidingComponent->StopGliding();
    JumpCount = 0;
}

void AMP_BaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}
