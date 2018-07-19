// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/TeamInterface.h"
#include "SpaceActor.generated.h"


/**
*	@brief SpaceActorClass Represent any SpaceObject that is not directly possesed.
*/
UCLASS()
class PROJECTCENTAURI_API ASpaceActor : public AActor // , public ITeamInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceActor();


protected:

	UPROPERTY(EditDefaultsOnly)
		bool bCanAttach;

	UPROPERTY()
		bool bIsAttached;


public:

	FORCEINLINE bool GetCanAttach() const { return bCanAttach; }
	FORCEINLINE bool GetIsAttached() const { return bIsAttached; }


	//USceneComponent * RootAttach; // SpaceActors always attach on root. like any ChildActors actually
	
	TArray<USceneComponent *> OutAttach;


	UPROPERTY()
		float Hull; // Equivalent to life for most video games

	UFUNCTION()
		virtual float HullIntegrity(); // if below 1.0f can't be attached and is considered a space debris. 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	
	
};
