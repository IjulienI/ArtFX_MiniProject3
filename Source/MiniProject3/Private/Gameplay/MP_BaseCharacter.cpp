// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniProject3/Public/Gameplay/MP_BaseCharacter.h"

#include "Gameplay/MP_GlidingComponent.h"

#include "DataAsset/MP_PlayerDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


void AMP_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (PlayerDataAsset)
	{
		CurrentLife = PlayerDataAsset->MaxLife;

		CharacterMovement = GetCharacterMovement(); // GetComponentByClass<UCharacterMovementComponent>();
		if (CharacterMovement)
		{
			CharacterMovement->AirControl = PlayerDataAsset->AirControl;
			CharacterMovement->AirControlBoostMultiplier = PlayerDataAsset->AirControlBoost;
			CharacterMovement->GravityScale = PlayerDataAsset->GravityScale;
			CharacterMovement->JumpZVelocity = PlayerDataAsset->JumpVelocity;
			CharacterMovement->MaxWalkSpeed = PlayerDataAsset->WalkSpeed;
			CharacterMovement->BrakingDecelerationFalling = PlayerDataAsset->FallingBreakingFriction;
		}

		auto SpringArm = GetComponentByClass<USpringArmComponent>();
		if (SpringArm)
		{
			SpringArm->TargetArmLength = PlayerDataAsset->TargetArmLengh;
			SpringArm->bEnableCameraLag = PlayerDataAsset->bCameraLag;
			SpringArm->CameraLagSpeed = PlayerDataAsset->CameraLagForce;
			SpringArm->SocketOffset = PlayerDataAsset->SocketOffset;
			SpringArm->TargetOffset = PlayerDataAsset->TargetOffset;
		}
	}
}

AMP_BaseCharacter::AMP_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMP_BaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GEngine->AddOnScreenDebugMessage(-1, 0.5, FColor::Red,
	                                 FString::Printf(TEXT("JumpCount = %d"), JumpCurrentCount));
}

void AMP_BaseCharacter::Jump()
{
	if (bCanCoyoteJump && GetCharacterMovement() && GetCharacterMovement()->IsFalling())
	{
		FVector launch = FVector(0,0, GetCharacterMovement()->JumpZVelocity);
		LaunchCharacter(launch, false, true);
		DisableCoyoteTime();
		return;
	}
	Super::Jump();
}

void AMP_BaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	if (GlidingComponent && GlidingComponent->GetIsGliding())
		GlidingComponent->StopGliding();
	JumpCount = 0;
}

void AMP_BaseCharacter::StartCoyoteTimer()
{
	bCanCoyoteJump = true;
	GetWorldTimerManager().ClearTimer(CoyoteTimerHandle);
	GetWorldTimerManager().SetTimer(
		CoyoteTimerHandle,
		this,
		&AMP_BaseCharacter::DisableCoyoteTime,
		CoyoteTime,
		false
	);
}

void AMP_BaseCharacter::DisableCoyoteTime()
{
	bCanCoyoteJump = false;
}

bool AMP_BaseCharacter::CanJumpInternal_Implementation() const
{
	if (Super::CanJumpInternal_Implementation())
		return true;

	if (bCanCoyoteJump)
	{
		return true;
	}

	return false;
}

void AMP_BaseCharacter::Falling()
{
	Super::Falling();
	StartCoyoteTimer();
}

void AMP_BaseCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	DisableCoyoteTime();
}

void AMP_BaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (PrevMovementMode == MOVE_Walking && GetCharacterMovement()->IsFalling())
	{
		StartCoyoteTimer();
	}

	if (!GetCharacterMovement()->IsFalling())
	{
		DisableCoyoteTime();
	}
}
