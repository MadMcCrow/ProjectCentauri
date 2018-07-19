// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChildInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint), MinimalAPI)
class UChildInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	@brief IChildInterface Interface
 *  This interface implements function for searching, finding and interacting with attached actors
 */
class PROJECTCENTAURI_API IChildInterface
{
	GENERATED_BODY()


public:

	/**
	 *	@brief UpdateChildActors Function
	 *	This function should refresh the list of Actor attached to any class implementing this interface
	 *	@note Class implementing this interface must implement it.
	 */
	UFUNCTION()
		virtual void UpdateChildActors() = 0;

protected:

	/**
	*	@brief GetAttachedActorsRecursively Function
	*	by default, This function browse recursively the Actors attached to any class implementing this interface
	*/
	UFUNCTION()
		virtual void GetAttachedActorsRecursively(TArray<AActor*> & Out);


	UFUNCTION()
		virtual bool AddChildActor(class USceneComponent * Parent, TSubclassOf<class ASpaceActor> ClassToSpawn, FName Socket = "None");

	UFUNCTION(BlueprintCallable, Category = "ChildInterface", meta = (DisplayName = "Add Child Actor"))
		virtual bool AddChildActor_BP(class USceneComponent * Parent, TSubclassOf<class ASpaceActor> ClassName) { return AddChildActor(Parent, ClassName); };

	
	
};
