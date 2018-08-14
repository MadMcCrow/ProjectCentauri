// Copyright 2018 Noe PERARD-GAYOT

#include "SpacePlayerController.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"

#include "Components/AttachComponent.h"
#include "UserInterface/SelectionActor.h"

#include "Components/WidgetComponent.h"




const FName  ASpacePlayerController::RotateYawBinding("Camera Yaw");
const FName  ASpacePlayerController::RotatePitchBinding("Camera Pitch");;
const FName  ASpacePlayerController::RotateRollBinding("Roll");;

ASpacePlayerController::ASpacePlayerController() : Super()
{
	bSelectionEnabled = false;
	bShowMouseCursor = false;
	bAttachToPawn = true;
}

void ASpacePlayerController::InitializeBindings()
{
	InputComponent->BindAxis(RotateYawBinding, this, &APlayerController::AddYawInput);
	InputComponent->BindAxis(RotatePitchBinding, this, &APlayerController::AddPitchInput);
	//InputComponent->BindAxis(RotateRollBinding, this, &APlayerController::AddRollInput);

	InputComponent->BindAction(SelectionClickBinding, IE_Pressed, this, &ASpacePlayerController::SelectComponent);
}


void ASpacePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bSelectionEnabled)
	{
		if (MouseOverComponent())
		{
			HoverOnMode(SpaceState);
		}
	}
	// Do nothing yet
}

void ASpacePlayerController::HoverOnMode(EControllerStateEnum Mode)
{
	switch (Mode)
	{
	case EControllerStateEnum::CSE_Build:
		if (HoveredComponent)
			if (HoveredComponent->IsA<UAttachComponent>())
			{
				if(HoverActor)
					HoverActor->Destroy();
				HoverActor = SpawnSelectionActor(HoveredComponent->GetComponentTransform());
				if (HoverActor)
					HoverActor->SetActive(false);
			}
			else { // Not a Attach component, no need to hover
				if (HoverActor)
					HoverActor->Destroy();
			}
		
		break;
	case EControllerStateEnum::CSE_Pilot:
		break;
	case EControllerStateEnum::CSE_Aim:
		break;
	default:
		break;
	}

}

ASelectionActor * ASpacePlayerController::SpawnSelectionActor(const FTransform SpawnTransform)
{
	// first prepare the parameters
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParam.Owner = GetPawnOrSpectator(); 	// Obey your master
	SpawnParam.bAllowDuringConstructionScript = true; // maybe not necessary but better be safe than sorry
	// Spawn
	auto NewSelectionActor = GetWorld()->SpawnActor<ASelectionActor>(SelectionActorClass, SpawnTransform, SpawnParam);
	if (!NewSelectionActor)
		return nullptr;
	return NewSelectionActor;
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

void ASpacePlayerController::SelectComponent()
{
	// Call Parent.
	Super::SelectComponent();
	
	// Act differently depending on mode.
	switch (SpaceState)
	{
	case EControllerStateEnum::CSE_Build:
		if(SelectedComponent)
			if (SelectedComponent->IsA<UAttachComponent>())
			{
				if (SelectionActor)
					SelectionActor->Destroy();
				SelectionActor = SpawnSelectionActor(HoveredComponent->GetComponentTransform());
				if (SelectionActor)
					SelectionActor->SetActive(true);
			}
			else if (SelectedComponent->IsA<UWidgetComponent>()) {
				UE_LOG(LogTemp, Warning, TEXT(" Doing your stuff"));
			}
		break;
	case EControllerStateEnum::CSE_Pilot:
		break;
	case EControllerStateEnum::CSE_Aim:
		break;
	default:
		break;
	}
	OnSelect_BP();
}
