// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceActor.h"
#include "Components/SceneComponent.h"

#if WITH_EDITOR
#include "Components/ArrowComponent.h"
#endif // WITH_EDITOR

// Sets default values
ASpaceActor::ASpaceActor()
{
 	// No need to tick
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITOR
	auto Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->ArrowColor = FColor::Cyan;
	Arrow->EditorScale = 5;
	Arrow->SetupAttachment(RootComponent);
#endif // WITH_EDITOR

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

