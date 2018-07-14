// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ShipMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UShipMovementComponent : public UFloatingPawnMovement
{
	GENERATED_BODY()
public:
	UShipMovementComponent();
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ApplyMovement(FVector Input);
	virtual void BeginPlay() override;

	void SetAcceleration(float A);
private:
	FTransform WorldSpawnTransform;
	class AActor* OwnerRef;
	
	
};
