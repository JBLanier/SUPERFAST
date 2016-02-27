// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SUPERFAST.h"
#include "SUPERFASTGameMode.h"
#include "SUPERFASTCharacter.h"

ASUPERFASTGameMode::ASUPERFASTGameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = ASUPERFASTCharacter::StaticClass();	
	
	UE_LOG(LogTemp, Warning, TEXT("Trying to set Custom Player Conteroller "));
	 static ConstructorHelpers::FObjectFinder<UBlueprint> Blueprint(TEXT("Blueprint'/Game/Blueprints/SFPlayercontroller.SFPlayerController'"));
      if (Blueprint.Object){
		  UE_LOG(LogTemp, Warning, TEXT("Custom Player Conteroller Set!"));
          PlayerControllerClass = (UClass*)Blueprint.Object->GeneratedClass;
	  }
	  else {
		  UE_LOG(LogTemp, Warning, TEXT("FAILED to set Custom Player Conteroller "));
	  }
	
}
