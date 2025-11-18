// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_SlidingComponent.generated.h"


class UMP_SlideDataAsset;
class UCharacterMovementComponent;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIPROJECT3_API UMP_SlidingComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMP_SlidingComponent();

    // Actions
    void StartSliding();
    void StopSliding();

    bool GetIsSliding();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


    // VISIBLE SETTINGS ------------------------------------------------------------------------
    
    // Traces Info
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    TEnumAsByte<ECollisionChannel> TraceCollisionChannel = ECollisionChannel::ECC_Visibility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    UMP_SlideDataAsset* SlidingDataAsset = nullptr;
    

    // HIDDEN SETTINGS -------------------------------------------------------------------------
    
    //References
    UPROPERTY(BlueprintReadOnly, Category="Slide")
    TWeakObjectPtr<ACharacter> Character;

    UPROPERTY(BlueprintReadOnly, Category="Slide")
    TWeakObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

    // Sliding Conditions
    UPROPERTY(BlueprintReadOnly, Category="Slide")
    bool bCanSlide = true;

    UPROPERTY(BlueprintReadOnly, Category="Slide")
    bool bIsSliding = false;

    UPROPERTY(BlueprintReadOnly, Category="Slide")
    bool bJustChangedState = false;

    // Sliding Values
    UPROPERTY(BlueprintReadOnly, Category="Slide")
    float TargetCapsuleHeigth = 55.0f;

    UPROPERTY(BlueprintReadOnly, Category="Slide")
    FVector Velocity = FVector::ZeroVector;

    // Cached Base Values
    UPROPERTY(BlueprintReadOnly, Category="Slide|Cached")
    float BaseCapsuleHeight = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="Slide|Cached")
    float BaseBrakingDecelerationWalking = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="Slide|Cached")
    float BaseBrakingFrictionFactor = 0.0f;
    
    // Timers
    FTimerHandle ResetCanSlideTimerHandle;
    FTimerHandle CheckSpeedTimerHandle;
    FTimerHandle CheckIfFallingTimerHandle;

private:
    void ResetCanSlide();
    void CheckSpeed();
    void CheckIfFalling();
};
