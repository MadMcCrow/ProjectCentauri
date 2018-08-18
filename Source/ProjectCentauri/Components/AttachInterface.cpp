// Copyright 2018 Noe PERARD-GAYOT

#include "AttachInterface.h"
#include "Components/MeshComponent.h"
#include "Components/SceneComponent.h"

#include "Components/MeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/SkeletalMeshSocket.h"

// Add default functionality here for any IAttachInterface functions that are not pure virtual.

bool IAttachInterface::AddComponent(TSubclassOf<USceneComponent> ClassToAdd, FName SocketName)
{
	auto NewComp = CreateComponent(ClassToAdd);
	if (NewComp)
	{
		NewComp->AttachToComponent(GetMesh() , FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
		return true;
	}
	return false;
}

void IAttachInterface::SetSockets(UMeshComponent * Setup)
{
	// either it is a Static or a Skeletal Mesh Component.
	UStaticMeshComponent * Static = Cast<UStaticMeshComponent>(Setup);
	if (Static) {
		if (Static->GetStaticMesh())
		{
			auto StaticSockets = Static->GetStaticMesh()->Sockets;
			for (auto it : StaticSockets)
			{
				GetSockets().Add(FSpaceSocket(it->SocketName, it->Tag, FTransform(it->RelativeRotation, it->RelativeLocation, it->RelativeScale)));
			}
		}
	}
	else {
		USkeletalMeshComponent * Skeletal = Cast<USkeletalMeshComponent>(Setup);
		if (Skeletal)
		{
			if (Skeletal->SkeletalMesh)
			{
				auto SkeletalSockets = Skeletal->SkeletalMesh->GetActiveSocketList();
				for (auto it : SkeletalSockets)
				{
					GetSockets().Add(FSpaceSocket(it->SocketName, TEXT("NO TAG FOR SKELETAL MESH"), FTransform(it->RelativeRotation, it->RelativeLocation, it->RelativeScale)));
				}
			}
		}
	}
}

USceneComponent * IAttachInterface::CreateComponent(TSubclassOf<USceneComponent> ClassToAdd)
{
	if (!ClassToAdd)
		return nullptr;
	//FName ComponentName = UStaticSpaceComponent::GetCDO();
	auto Outer = NewObject<USceneComponent>(ClassToAdd);
	if (Outer)
	{
		Outer->RegisterComponent();
		return Outer;
	}
	return nullptr;
}


void IAttachInterface::GetSocketsByTag(const FString & Tag, TArray<FSpaceSocket>& Out) const
{
	auto Sockets = GetSockets();
	Out.Empty();
	for (auto it : Sockets)
	{
		if (it.SocketTag == Tag)
			Out.Add(it);
	}
}

FTransform IAttachInterface::GetSpaceSocketTransform(const FSpaceSocket & Socket) const
{
	auto index = GetSockets().Find(Socket);
	if (index != INDEX_NONE)
	{
		return GetMesh()->GetSocketTransform(Socket.SocketName);
	}
	return FTransform();
}

bool IAttachInterface::GetSpaceSocketTransformByTag(const FString & Tag, TArray<FTransform>& Out)
{
	auto Sockets = GetSockets();
	Out.Empty();
	for (auto it : Sockets)
	{
		if (it.SocketTag == Tag)
			Out.Add(GetMesh()->GetSocketTransform(it.SocketName));
	}
	return (Out.Num() >= 1);
}

FTransform IAttachInterface::GetSocketFromScreenSpace(FVector2D & SceenCoordinates) const
{
	return FTransform();
}
