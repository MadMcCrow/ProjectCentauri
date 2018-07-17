// Copyright 2018 Noe PERARD-GAYOT

#include "TurretActor.h"

// Sets default values
ATurretActor::ATurretActor()
{

}

/**
* Post Spawn initialisation
* @todo : maybe remove the unnecessary calls
*/
void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
}


/**
* Function that checks the gun alignement
* @return bool : true if gun is correctly aligned
* @todo : maybe add gun firing rate check here
* @todo : check for precision of alignement
*/
bool ATurretActor::CanFire()
{
	//if (TurretComp->IsAligned() && FireCooldown <= 0)
	//	return true;
	return false;
}


/**
* Called Every frame.
* @todo : make it tick every second and add a fire at enemy logic
*/
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

