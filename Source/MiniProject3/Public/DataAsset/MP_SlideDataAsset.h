// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MP_SlideDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MINIPROJECT3_API UMP_SlideDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideForce = 800.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideCapsuleHeight = 55.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideBrakingFactor = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideTransitionSpeed = 15.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideFloorDetectionLenght = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideCooldown = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideMinimumVelocity = 300.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Slide")
    float SlideSlopeAcceleration = 1200.0f;
};
