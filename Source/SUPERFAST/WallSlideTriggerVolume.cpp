// Fill out your copyright notice in the Description page of Project Settings.

#include "SUPERFAST.h"
#include "WallSlideTriggerVolume.h"
/*
AWallSlideTriggerVolume::AWallSlideTriggerVolume(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName CollisionProfileName(TEXT("Trigger"));
	GetBrushComponent()->SetCollisionProfileName(CollisionProfileName);

	bColored = true;
	BrushColor.R = 100;
	BrushColor.G = 255;
	BrushColor.B = 100;
	BrushColor.A = 255;

}

#if WITH_EDITOR

void AWallSlideTriggerVolume::LoadedFromAnotherClass(const FName& OldClassName)
{
	Super::LoadedFromAnotherClass(OldClassName);

	if (GetLinkerUE4Version() < VER_UE4_REMOVE_DYNAMIC_VOLUME_CLASSES)
	{
		static FName DynamicTriggerVolume_NAME(TEXT("DynamicTriggerVolume"));

		if (OldClassName == DynamicTriggerVolume_NAME)
		{
			GetBrushComponent()->Mobility = EComponentMobility::Movable;
		}
	}
}

#endif

*/

