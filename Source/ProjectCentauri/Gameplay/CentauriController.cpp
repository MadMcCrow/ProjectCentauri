// Copyright 2018 Noe PERARD-GAYOT

#include "CentauriController.h"
#include "GameFramework/PlayerInput.h"


//Bindings for the selection
const FName ACentauriController::SelectionToggleBinding("ToggleSelection");
const FName ACentauriController::SelectionClickBinding("ClickSelection");

ACentauriController::ACentauriController() : Super()
{
	//SetInputMode(FInputModeGameAndUI());
}


void ACentauriController::InitializeBindings()
{
	// is this necessary ? Will see
	PlayerInput->AddEngineDefinedActionMapping(FInputActionKeyMapping(SelectionToggleBinding, EKeys::Tab));
	PlayerInput->AddEngineDefinedActionMapping(FInputActionKeyMapping(SelectionClickBinding, EKeys::LeftMouseButton));
}

void ACentauriController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InitializeBindings();
	//InputComponent->BindAction(SelectionToggleBinding, IE_Pressed, this, &ASpacePlayerController::ToggleSelectionMode);
	//InputComponent->BindAction(SelectionClickBinding, IE_Pressed, this, &ASpacePlayerController::SelectComponent);
}

bool ACentauriController::GetRelativeCursorCoordinate(FVector2D &Coordinate)
{

	int32 X, Y;
	GetViewportSize(X,Y);
	FVector2D ViewPortDimension(X,Y), CursorPos;
	bool IsIn = GetMousePosition(CursorPos.X, CursorPos.Y);
	Coordinate = CursorPos/ViewPortDimension;
	return IsIn;
}

FVector2D ACentauriController::GetBorderDirection(float BorderSize)
{
	check(BorderSize <= 1);
	BorderSize /= 2; // Because 1 should be halfscreen ;)
	FVector2D MouseCoord, BorderDirection;
	if (!GetRelativeCursorCoordinate(MouseCoord) || (MouseCoord >= FVector2D(BorderSize, BorderSize) && MouseCoord >= FVector2D(1-BorderSize, 1-BorderSize))) //not interesting
		return FVector2D();

	if (MouseCoord.X < BorderSize)
		BorderDirection.X = (-1 + MouseCoord.X / BorderSize);
	if (MouseCoord.X > 1 - BorderSize)
		BorderDirection.X = 1 - (1 - MouseCoord.X) / (BorderSize);
	if (MouseCoord.Y < BorderSize)
		BorderDirection.Y = 1 - MouseCoord.Y / BorderSize;
	if (MouseCoord.Y > 1 - BorderSize)
		BorderDirection.Y = -1 + (1 - MouseCoord.Y) / (BorderSize);

	return BorderDirection;
}

USceneComponent * ACentauriController::GetVisibleComponentUnderCursor()
{
	ETraceTypeQuery TraceChannel = ETraceTypeQuery::TraceTypeQuery1;
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(TraceChannel, true, HitResult);
	if (HitResult.Component.IsValid())
		return HitResult.Component.Get();
	return nullptr;
}


USceneComponent * ACentauriController::GetComponentByObjectUnderCursor()
{

	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery_MAX);
	GetHitResultUnderCursorForObjects(ObjectTypes, true, HitResult);
	if (HitResult.Component.IsValid())
		return HitResult.Component.Get();
	return nullptr;
}

void ACentauriController::SelectComponent()
{
	auto target = GetComponentByObjectUnderCursor();
	if (target)
	{
		SelectedComponent = target;
		SelectedActor = target->GetOwner();
		SelectComponent_BP(SelectedComponent);
	}

}

bool ACentauriController::MouseOverComponent()
{
	auto target = GetComponentByObjectUnderCursor();
	if (target)
	{
		if (target != HoveredComponent)
		{
			// We changed component
			HoveredComponent = target;
			HoveredActor = target->GetOwner();
			MouseOverComponent_BP(HoveredComponent);
			return true;
		}
	}
	return false;
}