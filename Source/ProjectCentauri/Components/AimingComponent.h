// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

/**
* @brief : Class that add auto aiming to any turret. Very useful !
* @todo : Implement non-auto behaviour.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCENTAURI_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAimingComponent();
	UAimingComponent(float range);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetRange(float Range);
	void SetSwivelVOfsset(float height);

	//These function are made for non fully automatic aiming
	void SetTargetOnce(FVector TargetWorldLocation);
	void SetTargetActor(class AActor * TargetActor);

	// These function are for the turret component to know what to do
	float GetGunAngle() const;
	float GetSwivelAngle() const;
	FRotator GetLookAtTarget() const;
	UFUNCTION(BlueprintCallable, Category = "aim")
	FVector GetTargetLocation() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// All the Aiming crap you can think of
	FRotator LookAtTarget;
	class AActor * TargetActor;
	bool bIsAutoAim = true;
	bool bTargetLocked;
	float FiringRange;

	// Aiming functions
	FRotator Aim() const;
	bool FindATarget();

private:
	FVector TargetRelativeCoordinates;

	// Variable for getting the correct alignement out of the Swivel, for the gun
	float SwivelOffset = 0.f;
	// Owner Pointer and Sanity check bool for safety
	class AActor * Owner;
	bool bOwnerHasTeamInterface;
};