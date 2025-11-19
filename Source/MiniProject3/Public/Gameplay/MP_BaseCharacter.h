// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MP_BaseCharacter.generated.h"

class UMP_GlidingComponent;

UCLASS()
class MINIPROJECT3_API AMP_BaseCharacter : public ACharacter
{
    GENERATED_BODY()
    
protected:
    virtual void BeginPlay() override;
    
public:
    AMP_BaseCharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Data Asset")
    TObjectPtr<class UMP_PlayerDataAsset> PlayerDataAsset{nullptr};

    TObjectPtr<UCharacterMovementComponent> CharacterMovement{nullptr};
    
    virtual void Jump() override;
    virtual void Landed(const FHitResult& Hit) override;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Player")
    int CurrentLife = 1;
    virtual void BeginPlay() override;

    // References
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
    TObjectPtr<UMP_GlidingComponent> GlidingComponent;
    
    int JumpCount = 0;
    UPROPERTY(EditDefaultsOnly)
    int NewMaxJumpCount = 2;
};
