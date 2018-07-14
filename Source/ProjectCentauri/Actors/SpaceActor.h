// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "TeamInterface.h"
#include "SpaceActor.generated.h"

UCLASS()
class PROJECTCENTAURI_API ASpaceActor : public AActor //, ITeamInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceActor();


protected:

	UPROPERTY()
		bool bCanAttach;

	USceneComponent * RootAttach; // SpaceActors always attach on root.
	
	
	TArray<USceneComponent *> OutAttach;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
