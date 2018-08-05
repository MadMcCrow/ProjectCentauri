// Copyright 2018 Noe PERARD-GAYOT

#include "CentauriController.h"




ACentauriController::ACentauriController() : Super()
{

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

void ACentauriController::MouseOverComponent()
{
	auto target = GetComponentByObjectUnderCursor();
	if (target)
	{
		HoveredComponent = target;
		HoveredActor = target->GetOwner();
		MouseOverComponent_BP(HoveredComponent);
	}
}