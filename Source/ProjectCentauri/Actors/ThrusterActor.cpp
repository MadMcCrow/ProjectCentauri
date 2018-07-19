// Copyright 2018 Noe PERARD-GAYOT

#include "ThrusterActor.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"


AThrusterActor::AThrusterActor() : Super()
{
	ThrusterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Thruster mesh"));
	Thruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("Thruster"));
}

void AThrusterActor::DoThrust()
{

}
