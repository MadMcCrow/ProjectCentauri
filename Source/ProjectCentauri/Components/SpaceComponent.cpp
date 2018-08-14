// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceComponent.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"


// Sets default values for this component's properties
USpaceComponent::USpaceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USpaceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpaceComponent::AddComponent(TSubclassOf<USpaceComponent> ClassToAdd, FName SocketName)
{
}

void USpaceComponent::SetSockets(UMeshComponent * Setup)
{
	// either it is a Static or a Skeletal Mesh Component.
	UStaticMeshComponent * Static = Cast<UStaticMeshComponent>(Setup);
	if (Static) {
		auto StaticSockets = Static->GetStaticMesh()->Sockets;
		for (auto it : StaticSockets)
		{
			Sockets.Add(FSpaceSocket(it->SocketName, it->Tag));
		}
	}
	else {
		USkeletalMeshComponent * Skeletal = Cast<USkeletalMeshComponent>(Setup);
		if (Skeletal)
		{

		}
	}
}
