// Copyright 2018 Noe PERARD-GAYOT

#include "ChildInterface.h"
//#include "GameFramework/Actor.h"
#include "Actors/SpaceActor.h"
#include "Engine/World.h"

// Add default functionality here for any IChildInterface functions that are not pure virtual.

void IChildInterface::GetAttachedActorsRecursively(TArray<AActor*>& Out)
{
	//Out.Empty(); // Check if this is not a stupid idea
	TArray<AActor *> Root;
	auto Actor = Cast<AActor>(this);
	if (!Actor)
		return;
	Actor->GetAttachedActors(Root);
	//Out.Append(Root);
	for (auto it : Root)
	{
		if (it->Implements<UChildInterface>())
			Out.Add(it);
	}
	for (auto it : Out)
	{
		auto AsInterface = Cast<IChildInterface>(it);
		if (AsInterface)
			AsInterface->GetAttachedActorsRecursively(Out);
	}

}

bool IChildInterface::AddChildActor(USceneComponent * Parent, TSubclassOf<class ASpaceActor> ClassToSpawn, FName Socket)
{
	auto Actor = Cast<AActor>(this);
	if (!Actor)
		return false;
	auto World = Actor->GetWorld();
	if(!World)
		return false;
	// first prepare the parameters
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParam.Owner = Actor;
	SpawnParam.bAllowDuringConstructionScript = true; // maybe not necessary but better be safe than sorry
	auto NewActor = World->SpawnActor<ASpaceActor>(ClassToSpawn, Parent->GetComponentLocation() , Parent->GetComponentRotation(), SpawnParam);
	if (!NewActor)
		return false;
	NewActor->AttachToComponent(Parent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Socket);
	return true;

}
