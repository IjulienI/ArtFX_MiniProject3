// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_SlidingComponent.generated.h"


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

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    //References
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    TWeakObjectPtr<ACharacter> Character;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    TWeakObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

    // Sliding Conditions
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    bool bCanSlide = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    bool bIsSliding = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    bool bJustChangedState = false;

    // Sliding Values
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float TargetCapsuleHeigth = 55.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    FVector Velocity = FVector::ZeroVector;

    // Cached Base Values
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide|Cached")
    float BaseCapsuleHeight = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide|Cached")
    float BaseBrakingDecelerationWalking = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide|Cached")
    float BaseBrakingFrictionFactor = 0.0f;

    // Traces Info
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide|Trace")
    TEnumAsByte<ECollisionChannel> TraceCollisionChannel = ECollisionChannel::ECC_Visibility;
    
    // Timers
    FTimerHandle ResetCanSlideTimerHandle;
    FTimerHandle CheckSpeedTimerHandle;
    FTimerHandle CheckIfFallingTimerHandle;

private:
    void ResetCanSlide();
    void CheckSpeed();
    void CheckIfFalling();
};
