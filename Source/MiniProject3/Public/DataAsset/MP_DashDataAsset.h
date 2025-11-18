// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MP_DashDataAsset.generated.h"

UCLASS()
class MINIPROJECT3_API UMP_DashDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "10.0", ClampMax = "1000.0", Units = "Centimeters"))
	float DashDistance = 300.f;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.1", ClampMax = "60.0", Units = "Seconds"))
	float DashCooldown = 2.f;
	UPROPERTY(EditAnywhere, Category = "Speed")
	bool bUseSpeedCurve = false;
	UPROPERTY(EditAnywhere, Category = "Speed", meta = (EditCondition = "bUseSpeedCurve", EditConditionHides))
	TObjectPtr<class UCurveFloat> DashSpeedCurve = nullptr;
	UPROPERTY(EditAnywhere, Category = "Speed", meta = (EditCondition = "bUseSpeedCurve", EditConditionHides))
	float DashPlayRate = 1.f;
	UPROPERTY(EditAnywhere, Category = "Speed", meta = (EditCondition = "!bUseSpeedCurve", EditConditionHides, Units = "CentimetersPerSecond"))
	float DashLinearSpeed = 3000.f;
};
