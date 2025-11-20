// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_GlidingComponent.generated.h"


class UNiagaraComponent;
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

    // Setter
    void SetHasJump(bool bInHasJump);

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void OnGliding();

    // Functions
    //------------------------------------------------------------------------------------------

    // Delegates
    UFUNCTION()
    void OnReachJumpApex();

    UFUNCTION()
    void OnLandedDelegate(const FHitResult& Hit);

    // Variables
    //------------------------------------------------------------------------------------------

    // VISIBLE SETTINGS ------------------------------------------------------------------------

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    UMP_GlideDataAsset* GlidingDataAsset = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    bool bDrawDebug = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide|Trace")
    TEnumAsByte<ECollisionChannel> WallRunCollisionChannel = ECollisionChannel::ECC_EngineTraceChannel1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide|Trace")
    float TraceRadius = 100.0f;
    
    // HIDDEN SETTINGS ------------------------------------------------------------------------
    
    // References
    UPROPERTY(BlueprintReadOnly, Category="Glide")
    TWeakObjectPtr<ACharacter> Character;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    TWeakObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

    // System Variables
    UPROPERTY(BlueprintReadOnly, Category="Glide")
    bool bIsGliding = false;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    UNiagaraComponent* NiagaraComponent = nullptr;

    // Owner Variables Cache
    UPROPERTY(BlueprintReadOnly, Category="Glide")
    float PreviousGravityScale = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    float PreviousAirControl = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category="Glide")
    FRotator PreviousRotationRate = FRotator::ZeroRotator;

private:
    bool DetectWallRunCollision();
    
    bool bHasJump = false;
    bool bAskGlide = false;
};
