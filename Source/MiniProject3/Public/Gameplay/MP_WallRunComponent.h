// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MP_WallRunComponent.generated.h"


class UMP_WallRunDataAsset;
class UMP_PlayerDataAsset;

UCLASS( Abstract, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINIPROJECT3_API UMP_WallRunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMP_WallRunComponent();

	// overrides
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// jump of wall
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void JumpOfWall();
	void StartJumpHeight();

	UFUNCTION(BlueprintCallable)
	void BypassJumpHeight();
	
	UFUNCTION(BlueprintCallable)
	void ResetJumpCount();

	// data Asset
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wall Run|Data Asset")
	TObjectPtr<UMP_WallRunDataAsset> WallRunDataAsset{nullptr};
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wall Run|Data Asset")
	TObjectPtr<UMP_PlayerDataAsset> PlayerDataAsset{nullptr};

	// wall run
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wall Run")
	float CharacterPitchCurrentTilt = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wall Run")
	float StartJumpFromGroundHeight = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wall Run")
	bool bHasHitWall = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wall Run")
	FHitResult HitWall;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wall Run")
	bool bCanCheck = true;
};
