// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
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

protected:

	struct FConstructorStatics
	{

		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset1;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset1;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> BeginJumpAnimationAsset1;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> FollowThroughJumpAnimationAsset1;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> SlideAnimationAsset1;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WallSlideAnimationAsset1;

		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> BeginJumpAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> FollowThroughJumpAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> SlideAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WallSlideAnimationAsset2;

		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset3;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset3;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> BeginJumpAnimationAsset3;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> FollowThroughJumpAnimationAsset3;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> SlideAnimationAsset3;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WallSlideAnimationAsset3;

		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset4;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset4;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> BeginJumpAnimationAsset4;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> FollowThroughJumpAnimationAsset4;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> SlideAnimationAsset4;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WallSlideAnimationAsset4;

		FConstructorStatics()
			: RunningAnimationAsset1(TEXT("/Game/SuperFastSprites/1/1Run_FlipBook"))
			, IdleAnimationAsset1(TEXT("/Game/SuperFastSprites/1/1Ready_FlipBook"))
			, BeginJumpAnimationAsset1(TEXT("/Game/SuperFastSprites/1/1Jump_1_FlipBook"))
			, FollowThroughJumpAnimationAsset1(TEXT("/Game/SuperFastSprites/1/1Jump_2_Flipbook"))
			, SlideAnimationAsset1(TEXT("/Game/SuperFastSprites/1/1Slide_FlipBook"))
			, WallSlideAnimationAsset1(TEXT("/Game/SuperFastSprites/1/1WallSlide_FlipBook"))

			, RunningAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Run_FlipBook"))
			, IdleAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Ready_FlipBook"))
			, BeginJumpAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Jump_1_FlipBook"))
			, FollowThroughJumpAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Jump_2_Flipbook"))
			, SlideAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Slide_FlipBook"))
			, WallSlideAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2WallSlide_FlipBook"))

			, RunningAnimationAsset3(TEXT("/Game/SuperFastSprites/3/3Run_FlipBook"))
			, IdleAnimationAsset3(TEXT("/Game/SuperFastSprites/3/3Ready_FlipBook"))
			, BeginJumpAnimationAsset3(TEXT("/Game/SuperFastSprites/3/3Jump_1_FlipBook"))
			, FollowThroughJumpAnimationAsset3(TEXT("/Game/SuperFastSprites/3/3Jump_2_Flipbook"))
			, SlideAnimationAsset3(TEXT("/Game/SuperFastSprites/3/3Slide_FlipBook"))
			, WallSlideAnimationAsset3(TEXT("/Game/SuperFastSprites/3/3WallSlide_FlipBook"))

			, RunningAnimationAsset4(TEXT("/Game/SuperFastSprites/4/4Run_FlipBook"))
			, IdleAnimationAsset4(TEXT("/Game/SuperFastSprites/4/4Ready_FlipBook"))
			, BeginJumpAnimationAsset4(TEXT("/Game/SuperFastSprites/4/4Jump_1_FlipBook"))
			, FollowThroughJumpAnimationAsset4(TEXT("/Game/SuperFastSprites/4/4Jump_2_Flipbook"))
			, SlideAnimationAsset4(TEXT("/Game/SuperFastSprites/4/4Slide_FlipBook"))
			, WallSlideAnimationAsset4(TEXT("/Game/SuperFastSprites/4/4WallSlide_FlipBook"))

		{
		}
	};

	static FConstructorStatics ConstructorStatics;

		/** Side view camera */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UTextRenderComponent* TextComponent;
	virtual void Tick(float DeltaSeconds) override;

	class UPaperFlipbook* RunningAnim1;
	class UPaperFlipbook* RunningAnim2;
	class UPaperFlipbook* RunningAnim3;
	class UPaperFlipbook* RunningAnim4;

	class UPaperFlipbook* IdleAnim1;
	class UPaperFlipbook* IdleAnim2;
	class UPaperFlipbook* IdleAnim3;
	class UPaperFlipbook* IdleAnim4;

	class UPaperFlipbook* BeginJumpAnim1;
	class UPaperFlipbook* BeginJumpAnim2;
	class UPaperFlipbook* BeginJumpAnim3;
	class UPaperFlipbook* BeginJumpAnim4;

	class UPaperFlipbook* FollowThroughJumpAnim1;
	class UPaperFlipbook* FollowThroughJumpAnim2;
	class UPaperFlipbook* FollowThroughJumpAnim3;
	class UPaperFlipbook* FollowThroughJumpAnim4;

	class UPaperFlipbook* SlideAnim1;
	class UPaperFlipbook* SlideAnim2;
	class UPaperFlipbook* SlideAnim3;
	class UPaperFlipbook* SlideAnim4;

	class UPaperFlipbook* WallSlideAnim1;
	class UPaperFlipbook* WallSlideAnim2;
	class UPaperFlipbook* WallSlideAnim3;
	class UPaperFlipbook* WallSlideAnim4;


	// The animation to play while running around
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// The animation to play while beginning a jump
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* BeginJumpAnimation;

	// The animation to play while following though a jump
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* FollowThroughJumpAnimation;

	//The animation to play while performing a slide
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* SlideAnimation;

	//The animation to play while performing a wall-slide
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UPaperFlipbook* WallSlideAnimation;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Replicated, Category = Movement)
		bool isInWallSlideVolume;



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

	// 0: not wall sliding 
	// 1: sliding with wall on left 
	// 2: sliding wall on right
	UPROPERTY(Replicated)
		int8 wallSlideBit;

	UPROPERTY(Replicated)
		bool mayDoubleJump;

	ASUPERFASTCharacter(const class FObjectInitializer& ObjectInitializer);
	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual bool CanJumpInternal_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	virtual void setUpAnimations(int32 playerIndex);

};