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
    
public:
    AMP_BaseCharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player|Data Asset")
    TObjectPtr<class UMP_PlayerDataAsset> PlayerDataAsset{nullptr};

    TObjectPtr<UCharacterMovementComponent> CharacterMovement{nullptr};
	
    virtual void Jump() override;
    virtual void Landed(const FHitResult& Hit) override;

    
    UFUNCTION(BlueprintCallable)
    void StartCoyoteTimer();
	
    UFUNCTION(BlueprintCallable)
    void DisableCoyoteTime();
	
    UPROPERTY()
    bool bCanCoyoteJump = false;
	
    UPROPERTY(EditAnywhere)
    float CoyoteTime = 0.3f;

    UPROPERTY(EditAnywhere)
    FTimerHandle CoyoteTimerHandle;
	
    virtual bool CanJumpInternal_Implementation() const override;
    virtual void Falling() override;
    virtual void OnJumped_Implementation() override;
    virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

protected:
    UPROPERTY(BlueprintReadWrite, Category = "Player")
    int CurrentLife = 1;
    virtual void BeginPlay() override;

    // References
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
    TObjectPtr<UMP_GlidingComponent> GlidingComponent;
    
    int JumpCount = 0;
    UPROPERTY(EditDefaultsOnly)
    int NewMaxJumpCount = 2;
};
