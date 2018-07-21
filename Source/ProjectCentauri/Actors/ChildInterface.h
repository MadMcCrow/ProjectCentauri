// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ChildInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
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
	 *	@note : Class implementing this interface must implement it.
	 */
	UFUNCTION()
		virtual void UpdateChildActors() = 0;
	/**
	*	@brief UpdateChildActors_BP Function
	*	This function should refresh the list of Actor attached to any class implementing this interface
	*	@note : this function is to use UpdateChildActors in Blueprints. There's no need to override it.
	*	@see UpdateChildActors()
	*/
	UFUNCTION(BlueprintCallable, Category = "ChildInterface", meta = (DisplayName = "Update Child Actors"))
		virtual void UpdateChildActors_BP() { UpdateChildActors(); }


	/**
	*	@brief GetAllAttachedActors Function
	*	This function should grant you access to an Array of Actors attached.
	*	@note : this is a const function, you should make sure to have the Array at hand in a variable somewhere
	*	@note : Class implementing this interface must implement it.
	*/
	UFUNCTION()
		virtual TArray<AActor *> GetAllAttachedActors() const = 0;

protected:

	/**
	 *	@brief GetAttachedActorsRecursively Function
	 *	by default, This function browse recursively the Actors attached to any class implementing this interface
	 *	@param Out : the array containing the attached actors
	 *	@param bOnlyInterface : restrict to only actors implementing the interface
	 *  @note : Don't use that function too often.
	 *	@note : Should be faster with no restriction.
	 *	@note : No need to override.
 	 */
	UFUNCTION()
		virtual void GetAttachedActorsRecursively(TArray<AActor*> & Out, bool bOnlyInterface = false);

	/**
	 *	@brief AddChildActor_BP Function
	 *	This function tries to add and attach an Actor to the Actor implementing this interface
	 *	@param Parent : the Component to Attach to.
	 *	@param ClassToSpawn : The Class of SpaceActor you're trying to spawn
	 *	@param InTransform : A Transform you should Apply at Spawn
	 *	@param Socket : A socket on parent at which we should attach
	 *	@return AActor : The actor Created, or nullptr if it failed
	 */
	UFUNCTION()
		virtual AActor * AddChildActor(class UAttachComponent * Parent, TSubclassOf<class ASpaceActor> ClassToSpawn,const FTransform& InTransform = FTransform::Identity, FName Socket = "None");


	/**
	*	@brief GetAvaibleAttachPoints Function
	*	This function fills an Array with OutConnectors
	*	@param Out : Array containing available attach points
	*	@return bool : true if there's a Valid AttachPoint.
	*/
	UFUNCTION()
		virtual bool GetAvaibleAttachPoints(TArray<class UAttachComponent *> &Out);

	/**
	*	@brief GetAvaibleAttachPoints Function
	*	This function fills an Array with OutConnectors
	*	@param Out : the resulting transform for Adding a Child
	*	@return bool : true if there's a Valid AttachPoint.
	*/
	UFUNCTION()
		virtual bool GetAvaibleAttachPointsTransforms(TArray<FTransform> &Out);




	/**
	*	@brief GetAvaibleAttachPoints Function
	*	This function fills an Array with OutConnectors
	*	@param Out the resulting transform for Adding a Child
	*	@return bool: true if there's a Valid AttachPoint.
	*/
	UFUNCTION(BlueprintCallable, Category = "ChildInterface", meta = (DisplayName = "Get Avaible Attach Points"))
		virtual bool GetAvaibleAttachPoints_BP(TArray<FTransform> &Out) { return GetAvaibleAttachPointsTransforms(Out); }


	/**
	*	@brief AddAttachSpaceActor Function
	*	This function will add and  attach a space actor
	*	@param AActor: Out the created Actor for future reference.
	*	@return bool: true if we attached an actor correctly.
	*/
	UFUNCTION()
		virtual bool AddAttachSpaceActor(AActor * &Out, TSubclassOf<class ASpaceActor> ClassToSpawn, class UAttachComponent  * Target = nullptr);

	/**
	*	@brief AddAttachSpaceActor_BP Function
	*	This function will add and  attach a space actor
	*	@param AActor: Out the created Actor for future reference.
	*	@return bool: true if we attached an actor correctly.
	*	@see AddAttachSpaceActor
	*/
	UFUNCTION(BlueprintCallable, Category = "ChildInterface", meta = (DisplayName = "Add and Attach Space Actor"))
		virtual bool AddAttachSpaceActor_BP(AActor * &Out, TSubclassOf<class ASpaceActor> ClassToSpawn, class UAttachComponent  * Target = nullptr) {return AddAttachSpaceActor(Out, ClassToSpawn, Target);}



};
