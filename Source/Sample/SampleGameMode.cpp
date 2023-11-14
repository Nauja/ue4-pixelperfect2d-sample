// Copyright Epic Games, Inc. All Rights Reserved.

#include "SampleGameMode.h"
#include "SampleCharacter.h"
#include "Kismet/GameplayStatics.h"

ASampleGameMode::ASampleGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ASampleCharacter::StaticClass();	
}
