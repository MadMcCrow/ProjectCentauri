// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceActor.h"


// Sets default values
ASpaceActor::ASpaceActor()
{
 	// No need to tick
	PrimaryActorTick.bCanEverTick = false;

}

float ASpaceActor::HullIntegrity()
{
	return 1.0f;
}

// Called when the game starts or when spawned
void ASpaceActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

