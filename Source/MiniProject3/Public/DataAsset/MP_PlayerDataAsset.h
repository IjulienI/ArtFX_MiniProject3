
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MP_PlayerDataAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MINIPROJECT3_API UMP_PlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0", ClampMax = "1000.0"), Category = "Player|Movements")
	float JumpVelocity = 420.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "100.0"), Category = "Player|Movements")
	float AirControl = 0.05f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1000.0"), Category = "Player|Movements")
	float GravityScale = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1000.0"), Category = "Player|Movements")
	float AirControlBoost = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0", ClampMax = "2000.0"), Category = "Player|Movements")
	float RunSpeed = 800.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "10.0", ClampMax = "2000.0"), Category = "Player|Movements")
	float WalkSpeed = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "100"), Category = "Player")
	int MaxLife = 8;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "10.0"), Category = "Player|Movements")
    float FallingBreakingFriction = 600.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "100"), Category = "PickUp|Health")
	int HealthGain = 1;
};
