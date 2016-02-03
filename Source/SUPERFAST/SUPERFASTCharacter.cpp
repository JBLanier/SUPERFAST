// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SUPERFAST.h"
#include "SUPERFASTCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"




DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);
//////////////////////////////////////////////////////////////////////////
// ASUPERFASTCharacter

ASUPERFASTCharacter::ASUPERFASTCharacter()
{
	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> BeginJumpAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> FollowThroughJumpAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> SlideAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WallSlideAnimationAsset;
		FConstructorStatics()
			: RunningAnimationAsset(TEXT("/Game/SuperFastSprites/Run_FlipBook"))
			, IdleAnimationAsset(TEXT("/Game/SuperFastSprites/Ready_FlipBook"))
			, BeginJumpAnimationAsset(TEXT("/Game/SuperFastSprites/Jump_1_FlipBook"))
			, FollowThroughJumpAnimationAsset(TEXT("/Game/SuperFastSprites/Jump_2_Flipbook"))
			, SlideAnimationAsset(TEXT("/Game/SuperFastSprites/Slide_FlipBook"))
			, WallSlideAnimationAsset(TEXT("/Game/SuperFastSprites/WallSlide_FlipBook"))

		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	RunningAnimation = ConstructorStatics.RunningAnimationAsset.Get();
	IdleAnimation = ConstructorStatics.IdleAnimationAsset.Get();
	BeginJumpAnimation = ConstructorStatics.BeginJumpAnimationAsset.Get();
	FollowThroughJumpAnimation = ConstructorStatics.FollowThroughJumpAnimationAsset.Get();
	SlideAnimation = ConstructorStatics.SlideAnimationAsset.Get();
	WallSlideAnimation = ConstructorStatics.WallSlideAnimationAsset.Get();

	GetSprite()->SetFlipbook(IdleAnimation);

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
	CameraBoom->bAbsoluteRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->RelativeRotation = FRotator(0.0f, -90.0f, 0.0f);


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->bAbsoluteRotation = true;
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 10.0f; //originally: 2.0f
	GetCharacterMovement()->AirControl = 0.80f; //originally 0.8 f
	GetCharacterMovement()->JumpZVelocity = 1500.f; //originally: 1000.0 f
	GetCharacterMovement()->GroundFriction = 3.0f; //originally 3.0 f
	GetCharacterMovement()->MaxWalkSpeed = 3000.0f; //originally 600 f
	GetCharacterMovement()->MaxFlySpeed = 600.0f; //originally: 600f

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

	acceptsMoveRightCommands = true;
	isSliding = false;
	isMovingLaterally = false;
	mayDoubleJump = true;
	isWallSliding = 0;
	isInWallSlideVolume = false;


	this->OnActorHit.AddDynamic(this, &ASUPERFASTCharacter::OnHit);
	this->OnActorBeginOverlap.AddDynamic(this, &ASUPERFASTCharacter::OnBeginOverlap);
	this->OnActorEndOverlap.AddDynamic(this, &ASUPERFASTCharacter::OnEndOverlap);
	
}

//////////////////////////////////////////////////////////////////////////
// Animation

void ASUPERFASTCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeed = PlayerVelocity.Size();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation;
	if (isWallSliding != 0) {
		DesiredAnimation = WallSlideAnimation;
	} else if (isSliding == true) {
		DesiredAnimation = SlideAnimation;
	} else if (GetCharacterMovement()->IsFalling() == true) {
		DesiredAnimation = (PlayerVelocity.Z < 0) ? FollowThroughJumpAnimation : BeginJumpAnimation;
	} else if (isMovingLaterally && !GetCharacterMovement()->IsFalling()) {
		DesiredAnimation = RunningAnimation;
	} else {
		DesiredAnimation = IdleAnimation;
	}

	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

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
	InputComponent->BindAction("Grapple", IE_Pressed, this, &ASUPERFASTCharacter::startGrappling);
	InputComponent->BindAction("Grapple", IE_Released, this, &ASUPERFASTCharacter::stopGrappling);
	InputComponent->BindAction("UseItem", IE_Released, this, &ASUPERFASTCharacter::useItem);
	InputComponent->BindAxis("MoveRight", this, &ASUPERFASTCharacter::MoveRight);

	InputComponent->BindTouch(IE_Pressed, this, &ASUPERFASTCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ASUPERFASTCharacter::TouchStopped);
}

void ASUPERFASTCharacter::MoveRight(float Value)
{
	/*UpdateChar();*/

	// Apply the input to the character motion
	if (acceptsMoveRightCommands && Value != 0) {

		isMovingLaterally = true;
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	}
	else {
		isMovingLaterally = false;

	}
}

