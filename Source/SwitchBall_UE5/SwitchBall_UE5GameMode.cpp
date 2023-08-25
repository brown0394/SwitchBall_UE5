// Copyright Epic Games, Inc. All Rights Reserved.

#include "SwitchBall_UE5GameMode.h"
#include "SwitchBall_UE5Character.h"
#include "UObject/ConstructorHelpers.h"

ASwitchBall_UE5GameMode::ASwitchBall_UE5GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
