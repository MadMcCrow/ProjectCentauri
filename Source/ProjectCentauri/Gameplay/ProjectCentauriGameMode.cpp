// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ProjectCentauriGameMode.h"
#include "CameraPawn.h"
#include "PlayerStatistics.h"
#include "SpacePlayerController.h"

AProjectCentauriGameMode::AProjectCentauriGameMode()
{
	DefaultPawnClass	  = ACameraPawn::StaticClass();
	PlayerControllerClass = ASpacePlayerController::StaticClass();
	PlayerStateClass	  = APlayerStatistics::StaticClass();
}

