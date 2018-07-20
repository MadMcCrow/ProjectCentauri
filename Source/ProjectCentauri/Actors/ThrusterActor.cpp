// Copyright 2018 Noe PERARD-GAYOT

#include "ThrusterActor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"


AThrusterActor::AThrusterActor() : Super()
{
	// The Mesh
	ThrusterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thruster mesh"));
	RootComponent = ThrusterMeshComponent;

	ThrusterMeshComponent->SetEnableGravity(false); // We have to disable Gravity globally for this to work



}

void AThrusterActor::DoThrust()
{
	if(PawnBaseComponent)
		PawnBaseComponent->AddForceAtLocation(LocalThrustDirection * InpulsePower, FVector() /* Location */, NAME_None);
}
