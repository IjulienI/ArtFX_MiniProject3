// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_GlidingComponent.generated.h"


class UCharacterMovementComponent;
class UMP_GlideDataAsset;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIPROJECT3_API UMP_GlidingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMP_GlidingComponent();

    void StartGliding();
    void StopGliding();

    // Getter
    UFUNCTION(BlueprintCallable, Category="Sliding")
    bool GetIsGliding();

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void OnGliding();

    // Functions
    //------------------------------------------------------------------------------------------

    UFUNCTION()
    void OnReachJumpApex();

    // Variables
    //------------------------------------------------------------------------------------------

    // VISIBLE SETTINGS ------------------------------------------------------------------------

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    UMP_GlideDataAsset* GlidingDataAsset = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    UForceFeedbackEffect* ForceFeedbackEffect = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Glide")
    bool bIsGliding = false;

    // HIDDEN SETTINGS ------------------------------------------------------------------------
    
    //References
    UPROPERTY(BlueprintReadOnly, Category="Glide")
    TWeakObjectPtr<ACharacter> Character;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    TWeakObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    float PreviousGravityScale = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    float PreviousAirControl = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    FRotator PreviousRotationRate = FRotator::ZeroRotator;

private:
    bool bHasJump = false;
};
