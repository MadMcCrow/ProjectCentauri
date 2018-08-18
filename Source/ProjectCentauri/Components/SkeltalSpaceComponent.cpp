// Copyright 2018 Noe PERARD-GAYOT

#include "SkeltalSpaceComponent.h"

#include "Components/MeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"


// Sets default values for this component's properties
USkeltalSpaceComponent::USkeltalSpaceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}




void USkeltalSpaceComponent::PostInitProperties()
{
	Super::PostInitProperties();
	SetSockets(GetMesh());
}

// Called when the game starts
void USkeltalSpaceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void USkeltalSpaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USkeltalSpaceComponent::SetSockets(UMeshComponent * Setup)
{
	USkeletalMeshComponent * Skeletal = Cast<USkeletalMeshComponent>(Setup);
	if (Skeletal)
	{
		if (Skeletal->SkeletalMesh)
		{
			auto SkeletalSockets = Skeletal->SkeletalMesh->GetActiveSocketList();
			for (auto it : SkeletalSockets)
			{
				Sockets.Add(FSpaceSocket(it->SocketName, TEXT("NO TAG FOR SKELETAL MESH"), FTransform(it->RelativeRotation, it->RelativeLocation, it->RelativeScale)));
			}
		}
	}
}
