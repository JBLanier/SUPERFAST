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
		GrappleSwinging,
	};

	/**
	* Perform jump. Called by Character when a jump has been detected because Character->bPressedJump was true. Checks CanJump().
	* Note that you should usually trigger a jump through Character::Jump() instead.
	* @param	bReplayingMoves: true if this is being done as part of replaying moves on a locally controlled client after a server correction.
	* @return	True if the jump was triggered successfully.
	*/
	virtual bool DoJump(bool bReplayingMoves) override;

	/**
	* Checks if new capsule size fits (no encroachment), and call CharacterOwner->OnStartCrouch() if successful.
	* In general you should set bWantsToCrouch instead to have the crouch persist during movement, or just use the crouch functions on the owning Character.
	* @param	bClientSimulation	true when called when bIsCrouched is replicated to non owned clients, to update collision cylinder and offset.
	*/
	virtual void Crouch(bool bClientSimulation = false) override;

	/**
	* Checks if default capsule size fits (no encroachment), and trigger OnEndCrouch() on the owner if successful.
	* @param	bClientSimulation	true when called when bIsCrouched is replicated to non owned clients, to update collision cylinder and offset.
	*/
	virtual void UnCrouch(bool bClientSimulation = false) override;

};