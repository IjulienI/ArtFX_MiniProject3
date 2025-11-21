
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MP_Controller.generated.h"

class UMP_GlidingComponent;
class UMP_GlidingController;
class UMP_SlidingController;
class UMP_WallRunController;
class UMP_DashController;
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;
class UCharacterMovementComponent;
class AMP_BaseCharacter;
/**
 * 
 */
UCLASS(Abstract)
class MINIPROJECT3_API AMP_Controller : public APlayerController
{
    GENERATED_BODY()

public:
    // Movement
    virtual void AddPitchInput(float Val) override;
    virtual void AddYawInput(float Val) override;



protected:
    // Overrides
    virtual void SetupInputComponent() override;
    virtual void SetPawn(APawn* InPawn) override;

    // Movement
    void MovePlayer(const FInputActionValue& Value);
    void TurnPlayer(const FInputActionValue& Value);

    void StartSprintPlayer(const FInputActionValue& Value);
    void StopSprintPlayer();
    
    void StartJumpPlayer(const FInputActionValue& Value);
    void StopJumpPlayer(const FInputActionValue& Value);

    // Pause
    //UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void CallPauseMenu();

protected:
    // Inputs
    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputMappingContext> InputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputAction> InputActionMove;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputAction> InputActionTurn;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputAction> InputActionSprint;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputAction> InputActionJump;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputAction> InputActionPause;

    TWeakObjectPtr<AMP_BaseCharacter> Character;
    TWeakObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
    TWeakObjectPtr<UMP_SlidingController> SlidingController;
    // TWeakObjectPtr<UCC_GravityGunController> GravityGunController;
    // TWeakObjectPtr<UScoreComponentController> ScoreController;
    // TWeakObjectPtr<UCC_PickupSpawnerController> PickupSpawner;
    // TWeakObjectPtr<UCC_PickupCountController> PickupCount;
    TWeakObjectPtr<UMP_WallRunController> WallRunController;
    TWeakObjectPtr<UMP_DashController> DashController;
    TWeakObjectPtr<UMP_GlidingController> GlidingController;
    TWeakObjectPtr<UMP_GlidingComponent> GlidingComponent;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Mouse", meta = (ClampMin = 0.1f, ClampMax = 100.0f))
    float SensitivityX = 0.8f;

    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput|Mouse", meta = (ClampMin = 0.1f, ClampMax = 100.0f))
    float SensitivityY = 0.8f;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WallRun")
    FVector OverrideDirection = FVector(0);
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WallRun")
    bool bIsOnWall = false;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Asset|Wall Run")
    TObjectPtr<class UMP_WallRunDataAsset> WallRunDataAsset{nullptr};
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Data Asset|Player")
    TObjectPtr<class UMP_PlayerDataAsset> PlayerDataAsset{nullptr};

};
