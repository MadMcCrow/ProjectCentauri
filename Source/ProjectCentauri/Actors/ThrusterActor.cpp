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

void AThrusterActor::DoThrust(float Intensity , UPrimitiveComponent * Root)
{
	
	if (Root)
		Root->AddForce(LocalThrustDirection * FMath::Clamp<float>(Intensity * InpulsePower, -InpulsePower, InpulsePower), NAME_None, false);
	DoThrust_BP(Intensity, Root);

}
