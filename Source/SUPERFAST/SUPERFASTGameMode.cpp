// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SUPERFAST.h"
#include "SUPERFASTGameMode.h"
#include "SUPERFASTCharacter.h"

ASUPERFASTGameMode::ASUPERFASTGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = ASUPERFASTCharacter::StaticClass();	
}