void ASUPERFASTCharacter::Jump()
{
	if (isWallSliding != 0) {
		int32 d = isWallSliding;
		stopWallSliding();
		jumpFromWallSlide(d);
	} else if (GetCharacterMovement()->IsFalling()) {
		//UE_LOG(LogTemp, Warning, TEXT("falling"));
		if (mayDoubleJump == true) {
			//UE_LOG(LogTemp, Warning, TEXT("may double jump was true"));

			doubleJump();
			mayDoubleJump = false;
		}
	} else {
		//UE_LOG(LogTemp, Warning, TEXT("not falling"));
		APaperCharacter::Jump();
	}
}

void ASUPERFASTCharacter::doubleJump()
{
	GetCharacterMovement()->Velocity.Z = GetCharacterMovement()->JumpZVelocity;
	
}

void ASUPERFASTCharacter::jumpFromWallSlide(int32 direction)
{
	GetCharacterMovement()->Velocity.Z = GetCharacterMovement()->JumpZVelocity;
	if (direction == 1) {
		GetCharacterMovement()->Velocity.X = GetCharacterMovement()->JumpZVelocity * -0.7;
	}
	else {
		GetCharacterMovement()->Velocity.X = GetCharacterMovement()->JumpZVelocity * 0.7;
	}

}


void ASUPERFASTCharacter::startSliding()
{
	acceptsMoveRightCommands = false;
	isMovingLaterally = false;
	isSliding = true;

	UCharacterMovementComponent *CM = GetCharacterMovement();
	FVector velocity = CM->Velocity;

	CM->BrakingFrictionFactor = 0.07;
	CM->bWantsToCrouch = true;

	if (!CM->IsFalling() && velocity.X <= 1000.0 && velocity.GetAbs().X > 0.0)
	{
		velocity.X += (velocity.Z > 0) ? 1 : ((velocity.Z < 0) ? -1 : 0) * 1000.0;
	}
}

void ASUPERFASTCharacter::stopSliding()
{
	acceptsMoveRightCommands = true;
	isSliding = false;
	
	GetCharacterMovement()->BrakingFrictionFactor = 2.0;
	GetCharacterMovement()->bWantsToCrouch = false;
}

void ASUPERFASTCharacter::startWallSliding(int32 direction)
{
	if (direction == 1 || direction == 2) {
		UE_LOG(LogTemp, Warning, TEXT("WALLSLIDE!"));

		GetCharacterMovement()->GravityScale = 2;
		acceptsMoveRightCommands = false;
		isWallSliding = direction;
	}
}

void ASUPERFASTCharacter::stopWallSliding()
{
	UE_LOG(LogTemp, Warning, TEXT("ENDED"));
	//Editor Value should match this
	GetCharacterMovement()->GravityScale = 5;
	acceptsMoveRightCommands = true;
	isWallSliding = 0;
}

void ASUPERFASTCharacter::startGrappling()
{
}

void ASUPERFASTCharacter::stopGrappling()
{

}

void ASUPERFASTCharacter::useItem()
{

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

void ASUPERFASTCharacter::UpdateCharacter()
{
	if (!isInWallSlideVolume && isWallSliding) {
		stopWallSliding();
	}
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

	
	UE_LOG(LogTemp, Warning, TEXT("COLLISION x: %f  y: %f"), Hit.Normal.X, Hit.Normal.Z);
	//UE_LOG(LogTemp, Warning, TEXT("X Velocity: %f"), GetCapsuleComponent()->ComponentVelocity.X);
	//UE_LOG(LogTemp, Warning, TEXT("Y Velocity: %f"), GetCapsuleComponent()->ComponentVelocity.Z);
	

	float NormalZ = Hit.Normal.Z;
	float NormalX = Hit.Normal.X;

	float xVelocity = GetCapsuleComponent()->ComponentVelocity.X;
	float zVelocity = GetCapsuleComponent()->ComponentVelocity.Z;

	// Landed on flat ground
	if (NormalZ > 0.01) {
		stopWallSliding();
		mayDoubleJump = true;
	}
	// Landed on 45 degree slope
	if (Hit.Normal.GetAbs().Z - 0.707 < 0.01 && Hit.Normal.GetAbs().Z - 0.707 > -0.01) {
		stopWallSliding();
		if (!isSliding) {
			GetCharacterMovement()->Velocity.X += (NormalX > 0 ? -1 : 1) * FVector::DotProduct(Hit.Normal, GetCapsuleComponent()->ComponentVelocity) * 0.2;
			
		}
	}

	// Hit Vertical Wall
	else if (NormalZ < 0.001 && NormalZ > -0.001 && isInWallSlideVolume && GetCharacterMovement()->IsFalling()) {
		if (isWallSliding == 0) {
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
	if (OtherActor != this) {
		isInWallSlideVolume = true;
	}
}

void ASUPERFASTCharacter::OnEndOverlap(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("End OVERLAP"));
	isInWallSlideVolume = false;
}