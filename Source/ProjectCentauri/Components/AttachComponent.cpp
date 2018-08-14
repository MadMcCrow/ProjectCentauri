// Copyright 2018 Noe PERARD-GAYOT

#include "AttachComponent.h"
#if WITH_EDITOR
#include "Components/ArrowComponent.h"
#endif // WITH_EDITOR



UAttachComponent::UAttachComponent() : Super()
{
	Owner = GetOwner();
	


#if WITH_EDITOR
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->ArrowColor = FColor::Yellow;
	Arrow->EditorScale = 1;
	Arrow->SetupAttachment(this);
#endif // WITH_EDITOR
}

bool UAttachComponent::AttachActor(AActor * NewActor, FName Socket)
{
	if (!bIsAvailable)
		return false; // aka : fuck you
	if (NewActor)
	{
		FAttachmentTransformRules AttachRules = FAttachmentTransformRules::KeepRelativeTransform;
		AttachRules.bWeldSimulatedBodies = true;
		NewActor->AttachToComponent(this, AttachRules, Socket);
		bIsAvailable = false;
		AttachedActor = NewActor;
		return true;
	}
	return false;
}

AActor * UAttachComponent::DetachActor()
{
	if (bIsAvailable || !AttachedActor)
		return nullptr;

	AttachedActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	bIsAvailable = true;
	return AttachedActor;
}
