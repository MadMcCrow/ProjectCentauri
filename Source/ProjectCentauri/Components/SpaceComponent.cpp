// Copyright 2018 Noe PERARD-GAYOT

#include "SpaceComponent.h"
#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values for this component's properties
USpaceComponent::USpaceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}




// Called when the game starts
void USpaceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpaceComponent::AddComponent(TSubclassOf<USpaceComponent> ClassToAdd, FName SocketName)
{
	auto NewComp = CreateComponent(ClassToAdd);
	if (NewComp)
	{
		NewComp->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}
}

USpaceComponent * USpaceComponent::CreateComponent(TSubclassOf<USpaceComponent> ClassToAdd)
{
	if (!ClassToAdd)
		return nullptr;
	//FName ComponentName = USpaceComponent::GetCDO();
	auto Outer = NewObject<USpaceComponent>(ClassToAdd);
	if (Outer)
	{
		Outer->RegisterComponent();
		return Outer;
	}
	return nullptr;
}

void USpaceComponent::SetSockets(UMeshComponent * Setup)
{
	// either it is a Static or a Skeletal Mesh Component.
	UStaticMeshComponent * Static = Cast<UStaticMeshComponent>(Setup);
	if (Static) {
		auto StaticSockets = Static->GetStaticMesh()->Sockets;
		for (auto it : StaticSockets)
		{
			Sockets.Add(FSpaceSocket(it->SocketName, it->Tag, FTransform(it->RelativeRotation,it->RelativeLocation, it->RelativeScale)));
		}
	}
	else {
		USkeletalMeshComponent * Skeletal = Cast<USkeletalMeshComponent>(Setup);
		if (Skeletal)
		{
			auto SkeletalSockets = Skeletal->SkeletalMesh->GetActiveSocketList();
			for (auto it : SkeletalSockets)
			{
				Sockets.Add(FSpaceSocket(it->SocketName, TEXT("NO TAG FOR SKELETAL MESH"), FTransform(it->RelativeRotation, it->RelativeLocation, it->RelativeScale)));
			}
		}
	}
}

void USpaceComponent::GetSocketsByTag(const FString & Tag, TArray<FSpaceSocket>& Out) const
{
	Out.Empty();
	for (auto it : Sockets)
	{
		if (it.SocketTag == Tag)
			Out.Add(it);
	}
}



bool USpaceComponent::GetSpaceSocketTransformByTag(const FString & Tag, TArray<FTransform> & Out)
{
	Out.Empty();
	for (auto it : Sockets)
	{
		if (it.SocketTag == Tag)
			Out.Add(GetSocketTransform(it.SocketName));
	}
	return (Out.Num() >= 1);
}

FTransform USpaceComponent::GetSocketTransform(FName SocketName, ERelativeTransformSpace TransformSpace) const
{
	return Mesh->GetSocketTransform(SocketName, TransformSpace);
}

FTransform USpaceComponent::GetSpaceSocketTransform(const FSpaceSocket &Socket)
{
	auto index = Sockets.Find(Socket);
	if (index != INDEX_NONE)
	{
		return Mesh->GetSocketTransform(Socket.SocketName);
	}
	return FTransform();
}
