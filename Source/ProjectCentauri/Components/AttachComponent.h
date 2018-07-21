// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AttachComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCENTAURI_API UAttachComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttachComponent();


#if WITH_EDITOR
	class UArrowComponent * Arrow; /**  @brief This allows displaying an arrow in editor to clearly see the attach component*/
#endif // WITH_EDITOR

	/**	
	 *	@brief GetWorldTransform
	 *	Allows for getting the world location of the AttachComponent
	 *	@note it should give the same result as GetComponentToWorld()
	 */
	UFUNCTION()
	FORCEINLINE FTransform GetWorldTransform() const{
		FTransform worldtrans = GetRelativeTransform();
		worldtrans.AccumulateWithShortestRotation(Owner->GetTransform(), ScalarRegister(1.f));
		return worldtrans;
	}

	/**
	 *	@brief GetAttachedActor
	 *	Getter for the AttachedActor property. returns the Actor attached or NULL if none
	 *	@see GetIsAvailable()	
	 */
	UFUNCTION()
		FORCEINLINE AActor * GetAttachedActor() const { return AttachedActor; }

	/**
	 *	@brief GetIsAvailable
	 *	Getter for the bIsAvailable property. returns true if nothing is attached, false otherwise
	 *	@see GetAttachedActor()
	 */
	UFUNCTION()
		FORCEINLINE bool GetIsAvailable() const { return bIsAvailable; }

	/**
	 *	@brief AttachActor
	 *	this function attaches actor to this component
	 *	@see GetAttachedActor()
	 *	@see GetIsAvailable()
	 *	@see @class ChildInterface 
	 */
	UFUNCTION()
		bool AttachActor(AActor* NewActor, FName Socket = "None");

	/**
	 *	@brief DetachActor
	 *	this function detaches the actor currently attached, if there's one.
	 *	@see GetAttachedActor()
	 *	@see GetIsAvailable()
	 *	@see AttachActor()
	 *	@see @class ChildInterface
	 */
	UFUNCTION()
		AActor * DetachActor();

private:
	
	/**
	 *	@brief Owner
	 *	Pointer to the Actor that own that component
	 *	it is the result of GetOwner in constructor
	 */
	UPROPERTY()
	class AActor* Owner;

	/**
	 *	@brief bIsAvailable
	 *	Boolean flag to describe if something is attached or not
	 *	@see AttachedActor
	 */
	UPROPERTY()
		bool bIsAvailable = true;


	/**
	*	@brief AttachedActor
	*	Pointer to the attached Actor. NULL if none attached.
	*	@see bIsAvailable
	*/
	UPROPERTY()
		class AActor * AttachedActor;

};
