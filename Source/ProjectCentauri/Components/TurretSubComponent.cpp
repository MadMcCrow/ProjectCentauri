// Copyright 2018 Noe PERARD-GAYOT

#include "TurretSubComponent.h"
#include "Engine/StaticMeshSocket.h"



UTurretSubComponent::UTurretSubComponent()
{
	if (Mesh)
	{
		SetStaticMesh(Mesh);
	}
}

const UStaticMeshSocket * UTurretSubComponent::GetInSocket() const
{
	if (InSocket)
		return InSocket;
	return nullptr;
}

const UStaticMeshSocket * UTurretSubComponent::GetOutSocket() const
{
	if (OutSocket)
		return OutSocket;
	return nullptr;
}

//TODO: replace safe by #if !UE_BUILD_SHIPPING statement
FName UTurretSubComponent::GetInSocketName(bool Safe) {
	if (Safe)
	{
		return FName(*(GetInSocketSafe()->GetName()));
	}
	else
		return FName(*(GetInSocket()->GetName()));
}

FName UTurretSubComponent::GetOutSocketName(bool Safe)
{
	if (Safe)
	{
		return FName(*(GetOutSocketSafe()->GetName()));
	}
	else
		return FName(*(GetOutSocket()->GetName()));
}

void UTurretSubComponent::SetTurretStaticMesh(UStaticMesh * NewMesh)
{
	SetStaticMesh(NewMesh);
	SetSockets();
}

bool UTurretSubComponent::IsValid()
{
	if (GetStaticMesh())
		if (OutSocket)
			return true;
	return false;
}

bool UTurretSubComponent::OutSocketExist()
{
	if (OutSocket)
		return true;
	return false;
}

bool UTurretSubComponent::InSocketExist()
{
	if (InSocket)
		return true;
	return false;
}

bool UTurretSubComponent::AttachCompToOutSocket(UTurretSubComponent * ChildTurretComp)
{
	SetSockets();
	if (OutSocketExist())
	{
		ChildTurretComp->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, OutSocket->SocketName);
		if (ChildTurretComp->InSocketExist())
			ChildTurretComp->RelativeLocation = FVector();// ChildTurretComp->GetInSocket()->RelativeLocation;
		return true;
	}
	else
	{
#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Warning, TEXT("Sockets were not sets when trying to attach"));
#endif
		SetSockets();
		ChildTurretComp->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("Out")));
		if (ChildTurretComp->InSocketExist())
			ChildTurretComp->RelativeLocation =  FVector();// ChildTurretComp->GetInSocket()->RelativeLocation;
		return true;

	}
	return false;
}

const UStaticMeshSocket * UTurretSubComponent::GetInSocketSafe()
{
	if (InSocket)
		return InSocket;
	else
		if (GetStaticMesh())
		{
			SetSockets();
			return InSocket;
		}
	return nullptr;
}

const UStaticMeshSocket * UTurretSubComponent::GetOutSocketSafe()
{
	if (OutSocket)
		return OutSocket;
	else
		if (GetStaticMesh())
		{
			SetSockets();
			return OutSocket;
		}
	return nullptr;
}

UTurretSubComponent * UTurretSubComponent::GetAttachedComponent()
{
	UTurretSubComponent * TurretComp = nullptr;
	TArray<USceneComponent *> Children;
	GetChildrenComponents(false, Children);
	for (USceneComponent * it : Children)
	{
		if (it->IsA(UTurretSubComponent::StaticClass()))
		{
			TurretComp = Cast<UTurretSubComponent>(it);
			break;
		}
	}
	return TurretComp;
}

void UTurretSubComponent::SetSockets()
{
	UStaticMesh * MeshPtr = GetStaticMesh();
	if (MeshPtr)
	{
		Mesh = MeshPtr;
		TArray<UStaticMeshSocket *> InSocArray = GetSocketsByTag(TEXT("In"));
		if (InSocArray.Num() >= 1)
			InSocket = InSocArray[0];
		else
			InSocket = GetSocketByName(TEXT("In"));
		TArray<UStaticMeshSocket *> OutSocArray = GetSocketsByTag(TEXT("Out"));
		if (OutSocArray.Num() >= 1)
			OutSocket = InSocArray[0];
		else
			OutSocket = GetSocketByName(TEXT("Out"));
	}
	
}
