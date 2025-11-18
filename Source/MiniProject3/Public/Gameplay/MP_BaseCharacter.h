// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MP_BaseCharacter.generated.h"

UCLASS()
class MINIPROJECT3_API AMP_BaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMP_BaseCharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Data Asset")
    TObjectPtr<class UMP_PlayerDataAsset> PlayerDataAsset{nullptr};
};
