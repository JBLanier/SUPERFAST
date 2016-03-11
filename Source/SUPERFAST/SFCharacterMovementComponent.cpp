// Fill out your copyright notice in the Description page of Project Settings.

#include "SUPERFAST.h"
#include "UnrealNetwork.h"
#include "SFCharacterMovementComponent.h"
#include "SUPERFASTCharacter.h"

//////////////////////////////////////////////////////////////////////////
// USFCharacterMovementComponent

////////////////////////////////////////////////////////

bool USFCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	GravityScale = 5;
	
	if (CharacterOwner && CharacterOwner->CanJump())
	{
		// Don't jump if we can't move up/down.
		if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
		{
			Velocity.Z = JumpZVelocity;
			
			auto owner = Cast<ASUPERFASTCharacter>(CharacterOwner);
			if (owner && IsFalling())
			{
				owner->mayDoubleJump = false;

				if (owner->wallSlideBit == 1)
				{
					Velocity.X = JumpZVelocity * -0.7;
				}
				else if (owner->wallSlideBit == 2)
				{
					Velocity.X = JumpZVelocity * 0.7;
				}
				owner->wallSlideBit = 0;
			}

			SetMovementMode(MOVE_Falling);

			return true;
		}
	}

	return false;
}

void USFCharacterMovementComponent::Crouch(bool bClientSimulation)
{
	Super::Crouch(bClientSimulation);
	BrakingFrictionFactor = 0.07;

	if (!IsFalling() && Velocity.GetAbs().X <= 1000.0 && Velocity.GetAbs().X > 0.0) {
		Velocity.X += ((Velocity.X > 0) ? 1 : -1) * 1000.0;
	}
}

void USFCharacterMovementComponent::UnCrouch(bool bClientSimulation)
{
	Super::UnCrouch(bClientSimulation);
	BrakingFrictionFactor = 2.0;
}
