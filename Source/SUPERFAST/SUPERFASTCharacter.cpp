// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SUPERFAST.h"
#include "SUPERFASTCharacter.h"
#include "PaperFlipbookComponent.h"
#include "SFCharacterMovementComponent.h"
#include "UnrealNetwork.h"
#include "Components/TextRenderComponent.h"


DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);
//////////////////////////////////////////////////////////////////////////
// ASUPERFASTCharacter


ASUPERFASTCharacter::ASUPERFASTCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<USFCharacterMovementComponent>(APaperCharacter::CharacterMovementComponentName))
{
	// Setup the assets
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

	RunningAnim1 = ConstructorStatics.RunningAnimationAsset1.Get();
	IdleAnim1 = ConstructorStatics.IdleAnimationAsset1.Get();
	BeginJumpAnim1 = ConstructorStatics.BeginJumpAnimationAsset1.Get();
	FollowThroughJumpAnim1 = ConstructorStatics.FollowThroughJumpAnimationAsset1.Get();
	SlideAnim1 = ConstructorStatics.SlideAnimationAsset1.Get();
	WallSlideAnim1 = ConstructorStatics.WallSlideAnimationAsset1.Get();

	RunningAnim2 = ConstructorStatics.RunningAnimationAsset2.Get();
	IdleAnim2 = ConstructorStatics.IdleAnimationAsset2.Get();
	BeginJumpAnim2 = ConstructorStatics.BeginJumpAnimationAsset2.Get();
	FollowThroughJumpAnim2 = ConstructorStatics.FollowThroughJumpAnimationAsset2.Get();
	SlideAnim2 = ConstructorStatics.SlideAnimationAsset2.Get();
	WallSlideAnim2 = ConstructorStatics.WallSlideAnimationAsset2.Get();

	RunningAnim3 = ConstructorStatics.RunningAnimationAsset3.Get();
	IdleAnim3 = ConstructorStatics.IdleAnimationAsset3.Get();
	BeginJumpAnim3 = ConstructorStatics.BeginJumpAnimationAsset3.Get();
	FollowThroughJumpAnim3 = ConstructorStatics.FollowThroughJumpAnimationAsset3.Get();
	SlideAnim3 = ConstructorStatics.SlideAnimationAsset3.Get();
	WallSlideAnim3 = ConstructorStatics.WallSlideAnimationAsset3.Get();
	
	RunningAnim4 = ConstructorStatics.RunningAnimationAsset4.Get();	
	IdleAnim4 = ConstructorStatics.IdleAnimationAsset4.Get();
	BeginJumpAnim4 = ConstructorStatics.BeginJumpAnimationAsset4.Get();
	FollowThroughJumpAnim4 = ConstructorStatics.FollowThroughJumpAnimationAsset4.Get();
	SlideAnim4 = ConstructorStatics.SlideAnimationAsset4.Get();
	WallSlideAnim4 = ConstructorStatics.WallSlideAnimationAsset4.Get();

	//JB - this is the end of stuff you need to do create a flipbook reference

	GetSprite()->SetFlipbook(IdleAnimation);
	GetSprite()->SetRelativeLocation(FVector(0, 0, -77));

	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(74.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);


	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 5000.0f;
	SideViewCameraComponent->bConstrainAspectRatio = true;
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 5.0f; //originally: 2.0f
	GetCharacterMovement()->AirControl = 0.80f; //originally 0.8 f
	GetCharacterMovement()->JumpZVelocity = 1500.f; //originally: 1000.0 f
	GetCharacterMovement()->GroundFriction = 2.0f; //originally 3.0 f
	GetCharacterMovement()->MaxWalkSpeed = 3200.0f; //originally 600 f
	GetCharacterMovement()->MaxWalkSpeedCrouched = 3200.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f; //originally: 600f
	GetCharacterMovement()->MaxAcceleration = 1600;
	GetCharacterMovement()->bCanWalkOffLedges = true;
	GetCharacterMovement()->bCanWalkOffLedgesWhenCrouching = true;
	GetCharacterMovement()->bMaintainHorizontalGroundVelocity = false;
	GetCharacterMovement()->JumpZVelocity = 2200.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 700.0f;
	GetCharacterMovement()->AirControl = 0.7f;
	GetCharacterMovement()->AirControlBoostMultiplier = 0.0f;
	GetCharacterMovement()->FallingLateralFriction = 0.75;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->SetWalkableFloorAngle(80.0f);

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
	// 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	// 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
	// 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	// 	TextComponent->AttachTo(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;


	//JB - everything below this point in the constructor is user created code:
	mayDoubleJump = true;

	//JB- TriggerVolumes in the level are currently used to define the space where the player should be able to wallSlide
	// The main purpose of these volumes is the define where walls VERTICALLY stop being walls.
	// For instance, when you slide off a wall and want to regain motion control, the fact that you just left the WallSlide volume allowed this.
	// If we don't use volumes to call events when the player enters and leaves them, the player will continue sliding even when they slide off a wall.
	isInWallSlideVolume = false;

	//JB - Characters send a broadcast to subscribers when these collision type events happen,
	// here I'm making the SUPERFASTCharacter subscribe to itself and define what functions it wants the broadcasts to call (OnHit, OnBeginOverlap, OnEndOverlap).
	// A whole lot of player movement state stuff is handled in OnHit(), the "on***overlap" functions currently only set whether or not the player is in a volume where they are allowed to WallSlide
	this->OnActorHit.AddDynamic(this, &ASUPERFASTCharacter::OnHit);
	this->OnActorBeginOverlap.AddDynamic(this, &ASUPERFASTCharacter::OnBeginOverlap);
	this->OnActorEndOverlap.AddDynamic(this, &ASUPERFASTCharacter::OnEndOverlap);

}

