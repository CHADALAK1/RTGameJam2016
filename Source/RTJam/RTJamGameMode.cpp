// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RTJam.h"
#include "RTJamGameMode.h"
#include "RTJamCharacter.h"

ARTJamGameMode::ARTJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
