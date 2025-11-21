// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAsset/MP_DashDataAsset.h"
#include "MP_DashComponent.generated.h"


UCLASS(Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIPROJECT3_API UMP_DashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMP_DashComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TWeakObjectPtr<class AMP_BaseCharacter> Character = nullptr;

	//Inputs
public:
	void OnDashInputPressed();
	UFUNCTION(BlueprintCallable, Category = "Dash")
	void StopDash();

public:
	UPROPERTY(BlueprintReadOnly, Category = "Dash")
	bool bInDash = false;
	//End of inputs
	
	//Collisions
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	TEnumAsByte<ETraceTypeQuery> DashTraceChannel;
	ECollisionChannel DashCollisionChannel;
	FVector RaycastStart;
	FVector FinishPose;
	FVector RaycastEnd;
	FVector LastVelocity;
	//End of collisions	

	//Data Asset
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Dash|Data Asset")
	TObjectPtr<UMP_DashDataAsset> DashDataAsset = nullptr;
	//End of Data Asset

	//Cooldown
protected:
	FTimerHandle DashCooldownTimerHangle;
	bool bCanDash = true;
	bool bDashInAir = false;
	float ActualDashTime = 0.f;

protected:
	UFUNCTION(BlueprintCallable, Category = "Dash")
	void ResetCooldown();
	void ActualiseDashTimeline();
	//End of Cooldown
};
