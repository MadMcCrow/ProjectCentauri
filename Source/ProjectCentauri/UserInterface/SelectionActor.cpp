// Copyright 2018 Noe PERARD-GAYOT

#include "SelectionActor.h"


// Sets default values
ASelectionActor::ASelectionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelectionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectionActor::SetActive(bool Active)
{
	bIsSelection = Active;
	SetActive_BP(Active);
}

