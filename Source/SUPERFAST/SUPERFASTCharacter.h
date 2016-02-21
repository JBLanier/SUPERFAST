// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PaperCharacter.h"
#include "SUPERFASTCharacter.generated.h"

// This class is the default character for SUPERFAST, and it is responsible for all
// physical interaction between the player and the world.
//
//   The capsule component (inherited from ACharacter) handles collision with the world
//   The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
//   The Sprite component (inherited from APaperCharacter) handles the visuals

class UTextRenderComponent;

UCLASS(config = Game)
class ASUPERFASTCharacter : public APaperCharacter
{
	GENERATED_BODY()

		/** Side view camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;
protected:
	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// The animation to play while beginning a jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* BeginJumpAnimation;

	// The animation to play while following though a jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* FollowThroughJumpAnimation;

	//The animation to play while performing a slide
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* SlideAnimation;

	//The animation to play while performing a wall-slide
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* WallSlideAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		bool isInWallSlideVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		bool mayDoubleJump;

	/** Called to choose the correct animation to play based on the character's movement state */
	void UpdateAnimation();

	/** Called for side to side input */
	void MoveRight(float Value);

	virtual void Jump() override;

	void startSliding();
	void stopSliding();

	void startWallSliding(int32 direction);
	void stopWallSliding();

	//Not Implemented Yet ///////
	void startGrappling();
	void stopGrappling();

	void useItem();
	////////////////

	void UpdateCharacter();

	
	UFUNCTION(/*custom parameters*/)
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(/*custom parameters*/)
		void OnBeginOverlap(AActor* OtherActor);

	UFUNCTION(/*custom parameters*/)
		void OnEndOverlap(AActor* OtherActor);

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	UPROPERTY(Replicated)
		// 0: not wallsliding 1: wall on left 2: wall on right
		int8 wallSlideBit;

	ASUPERFASTCharacter(const class FObjectInitializer& ObjectInitializer);
	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual bool CanJumpInternal_Implementation() const override;

	/** Trigger jump if jump button has been pressed. */
	//virtual void CheckJumpInput(float DeltaTime);
};
