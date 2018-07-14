// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceObjectComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values for this component's properties
USpaceObjectComponent::USpaceObjectComponent()
{
	// make this component tick
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	
}



bool USpaceObjectComponent::SetupSocketList()
{
	UStaticMesh* Mesh = GetStaticMesh();
	if (Mesh)
	{
		SocketsList = Mesh->Sockets;
		bSocketsListIsSet = true;
		return true;
	}
	return false;
}


void USpaceObjectComponent::Setup()
{
}

void USpaceObjectComponent::SetRealMass(float RealMass)
{
	Mass = RealMass;
	float BaseMass = CalculateMass();
	SetMassScale(NAME_None, (RealMass / BaseMass));
}

TArray<UStaticMeshSocket*> USpaceObjectComponent::GetSocketsList() const
{	
	if (bSocketsListIsSet) {
		return SocketsList;
	}
	else {
		return TArray<class UStaticMeshSocket*>();
	}
}

TArray<UStaticMeshSocket*> USpaceObjectComponent::GetSocketsByTag(FString TagDiscriminent)
{
	if (bSocketsListIsSet) {
		TArray<UStaticMeshSocket*> subset;
		for (UStaticMeshSocket* soc : SocketsList)
		{
			if (soc->Tag == TagDiscriminent)
				subset.Add(soc);
		}
		return subset;

	}
#if !UE_BUILD_SHIPPING
	else
		UE_LOG(LogTemp, Error, TEXT("Socket List is not set"));
#endif
	return TArray<UStaticMeshSocket*>();
}

// Called every frame
void USpaceObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