bool ASUPERFASTCharacter::CanJumpInternal_Implementation() const
{
	const bool bCanHoldToJumpHigher = (GetJumpMaxHoldTime() > 0.0f) && IsJumpProvidingForce();

	bool returnResult = (!bIsCrouched && GetCharacterMovement() && (CharacterMovement->IsMovingOnGround() || mayDoubleJump || wallSlideBit != 0 || bCanHoldToJumpHigher) && GetCharacterMovement()->IsJumpAllowed() && !CharacterMovement->bWantsToCrouch);

	return returnResult;
}

void ASUPERFASTCharacter::setUpAnimations(int32 playerIndex)
{

	switch (playerIndex % 4)
	{
		case 0:
			RunningAnimation = RunningAnim1;
			IdleAnimation = IdleAnim1;
			BeginJumpAnimation = BeginJumpAnim1;
			FollowThroughJumpAnimation = FollowThroughJumpAnim1;
			SlideAnimation = SlideAnim1;
			WallSlideAnimation = WallSlideAnim1;
			break;

		case 1:
			RunningAnimation = RunningAnim2;
			IdleAnimation = IdleAnim2;
			BeginJumpAnimation = BeginJumpAnim2;
			FollowThroughJumpAnimation = FollowThroughJumpAnim2;
			SlideAnimation = SlideAnim2;
			WallSlideAnimation = WallSlideAnim2;
			break;
		
		case 2:
			RunningAnimation = RunningAnim3;
			IdleAnimation = IdleAnim3;
			BeginJumpAnimation = BeginJumpAnim3;
			FollowThroughJumpAnimation = FollowThroughJumpAnim3;
			SlideAnimation = SlideAnim3;
			WallSlideAnimation = WallSlideAnim3;
			break;

		case 3:
			RunningAnimation = RunningAnim4;
			IdleAnimation = IdleAnim4;
			BeginJumpAnimation = BeginJumpAnim4;
			FollowThroughJumpAnimation = FollowThroughJumpAnim4;
			SlideAnimation = SlideAnim4;
			WallSlideAnimation = WallSlideAnim4;
			break;

		default:
			break;
	}

}

//////////////////////////////////////////////////////////////////////////
// Animation


//JB - direct animation changes should only happen here.
void ASUPERFASTCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeed = PlayerVelocity.Size();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation;
	if (wallSlideBit != 0) {
		DesiredAnimation = WallSlideAnimation;
	}
	else if (bIsCrouched == true) {
		DesiredAnimation = SlideAnimation;
	}
	else if (GetCharacterMovement()->IsFalling() == true) {
		DesiredAnimation = (PlayerVelocity.Z < 0) ? FollowThroughJumpAnimation : BeginJumpAnimation;
	}
	else if (GetVelocity().X != 0 && GetCharacterMovement()->MovementMode == MOVE_Walking && GetCharacterMovement()->GetCurrentAcceleration().X != 0) {
		DesiredAnimation = RunningAnimation;
	}
	else {
		DesiredAnimation = IdleAnimation;
	}

	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

//JB - this is called every single frame no matter what. If you can make something happen without calling it every frame, probably shouldn't edit this.
void ASUPERFASTCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateCharacter();
}


//////////////////////////////////////////////////////////////////////////
// Input

void ASUPERFASTCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Note: the 'Jump' action and the 'MoveRight' axis are bound to actual keys/buttons/sticks in DefaultInput.ini (editable from Project Settings..Input)
	InputComponent->BindAction("Jump", IE_Pressed, this, &ASUPERFASTCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ASUPERFASTCharacter::StopJumping);
	InputComponent->BindAction("Slide", IE_Pressed, this, &ASUPERFASTCharacter::startSliding);
	InputComponent->BindAction("Slide", IE_Released, this, &ASUPERFASTCharacter::stopSliding);
	InputComponent->BindAxis("MoveRight", this, &ASUPERFASTCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &ASUPERFASTCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ASUPERFASTCharacter::TouchStopped);
}

void ASUPERFASTCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion

	if (Value != 0 && wallSlideBit == 0 && !bIsCrouched) {
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	} else if (bIsCrouched) {
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value*0.3);
	}
}

