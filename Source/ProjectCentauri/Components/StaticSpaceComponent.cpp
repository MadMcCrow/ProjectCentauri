// Copyright 2018 Noe PERARD-GAYOT

#include "StaticSpaceComponent.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values for this component's properties
UStaticSpaceComponent::UStaticSpaceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


//	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
//	Mesh->SetupAttachment(this);
}




void UStaticSpaceComponent::PostInitProperties()
{
	Super::PostInitProperties();
	//Mesh->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//SetSockets(Mesh);
}

// Called when the game starts
void UStaticSpaceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UStaticSpaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UStaticSpaceComponent::SetSockets(UMeshComponent * Setup)
{
	// either it is a Static or a Skeletal Mesh Component.
	UStaticMeshComponent * Static = Cast<UStaticMeshComponent>(Setup);
	if (Static) {
		if (Static->GetStaticMesh())
		{
			auto StaticSockets = Static->GetStaticMesh()->Sockets;
			for (auto it : StaticSockets)
			{
				Sockets.Add(FSpaceSocket(it->SocketName, it->Tag, FTransform(it->RelativeRotation, it->RelativeLocation, it->RelativeScale)));
			}
		}
	}
}





