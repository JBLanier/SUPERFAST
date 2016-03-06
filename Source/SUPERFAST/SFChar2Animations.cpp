// Fill out your copyright notice in the Description page of Project Settings.

#include "SUPERFAST.h"
#include "SFChar2Animations.h"
#include "PaperFlipbookComponent.h"
#include "SFCharacterMovementComponent.h"
#include "UnrealNetwork.h"
#include "Components/TextRenderComponent.h"


/*void ASFChar2Animations::setUpAnimations()
{

	UE_LOG(LogTemp, Warning, TEXT("Child SET UP ANIMATIONS CALLED"));

	// Setup the assets
	struct FConstructorStatics
	{

		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> BeginJumpAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> FollowThroughJumpAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> SlideAnimationAsset2;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> WallSlideAnimationAsset2;

		FConstructorStatics()
			: RunningAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Run_FlipBook"))
			, IdleAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Ready_FlipBook"))
			, BeginJumpAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Jump_1_FlipBook"))
			, FollowThroughJumpAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Jump_2_Flipbook"))
			, SlideAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2Slide_FlipBook"))
			, WallSlideAnimationAsset2(TEXT("/Game/SuperFastSprites/2/2WallSlide_FlipBook"))

		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	RunningAnimation = ConstructorStatics.RunningAnimationAsset2.Get();
	IdleAnimation = ConstructorStatics.IdleAnimationAsset2.Get();
	BeginJumpAnimation = ConstructorStatics.BeginJumpAnimationAsset2.Get();
	FollowThroughJumpAnimation = ConstructorStatics.FollowThroughJumpAnimationAsset2.Get();
	SlideAnimation = ConstructorStatics.SlideAnimationAsset2.Get();
	WallSlideAnimation = ConstructorStatics.WallSlideAnimationAsset2.Get();
}
*/