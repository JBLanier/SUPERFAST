// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "SFCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SUPERFAST_API USFCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	enum CustomMovementModes {
		WallSliding,
		GrappleSwinging,
	};

	void USFCharacterMovementComponent::InitializeComponent() override;

	void USFCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	/**
	* Perform jump. Called by Character when a jump has been detected because Character->bPressedJump was true. Checks CanJump().
	* Note that you should usually trigger a jump through Character::Jump() instead.
	* @param	bReplayingMoves: true if this is being done as part of replaying moves on a locally controlled client after a server correction.
	* @return	True if the jump was triggered successfully.
	*/
	virtual bool DoJump(bool bReplayingMoves) override;


	/** Queue a pending launch with velocity LaunchVel. */
	//virtual void Launch(FVector const& LaunchVel) override;

	/** Handle a pending launch during an update. Returns true if the launch was triggered. */
	//virtual bool HandlePendingLaunch() override;

	/** Force this pawn to bounce off its current base, which isn't an acceptable base for it. */
	//virtual void JumpOff(AActor* MovementBaseActor) override;

	/** Set movement mode to the default based on the current physics volume. */
	//virtual void SetDefaultMovementMode() override;

	/**
	* Change movement mode.
	*
	* @param NewMovementMode	The new movement mode
	* @param NewCustomMode		The new custom sub-mode, only applicable if NewMovementMode is Custom.
	*/
	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;

protected:

	/** Called after MovementMode has changed. Base implementation does special handling for starting certain modes, then notifies the CharacterOwner. */
	//virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

public:

	// Movement functions broken out based on owner's network Role.
	// TickComponent calls the correct version based on the Role.
	// These may be called during move playback and correction during network updates.
	//

	/** Perform movement on an autonomous client */
	//virtual void PerformMovement(float DeltaTime) override;

	/**
	* Event triggered at the end of a movement update. If scoped movement updates are enabled (bEnableScopedMovementUpdates), this is within such a scope.
	* If that is not desired, bind to the CharacterOwner's OnMovementUpdated event instead, as that is triggered after the scoped movement update.
	*/
	//virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

	/** @return true if the character is allowed to crouch in the current state. By default it is allowed when walking or falling, if CanEverCrouch() is true. */
	//virtual bool CanCrouchInCurrentState() const override;

	/**
	* Checks if new capsule size fits (no encroachment), and call CharacterOwner->OnStartCrouch() if successful.
	* In general you should set bWantsToCrouch instead to have the crouch persist during movement, or just use the crouch functions on the owning Character.
	* @param	bClientSimulation	true when called when bIsCrouched is replicated to non owned clients, to update collision cylinder and offset.
	*/
	//virtual void Crouch(bool bClientSimulation = false) override;

	/**
	* Checks if default capsule size fits (no encroachment), and trigger OnEndCrouch() on the owner if successful.
	* @param	bClientSimulation	true when called when bIsCrouched is replicated to non owned clients, to update collision cylinder and offset.
	*/
	//virtual void UnCrouch(bool bClientSimulation = false) override;


	/** Handle falling movement. */
	//virtual void PhysFalling(float deltaTime, int32 Iterations) override;

	/** Check if pawn is falling */
	//virtual bool CheckFall(const FFindFloorResult& OldFloor, const FHitResult& Hit, const FVector& Delta, const FVector& OldLocation, float remainingTime, float timeTick, int32 Iterations, bool bMustJump) override;

	/** Transition from walking to falling */
	//virtual void StartFalling(int32 Iterations, float remainingTime, float timeTick, const FVector& Delta, const FVector& subLoc) override;

protected:

	/** @note Movement update functions should only be called through StartNewPhysics()*/
	//virtual void PhysWalking(float deltaTime, int32 Iterations) override;

	/** @note Movement update functions should only be called through StartNewPhysics()*/
	//virtual void PhysCustom(float deltaTime, int32 Iterations) override;

	/** Handle landing against Hit surface over remaingTime and iterations, calling SetPostLandedPhysics() and starting the new movement mode. */
	//virtual void ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations) override;

	/** Use new physics after landing. Defaults to swimming if in water, walking otherwise. */
	//virtual void SetPostLandedPhysics(const FHitResult& Hit) override;

public:

	/** Delegate when PhysicsVolume of UpdatedComponent has been changed **/
	//virtual void PhysicsVolumeChanged(class APhysicsVolume* NewVolume) override;

};