// Copyright 2018 Noe PERARD-GAYOT

#include "SpacePlayerController.h"
#include "GameFramework/PlayerInput.h"

//Bindings for the selection
const FName ASpacePlayerController::SelectionToggleBinding("ToggleSelection");
const FName ASpacePlayerController::SelectionClickBinding("ClickSelection");


const FName  ASpacePlayerController::RotateYawBinding("Yaw");
const FName  ASpacePlayerController::RotatePitchBinding("Pitch");;
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
	InputComponent->BindAction(SelectionToggleBinding, IE_Pressed, this, &ASpacePlayerController::ToggleSelectionMode);
	InputComponent->BindAction(SelectionClickBinding, IE_Pressed, this, &ASpacePlayerController::SelectComponent);

	InputComponent->BindAxis(RotateYawBinding, this, &APlayerController::AddYawInput);
	InputComponent->BindAxis(RotatePitchBinding, this, &APlayerController::AddPitchInput);
	InputComponent->BindAxis(RotateRollBinding, this, &APlayerController::AddRollInput);

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

USceneComponent * ASpacePlayerController::GetVisibleComponentUnderCursor()
{
	ETraceTypeQuery TraceChannel = ETraceTypeQuery::TraceTypeQuery1;
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceChannel, true, HitResult);
	if (HitResult.Component.IsValid())
		return HitResult.Component.Get();
	return nullptr;
}


USceneComponent * ASpacePlayerController::GetComponentByObjectUnderCursor()
{

	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery_MAX);
	GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult);
	if (HitResult.Component.IsValid())
		return HitResult.Component.Get();
	return nullptr;
}

void ASpacePlayerController::SelectComponent()
{
	auto target = GetComponentByObjectUnderCursor();
	if (target)
	{
		SelectedComponent = target;
		SelectedActor = target->GetOwner();
		SelectComponent_BP(SelectedComponent);
	}

}

void ASpacePlayerController::MouseOverComponent()
{
	auto target = GetComponentByObjectUnderCursor();
	if (target)
	{
		HoveredComponent = target;
		HoveredActor = target->GetOwner();
		MouseOverComponent_BP(HoveredComponent);
	}
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
