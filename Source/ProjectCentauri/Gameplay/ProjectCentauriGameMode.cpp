// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ProjectCentauriGameMode.h"
#include "Actors/ShipPawn.h"
#include "PlayerStatistics.h"

AProjectCentauriGameMode::AProjectCentauriGameMode()
{
	DefaultPawnClass = AShipPawn::StaticClass();
	PlayerStateClass = APlayerStatistics::StaticClass();
}

