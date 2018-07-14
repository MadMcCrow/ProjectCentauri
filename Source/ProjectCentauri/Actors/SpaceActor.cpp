// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceActor.h"


// Sets default values
ASpaceActor::ASpaceActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

