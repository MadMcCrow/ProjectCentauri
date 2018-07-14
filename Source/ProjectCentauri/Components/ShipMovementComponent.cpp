// Copyright 2018 Noe PERARD-GAYOT

#include "ShipMovementComponent.h"
#include "Engine/World.h"  // GetWorld()
#include "Kismet/KismetMathLibrary.h"

UShipMovementComponent::UShipMovementComponent() {
	OwnerRef = GetOwner();
	bConstrainToPlane = true;
}

void UShipMovementComponent::ApplyMovement(FVector Input)
{
	AddInputVector(Input, true);
	//Rotation
	if(Velocity!= FVector(0.f,0.f,0.f))
	{
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FVector(0.f, 0.f, 0.f), Velocity);
		Rotation.Roll =  Rotation.Euler().Z - OwnerRef->GetActorRotation().Euler().Z;
		Rotation = FMath::RInterpTo(OwnerRef->GetActorRotation(), Rotation, GetWorld()->GetTimeSeconds(), 0.01f);
		OwnerRef->SetActorRelativeRotation(Rotation.Quaternion(), false, nullptr, ETeleportType::TeleportPhysics);
	}

	//move back to Z origin
	OwnerRef->SetActorLocation(FVector( (float)OwnerRef->GetActorLocation().X,
									    (float)OwnerRef->GetActorLocation().Y,
										(float)WorldSpawnTransform.GetLocation().Z),
								false, nullptr, ETeleportType::TeleportPhysics);

								
}

void UShipMovementComponent::BeginPlay()
{
	WorldSpawnTransform = OwnerRef->GetActorTransform();
}

void UShipMovementComponent::SetAcceleration(float A)
{
	Acceleration = Deceleration = A;
	Deceleration /= 2;
}
