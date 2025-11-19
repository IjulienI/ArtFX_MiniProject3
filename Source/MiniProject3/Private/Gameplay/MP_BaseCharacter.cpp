// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Gameplay/MP_BaseCharacter.h"


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
    JumpCount = 0;
}