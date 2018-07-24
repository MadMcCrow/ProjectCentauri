// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ProjectCentauriGameMode.h"
#include "Actors/SpacePawn.h"
#include "PlayerStatistics.h"

AProjectCentauriGameMode::AProjectCentauriGameMode()
{
	DefaultPawnClass = ASpacePawn::StaticClass();
	PlayerStateClass = APlayerStatistics::StaticClass();
}

