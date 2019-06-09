// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MOBA_GameGameMode.h"
#include "MOBA_GamePlayerController.h"
#include "MOBA_GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMOBA_GameGameMode::AMOBA_GameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMOBA_GamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/BpHero"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
