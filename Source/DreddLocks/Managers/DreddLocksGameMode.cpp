// Copyright Epic Games, Inc. All Rights Reserved.

#include "DreddLocksGameMode.h"
#include "../Dredd/DreddLocksCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADreddLocksGameMode::ADreddLocksGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
