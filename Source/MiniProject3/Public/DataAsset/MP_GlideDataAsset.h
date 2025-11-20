// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MP_GlideDataAsset.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class MINIPROJECT3_API UMP_GlideDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide", meta = ( Units = "Seconds" ))
    float Duration = 10.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    float GravityScale = 0.4f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    float Speed = 200.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide", meta = ( ClampMin = 1.0f, ClampMax = 50.0f ))
    float Deceleration = 4.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    float AirControl = 1.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    float VelocityZ = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide", meta = ( ClampMin = 1.0f, ClampMax = 50.0f ))
    float DecelerationZ = 4.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide")
    FRotator RotationRate = FRotator(0.0f, 0.0f, 120.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide|Rumble")
    UForceFeedbackEffect* ForceFeedbackStartGlide = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide|Rumble")
    UForceFeedbackEffect* ForceFeedbackGlideLoop = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide|Effect")
    FName NiagaraComponentTag = NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide|Effect")
    FName NiagaraDurationUserParameterName = NAME_None;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Glide|Effect")
    UNiagaraSystem* NiagaraEffect = nullptr;
};
