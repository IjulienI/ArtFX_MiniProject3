// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MP_GlideDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MINIPROJECT3_API UMP_GlideDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    float GravityScale = 0.4f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    float AirControl = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    FRotator RotationRate = FRotator(0.0f, 0.0f, 120.0f);
};
