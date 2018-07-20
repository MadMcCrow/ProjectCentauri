// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gameplay/TeamInterface.h"
#include "Actors/ChildInterface.h"
#include "SpaceActor.generated.h"


/**
*	@brief SpaceActorClass Represent any SpaceObject that is not directly possesed.
*/
UCLASS()
class PROJECTCENTAURI_API ASpaceActor : public AActor , public IChildInterface //, public ITeamInterface
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
	
	TArray<class UAttachComponent *> OutAttach;


	UPROPERTY()
		float Hull; // Equivalent to life for most video games

	UFUNCTION()
		virtual float HullIntegrity(); // if below 1.0f can't be attached and is considered a space debris. 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Isn't called nor do anything
	virtual void Tick(float DeltaTime) override;


private:
	AActor * Owner;

public:

	FORCEINLINE void SetOwner(AActor * NewOwner) { if (NewOwner) Owner = NewOwner; }

#if 0
	// Team Interface
private:
	FTeam SpaceShipTeam;
protected:
	FORCEINLINE virtual void SetTeam(const FTeam &NewTeam) override { SpaceShipTeam = NewTeam; }
	FORCEINLINE virtual FTeam & GetTeam()  override { return SpaceShipTeam; }
#endif // 0

public:
	FORCEINLINE virtual void UpdateChildActors() override { ChildActorList.Empty(); GetAttachedActorsRecursively(ChildActorList,true); }
	FORCEINLINE virtual TArray<AActor *> GetAllAttachedActors() const override { return ChildActorList; };

private:
	/**
	*	This Array contains pointer to all the Actors we attached to the spaceship
	*/
	TArray<AActor*> ChildActorList;

protected:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get All Attached Actors"))
		FORCEINLINE TArray<AActor*> GetAllAttachedActors_BP() const { return ChildActorList; }

};
