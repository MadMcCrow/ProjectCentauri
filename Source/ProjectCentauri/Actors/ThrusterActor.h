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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float InpulsePower = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FVector RelativeThrustDirection = FVector::ForwardVector;


	UFUNCTION()
		virtual void DoThrust();

	
	
	
	
};
