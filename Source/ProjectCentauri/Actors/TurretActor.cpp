// Copyright 2018 Noe PERARD-GAYOT

#include "TurretActor.h"
#include "Components/TurretSubComponent.h"
#include "Engine/CollisionProfile.h"
#include "TurretDataTable.h"
#include "Components/AimingComponent.h"
#include "Components/TurretComponent.h"

// Sets default values
ATurretActor::ATurretActor()
{
	// let's make sure this ticks !
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true; 

	// build the turret
	TurretComp = CreateDefaultSubobject<UTurretComponent>(TEXT("Turret Base"));
	AimingComp = CreateDefaultSubobject<UAimingComponent>(TEXT("AimingComp"));

	// Let's load the Turret Data
	TurretStatistics = UTurretDataTable::GetRowStruct(0); // TODO: replace the 0 by a variable 
	// then toss it to the components
	TurretComp->UseTurretData(TurretStatistics);
	AimingComp->SetRange(TurretStatistics.GetRange()); 

	// little finishing touches
	RootComponent = TurretComp;
	AimingComp->SetSwivelVOfsset(TurretComp->GetSwivelOffset());
}

/**
* Post Spawn initialisation
* @todo : maybe remove the unnecessary calls
*/
void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
	AimingComp->SetSwivelVOfsset(TurretComp->GetSwivelOffset());
}


/**
* Function that checks the gun alignement
* @return bool : true if gun is correctly aligned
* @todo : maybe add gun firing rate check here
* @todo : check for precision of alignement
*/
bool ATurretActor::CanFire()
{
	if (TurretComp->IsAligned() && FireCooldown <= 0)
		return true;
	return false;
}


/**
* Called Every frame.
* @todo : make it tick every second and add a fire at enemy logic
*/
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Passing the Data from the aiming component to the actual turret
	TurretComp->SetTargetRotation(AimingComp->GetLookAtTarget());
	// refreshing cooldown
	if (FireCooldown > 0)
		FireCooldown -= DeltaTime;
	else
		FireCooldown = 0;
}

