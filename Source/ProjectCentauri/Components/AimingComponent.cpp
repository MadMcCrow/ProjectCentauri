// Copyright 2018 Noe PERARD-GAYOT

#include "AimingComponent.h"
#include "TeamInterface.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bTargetLocked = false; // We cannot have a target before finding one, that would break the logic.
	bIsAutoAim = true; // The non auto-Aim logic hasn't been done yet
}

// If Only Epic would give a way to specify which constructor to call this would be useful
UAimingComponent::UAimingComponent(float Range)
{
	PrimaryComponentTick.bCanEverTick = true;
	FiringRange = Range;
	bTargetLocked = false; // We cannot have a target before finding one, that would break the logic.
	bIsAutoAim = true; // The non auto-Aim logic hasn't been done yet
}

/**
 * Called Every Frame, Handle the update of the aiming. Currently only support Auto-Aim
 */
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check if Auto-Aiming
	if (bIsAutoAim) {
		// Check if Already own a Target
		if (!bTargetLocked) {
			TargetActor = nullptr;
			bTargetLocked = FindATarget();
		}
		else
		{
			// Target is Already locked, but may have left firing range or died
			if (!TargetActor)
				bTargetLocked = false;
			else if (FVector::Dist(Owner->GetActorLocation(), TargetActor->GetActorLocation()) > FiringRange)
				bTargetLocked = false;
		}
	}
	else{
		// Implements non-Auto Aiming logic here :
		// ...
	}

}

/**
 * Setup functin to set the range at wich look for a target
 * @param float: firing range
 */
void UAimingComponent::SetRange(float Range)
{
	FiringRange = Range; 
}

/**
* Function used by owner to get correct aiming angle
* @param float : the offset between the swivel and the base of the turret component
*/
void UAimingComponent::SetSwivelVOfsset(float height)
{
	SwivelOffset = height;
}


/**
 * Manually set a Location to fire at.
 */
void UAimingComponent::SetTargetOnce(FVector TargetWorldLocation) {
	TargetRelativeCoordinates = GetOwner()->GetActorTransform().InverseTransformPositionNoScale(TargetWorldLocation);
}

/**
* Manually set an Actor to fire at.
*/
void UAimingComponent::SetTargetActor(class AActor * Target) {
	if (Target)
		TargetActor = Target;
	else
		UE_LOG(LogTemp, Error, TEXT("Target is invalid"));

	TargetRelativeCoordinates = GetOwner()->GetActorTransform().InverseTransformPositionNoScale(Target->GetActorLocation());
}

/**
 * Function used by owner or other classes to ask for where to fire.
 * @return FRotator : The correct rotator to look toward the target. Might not be possible to use directly for the turret
 * @todo : maybe replace the calll by a value directly returned
 */
FRotator UAimingComponent::GetLookAtTarget() const
{
	return Aim();
}

/**
* Function used by owner or other classes to ask for where to fire.
* @return FRotator : The correct rotator to look toward the target. Might not be possible to use directly for the turret
*/
FVector UAimingComponent::GetTargetLocation() const
{
	if (TargetActor)
		return TargetActor->GetActorLocation();
	else
		return TargetRelativeCoordinates;
}



/**
 * Function that returns the adequat angle for a UTurretComponent gun rotation.
 * @return float: The aforementioned angle, in degree
 * @todo : check for correctness
 */
float UAimingComponent::GetGunAngle() const
{
	return Aim().Pitch;
}

/**
* Function that returns the adequat angle for a UTurretComponent swivel rotation.
* @return float: The aforementioned angle, in degree
* @todo : check for correctness
*/
float UAimingComponent::GetSwivelAngle() const
{
	return Aim().Yaw;
}


/**
* Called when the game starts. Handles post spawn initialisation
*/
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	if (Owner->Implements<UTeamInterface>())
		bOwnerHasTeamInterface = true;
	else
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Fatal, TEXT("Error, Turret Owner has no team, will not fire nor be fired at"));
#endif
	}
}

/**
* Function that returns the "Look at" rotation toward the target
* @return FRotator: Where to look at
* @todo : check for correctness
*/
FRotator UAimingComponent::Aim() const
{
	FVector Start = GetOwner()->GetActorLocation() + FVector(0.f, 0.f, SwivelOffset);
	FRotator Aim;
	if (bIsAutoAim)
	{
		if (TargetActor)
			Aim = UKismetMathLibrary::FindLookAtRotation(Start, TargetActor->GetActorLocation() );
		else
			Aim = UKismetMathLibrary::FindLookAtRotation(FVector(0.f,0.f,SwivelOffset), TargetRelativeCoordinates);
	}
	else
		Aim = UKismetMathLibrary::FindLookAtRotation(FVector(0.f, 0.f, SwivelOffset), TargetRelativeCoordinates);
	
#if !UE_BUILD_SHIPPING
	UE_LOG(LogTemp, Warning, TEXT("Swivel Vertical Offset is set to %f"), SwivelOffset);
#endif
	
	return Aim;
}

/**
* Function that find a valid target for auto-aim
* @return bool: true if found a valid target, false otherwise
*/
bool UAimingComponent::FindATarget()
{
	// Quick Sanity check
	if (!bOwnerHasTeamInterface)
		return false;

	TArray<AActor *> ActorsInRange;
	float Distance, DistancePrev = FiringRange;
	AActor * Target = nullptr;
	UGameplayStatics::GetAllActorsWithInterface((UObject *)GetWorld(), UTeamInterface::StaticClass(), ActorsInRange);
	for (AActor* it : ActorsInRange)
	{
		// find the closer one
		Distance = FVector::Dist(Owner->GetActorLocation(), it->GetActorLocation());
		if (Distance <= FiringRange && Distance <= DistancePrev && Distance >=0) {
			// first sanity check
			if (it != Owner) {
				// Let's check if it can be an enemy   
				if (it->Implements<UTeamInterface>())
				{
					ITeamInterface* OwnerAsTeamInterface = Cast<ITeamInterface>(Owner);
					ITeamInterface* itAsTeamInterface = Cast<ITeamInterface>(it);
					if( itAsTeamInterface->GetTeam() != OwnerAsTeamInterface->GetTeam())
					{
						Target = it;
						DistancePrev = Distance;
					}
				}

			}
		}
	}
	if (Target)
	{
		//From now on we have a valid target
		TargetActor = Target;
		return true;
	}
	else
		return false;
}
