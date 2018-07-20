// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Actors/SpaceActor.h"
#include "ThrusterActor.generated.h"

/**
 * @brief AThrusterActor Class
 *  Base class for thrusters
 */
UCLASS()
class PROJECTCENTAURI_API AThrusterActor : public ASpaceActor
{
	GENERATED_BODY()
public :

	AThrusterActor();

protected:



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Thruster")
		float InpulsePower = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Thruster")
		FVector LocalThrustDirection = FVector::ForwardVector;

	UPROPERTY(BlueprintReadOnly, Category = "Thruster")
		FVector RelativeThrustDirection = FVector::ForwardVector;


	UFUNCTION()
		virtual void DoThrust();

private:
	/**
	 *	@brief ThrusterMeshComponent
	 *	Static mesh representing the Thruster
	 */
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * ThrusterMeshComponent;

protected:

#if 0
	/**
	*	@brief Thruster
	*	the Physical Thruster
	*/
	UPROPERTY(Category = Thruster, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UPhysicsThrusterComponent * Thruster;

#endif // 0

	/**
	*	@brief PawnBaseComponent
	*	The object onto wich we should apply the force of the thruster
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Thruster")
		class UPrimitiveComponent * PawnBaseComponent;
	

};
