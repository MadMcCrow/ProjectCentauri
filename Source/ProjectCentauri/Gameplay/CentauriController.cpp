// Copyright 2018 Noe PERARD-GAYOT

#include "CentauriController.h"
#include "GameFramework/PlayerInput.h"


//Bindings for the selection
const FName ACentauriController::SelectionToggleBinding("ToggleSelection");
const FName ACentauriController::SelectionClickBinding("ClickSelection");

ACentauriController::ACentauriController() : Super()
{

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