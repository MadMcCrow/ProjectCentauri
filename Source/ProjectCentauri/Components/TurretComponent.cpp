// Copyright 2018 Noe PERARD-GAYOT

#include "TurretComponent.h"
#include "TurretDataTable.h"
#include "TurretSubComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"


UTurretComponent::UTurretComponent()
{
	// make this component tick
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;

	// Create the  turret
	PartType = ETurretPartEnum::TP_Base;
	Swivel = CreateDefaultSubobject<UTurretSubComponent>(TEXT("Swivel"), true);
	Swivel->PartType = ETurretPartEnum::TP_Swivel;
	Swivel->SetupAttachment(this);
	Gun = CreateDefaultSubobject<UTurretSubComponent>(TEXT("Gun"), true);
	Gun->PartType = ETurretPartEnum::TP_Gun;
	Gun->SetupAttachment(Swivel);

	// Let's get those data
	UseTurretData(0);
	ApplyTurretData();
	// Let's make sure We're not aiming at anything
	TargetAlign = FRotator(0.f, 0.f, 0.f);
}

/**
* Function called by owner to ask to use a specific Turret Data
* @param FName: the name of the correct table row
* @todo : should be done directly by owner or provided by DataTable
*/
void UTurretComponent::UseTurretData(FName TurretName)
{
	TurretStatistics = UTurretDataTable::GetRowStruct(TurretName);
}

/**
* Function called by owner to ask to use a specific Turret Data
* @param int: the index of the correct table row
* @todo : should be done directly by owner
*/
void UTurretComponent::UseTurretData(int index)
{
	TurretStatistics = UTurretDataTable::GetRowStruct(index);
}

/**
 * Function called by owner to adapt to the lookat angle given.
 * @param FRotator: the aim look at rotation
 * @todo : implements somewhere else the math offset
 */
void UTurretComponent::SetTargetRotation(FRotator SolidAngle)
{
	TargetAlign = FRotator(0, 270 + SolidAngle.Yaw, 90 - SolidAngle.Pitch);
}




/**
* Function to find the orientation of the gun.
* @return FRotator: the Gun current rotation
* @todo : remove it sometime in the futur, as it is not useful
*/
FRotator UTurretComponent::GetGunRotation() const
{
	return Gun->GetComponentRotation();
}

/**
* Function to find which turret characteristics are implemented in the turret
* @return FTurretData: the chosen turret data
*/
FTurretData UTurretComponent::GetTurretData() const
{
	return TurretStatistics;
}

/**
 * Function to find the vertical offset of the turret
 * @return float: the height offset
 */
float UTurretComponent::GetSwivelOffset() const
{
	return Gun->GetComponentLocation().Z - GetComponentLocation().Z;
}

/**
 * Function to get where to spawn projectile
 * @return bool: true if the gun is aligned with the target
 */
bool UTurretComponent::IsAligned() const
{
	return bIsAligned;
}

/**
 * Function to get where to spawn projectile
 * @return FTransform: the muzzle transform
 */
FTransform UTurretComponent::GetMuzzleTransform() const
{
	if (Gun->OutSocketExist())
	{
		FTransform Tr;
		if(Gun->GetOutSocket()->GetSocketTransform(Tr,Gun))
			return Tr;
	}
	return FTransform();
}

void UTurretComponent::BeginPlay()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTurretComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	RotateTurret();
}

/**
 * Function to apply the necessary movement
 */
void UTurretComponent::RotateTurret()
{
	FRotator CurrentAlign = FRotator(0.f, Swivel->GetRelativeTransform().Rotator().Yaw, Gun->GetRelativeTransform().Rotator().Roll);
	FRotator Delta = FMath::RInterpTo(CurrentAlign, TargetAlign, GetWorld()->GetDeltaSeconds(), TurretStatistics.GetRotationSpeed());
	Swivel->SetRelativeRotation(FRotator(0, Delta.Yaw, 0), false, nullptr, ETeleportType::TeleportPhysics);
	Gun->SetRelativeRotation(FRotator(0, 0, Delta.Roll), false, nullptr, ETeleportType::TeleportPhysics);

	// Check if aligned (half a degree is fine)
	if (UKismetMathLibrary::NormalizedDeltaRotator(CurrentAlign, Delta).IsNearlyZero(0.5))
		bIsAligned = true;
	else
		bIsAligned = false;
}

/**
 * Function to apply the necessary movement
 * @return float: the height offset
 */
void UTurretComponent::ApplyTurretData()
{ 
#if !UE_BUILD_SHIPPING
	if (!TurretStatistics.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Turret Data Incorrect"));
		return;
	}
#endif
	SetTurretStaticMesh(TurretStatistics.GetBaseMesh());
	Swivel->SetTurretStaticMesh(TurretStatistics.GetSwivelMesh());
	Gun->SetTurretStaticMesh(TurretStatistics.GetGunMesh());
	AttachCompToOutSocket(Swivel);
	Swivel->AttachCompToOutSocket(Gun);
}