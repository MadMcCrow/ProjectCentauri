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

	UFUNCTION()
		virtual void DoThrust(float Intensity, class UPrimitiveComponent * Root);

	UFUNCTION()
		virtual FVector GetWorldDirection () { return GetActorTransform().TransformVector(LocalThrustDirection); }

protected:



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Thruster")
		float InpulsePower = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Thruster")
		FVector LocalThrustDirection = FVector::ForwardVector;



private:
	/**
	 *	@brief ThrusterMeshComponent
	 *	Static mesh representing the Thruster
	 */
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * ThrusterMeshComponent;


};
