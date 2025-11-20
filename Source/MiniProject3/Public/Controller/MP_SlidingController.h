// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_SlidingController.generated.h"


struct FInputActionValue;
class UMP_SlidingComponent;
class UInputAction;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIPROJECT3_API UMP_SlidingController : public UActorComponent
{
    GENERATED_BODY()

public:
    UMP_SlidingController();

    void SetupInputComponentGravityGun(TObjectPtr<UInputComponent> InputComponent, APawn* InPawn);

protected:
    void StartSliding(const FInputActionValue& Value);
    void StopSliding(const FInputActionValue& Value);

    TWeakObjectPtr<UMP_SlidingComponent> SlidingComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputAction> InputActionSliding;

};
