// Copyright 2018 Noe PERARD-GAYOT

#include "AttachMeshComponent.h"
#include "Components/StaticMeshComponent.h"


UAttachMeshComponent::UAttachMeshComponent() : Super()
{
	ConnectorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMesh"));
	ConnectorMeshComponent->SetupAttachment(this);
}