void ASUPERFASTCharacter::Jump()
{
	Super::Jump();
}

void ASUPERFASTCharacter::startSliding()
{
	Crouch();
}

void ASUPERFASTCharacter::stopSliding()
{
	UnCrouch();
}

void ASUPERFASTCharacter::startWallSliding(int32 direction)
{
	wallSlideBit = direction;
	GetCharacterMovement()->GravityScale = 2;
}

void ASUPERFASTCharacter::stopWallSliding()
{
	wallSlideBit = 0;
	GetCharacterMovement()->GravityScale = 5;
}

void ASUPERFASTCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ASUPERFASTCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

//JB - this is called every single frame no matter what. If you can make something happen without calling it every frame, probably shouldn't edit this.
// So far nothing has had to have been added.
// animation changes are to be handled in UpdateAnimation()
void ASUPERFASTCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are traveling
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}

	
}

void ASUPERFASTCharacter::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit) {


	UE_LOG(LogTemp, Log, TEXT("COLLISION x: %f  y: %f"), Hit.Normal.X, Hit.Normal.Z);
	//UE_LOG(LogTemp, Warning, TEXT("X Velocity: %f"), GetCapsuleComponent()->ComponentVelocity.X);
	//UE_LOG(LogTemp, Warning, TEXT("Y Velocity: %f"), GetCapsuleComponent()->ComponentVelocity.Z);


	float NormalZ = Hit.Normal.Z;
	float NormalX = Hit.Normal.X;

	//JB - getting the players Capsule component's velocity because the player's velocity reads 0 for some reason when OnHit is called.
	float xVelocity = GetCapsuleComponent()->ComponentVelocity.X;
	float zVelocity = GetCapsuleComponent()->ComponentVelocity.Z;

	// Landed on flat ground
	if (NormalZ > 0.01) {
		stopWallSliding();
		mayDoubleJump = true;
	}
	// Landed on 45 degree slope
	if (Hit.Normal.GetAbs().Z - 0.707 < 0.03 && Hit.Normal.GetAbs().Z - 0.707 > -0.03) {
		stopWallSliding();
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		UE_LOG(LogTemp, Log, TEXT("45 degree"));
		if (!bIsCrouched) {
			//JB - this is the snippet that transfers falling velocity to lateral motion on slopes. 
			// Marcel (genius) figured out how to tell when the player wants to transfer his momentum based on his current velocity.
			// This may or may not be the way we want to permanently implement it. It work is most all cases except using slopes to change direction in hairpin turns.
			// Check out going down the stuff to the left of player start to see what I mean.
			if (NormalX * GetCapsuleComponent()->ComponentVelocity.X >= 0) {
				GetCharacterMovement()->Velocity.X += (NormalX > 0 ? -1 : 1) * FVector::DotProduct(Hit.Normal, GetCapsuleComponent()->ComponentVelocity);
			}
			else {
				GetCharacterMovement()->Velocity.X += (NormalX > 0 ? -1 : 1) * FVector::DotProduct(Hit.Normal, GetCapsuleComponent()->ComponentVelocity)*0.4;
			}
		}
	}

	// Hit Vertical Wall
	else if (NormalZ < 0.001 && NormalZ > -0.001 && isInWallSlideVolume && GetCharacterMovement()->IsFalling()) {
		if (wallSlideBit == 0) {
			GetCharacterMovement()->Velocity.Z += FMath::Sqrt(-FVector::DotProduct(Hit.Normal, GetCapsuleComponent()->ComponentVelocity))*1.5;
			int32 WallDirection;
			if (NormalX < 0) {
				WallDirection = 1;
			}
			else {
				WallDirection = 2;
			}
			startWallSliding(WallDirection);
		}
	}


}

void ASUPERFASTCharacter::OnBeginOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("BEGIN OVERLAP"));
	if (OtherActor != this && OtherActor->ActorHasTag("ws")) {
		isInWallSlideVolume = true;
	}
}

void ASUPERFASTCharacter::OnEndOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("End OVERLAP"));
	if (OtherActor->ActorHasTag("ws")) {
		isInWallSlideVolume = false;
		stopWallSliding();
	}
}

void ASUPERFASTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(ASUPERFASTCharacter, wallSlideBit);
	DOREPLIFETIME(ASUPERFASTCharacter, mayDoubleJump);
	DOREPLIFETIME(ASUPERFASTCharacter, IdleAnimation);
	DOREPLIFETIME(ASUPERFASTCharacter, RunningAnimation);
	DOREPLIFETIME(ASUPERFASTCharacter, BeginJumpAnimation);
	DOREPLIFETIME(ASUPERFASTCharacter, FollowThroughJumpAnimation);
	DOREPLIFETIME(ASUPERFASTCharacter, SlideAnimation);
	DOREPLIFETIME(ASUPERFASTCharacter, WallSlideAnimation);
}