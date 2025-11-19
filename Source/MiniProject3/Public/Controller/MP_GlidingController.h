// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_GlidingController.generated.h"


struct FInputActionValue;
class UMP_GlidingComponent;
class UInputAction;

UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MINIPROJECT3_API UMP_GlidingController : public UActorComponent
{
    GENERATED_BODY()

public:
    UMP_GlidingController();

    void SetupInputComponentGliding(TObjectPtr<UInputComponent> InputComponent, APawn* InPawn);
    
protected:
    void StartGliding(const FInputActionValue& Value);
    void StopGliding(const FInputActionValue& Value);

    TWeakObjectPtr<UMP_GlidingComponent> GlidingComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
    TObjectPtr<UInputAction> InputActionGliding;
};
