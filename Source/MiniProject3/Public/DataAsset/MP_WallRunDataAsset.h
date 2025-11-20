// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MP_WallRunDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class MINIPROJECT3_API UMP_WallRunDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0", ClampMax = "100000.0"), Category = "WallRun")
	float JumpForce = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0", ClampMax = "100000.0"), Category = "WallRun")
	float MaxRunSpeedOnWall = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0", ClampMax = "1000.0"), Category = "WallRun")
	float DetectionRayWidthSize = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0", ClampMax = "1000.0"), Category = "WallRun")
	float DetectionRayZOffset = 60.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "90.0"), Category = "WallRun")
	float CharacterMeshTiltAngle = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "90.0"), Category = "WallRun")
	float JumpOfWallUpAngleDirection = 20.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1000.0"), Category = "WallRun")
	float JumpVelBeforeWallRunStop = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1000.0"), Category = "WallRun")
	float HeightBeforeWallRun = 100.0f;
};
