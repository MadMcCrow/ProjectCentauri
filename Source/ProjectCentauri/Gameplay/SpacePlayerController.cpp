// Copyright 2018 Noe PERARD-GAYOT

#include "SpacePlayerController.h"
#include "GameFramework/PlayerInput.h"

//Bindings for the selection
const FName ASpacePlayerController::SelectionToggleBinding("ToggleSelection");
const FName ASpacePlayerController::SelectionClickBinding("ClickSelection");


const FName  ASpacePlayerController::RotateYawBinding("Camera Yaw");
const FName  ASpacePlayerController::RotatePitchBinding("Camera Pitch");;
const FName  ASpacePlayerController::RotateRollBinding("Roll");;

ASpacePlayerController::ASpacePlayerController() : Super()
{
	bSelectionEnabled = false;
	bShowMouseCursor = false;

}

void ASpacePlayerController::InitializeBindings()
{
	// is this necessary ? Will see
	PlayerInput->AddEngineDefinedActionMapping(FInputActionKeyMapping(SelectionToggleBinding, EKeys::Tab));
	PlayerInput->AddEngineDefinedActionMapping(FInputActionKeyMapping(SelectionClickBinding, EKeys::LeftMouseButton));
}

void ASpacePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InitializeBindings();
	//InputComponent->BindAction(SelectionToggleBinding, IE_Pressed, this, &ASpacePlayerController::ToggleSelectionMode);
	//InputComponent->BindAction(SelectionClickBinding, IE_Pressed, this, &ASpacePlayerController::SelectComponent);

	InputComponent->BindAxis(RotateYawBinding, this, &APlayerController::AddYawInput);
	InputComponent->BindAxis(RotatePitchBinding, this, &APlayerController::AddPitchInput);
	//InputComponent->BindAxis(RotateRollBinding, this, &APlayerController::AddRollInput);

}

void ASpacePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bSelectionEnabled)
	{
		MouseOverComponent();
	}
	// Do nothing yet
}

void ASpacePlayerController::SetSelectionMode(bool IsSelectionMode)
{
	bShowMouseCursor = IsSelectionMode;
	bSelectionEnabled = IsSelectionMode;
	SetSelectionMode_BP(IsSelectionMode);
}

void ASpacePlayerController::ToggleSelectionMode()
{
	SetSelectionMode(!bSelectionEnabled);
	ToggleSelectionMode_BP();
}

void ASpacePlayerController::DisplaySelection()
{
	DisplaySelection_BP(); // BlueprintImplementableEvent
}

void ASpacePlayerController::ChooseMode(EControllerStateEnum NewMode)
{
	SpaceState = NewMode;
	switch (NewMode)
	{
	case EControllerStateEnum::CSE_Build:
		SetBuilding();
		break;
	case EControllerStateEnum::CSE_Pilot:
		SetPilot();
		break;
	case EControllerStateEnum::CSE_Aim:
		SetAim();
		break;
	default:
		// Do nothing
		break;
	}

}

void ASpacePlayerController::SetBuilding()
{
	SetSelectionMode(true);
	// Call the Blueprint implementation.
	SetBuilding_BP();
}

void ASpacePlayerController::SetPilot()
{
	// Call the blueprint implementation
	SetPilot_BP();
}

void ASpacePlayerController::SetAim()
{
	// Call the blueprint implementation
	SetAim_BP();
}