// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Gameplay/MP_BaseCharacter.h"

#include "DataAsset/MP_PlayerDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"


void AMP_BaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (PlayerDataAsset)
    {
        CharacterMovement = GetComponentByClass<UCharacterMovementComponent>();
        if (CharacterMovement)
        {
            CharacterMovement->AirControl = PlayerDataAsset->AirControl;
            CharacterMovement->AirControlBoostMultiplier = PlayerDataAsset->AirControlBoost;
            CharacterMovement->GravityScale = PlayerDataAsset->GravityScale;
            CharacterMovement->JumpZVelocity = PlayerDataAsset->JumpVelocity;
            CharacterMovement->MaxWalkSpeed = PlayerDataAsset->WalkSpeed;
            CharacterMovement->BrakingDecelerationFalling = PlayerDataAsset->FallingBreakingFriction;
        }
    }
}

AMP_BaseCharacter::AMP_BaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMP_BaseCharacter::Jump()
{
    Super::Jump();
}

void AMP_BaseCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
}