#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MP_BossDataAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class MINIPROJECT3_API UMP_BossDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile")
	bool bUseDirectProjectile = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile", meta = (EditCondition = "bUseDirectProjectile", EditConditionHides), meta = (ClampMin = "0.01"))
	float AttackRandomOffset = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile",  meta = (EditCondition = "bUseDirectProjectile", EditConditionHides))
	bool bShootRandomDelayOffset = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile", meta = (EditCondition = "bUseDirectProjectile && bShootRandomDelayOffset", EditConditionHides, Units = "Seconds", ClampMin = "0.0"))
	float RandomDelayOffset = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile", meta = (EditCondition = "bUseDirectProjectile", EditConditionHides, Units = "Seconds", ClampMin = "0.0"))
	float DelayBetweenProjectile = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bUseDirectProjectile", EditConditionHides))
	bool bEnableFireflies = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies")
	bool bRandomFireflyAmount = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bEnableFireflies && bUseDirectProjectile && bRandomFireflyAmount", EditConditionHides))
	int FirefliesAmountMin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bEnableFireflies && bUseDirectProjectile && bRandomFireflyAmount", EditConditionHides))
	int FirefliesAmountMax = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bEnableFireflies && bUseDirectProjectile && !bRandomFireflyAmount", EditConditionHides))
	int FirefliesAmount = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bEnableFireflies && bUseDirectProjectile", EditConditionHides, ClampMin = "0.0"))
	float FirefliesSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bEnableFireflies && bUseDirectProjectile", EditConditionHides, ClampMin = "0.0"))
	float AttackDamage = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bEnableFireflies && bUseDirectProjectile", EditConditionHides, ClampMin = "0.0"))
	float AttackDuration = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Direct Projectile|Fireflies", meta = (EditCondition = "bEnableFireflies && bUseDirectProjectile", EditConditionHides, Units = "Seconds"))
	FLinearColor FireflyColor = FLinearColor::Yellow;
};