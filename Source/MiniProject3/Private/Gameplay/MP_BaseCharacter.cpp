// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Gameplay/MP_BaseCharacter.h"

#include "DataAsset/MP_PlayerDataAsset.h"


AMP_BaseCharacter::AMP_BaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
    CurrentLife = PlayerDataAsset ? PlayerDataAsset->Health : 1;
}

void AMP_BaseCharacter::Jump()
{
    Super::Jump();
}

void AMP_BaseCharacter::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
}