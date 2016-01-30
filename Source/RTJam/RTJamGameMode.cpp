// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RTJam.h"
#include "RTJamGameMode.h"
#include "FeatherController.h"
#include "RTJamCharacter.h"

ARTJamGameMode::ARTJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/FeatherController_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
