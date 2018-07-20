// Copyright 2018 Noe PERARD-GAYOT

#include "ChildInterface.h"
//#include "GameFramework/Actor.h"
#include "Actors/SpaceActor.h"
#include "Engine/World.h"
#include "Components/AttachComponent.h"
// Add default functionality here for any IChildInterface functions that are not pure virtual.

void IChildInterface::GetAttachedActorsRecursively(TArray<AActor*>& Out, bool bOnlyInterface)
{
	TArray<AActor *> Root;
	auto Actor = Cast<AActor>(this);
	if (!Actor)
		return;
	Actor->GetAttachedActors(Root);
	if (bOnlyInterface)
	{
		for (auto it : Root)
		{
			if (it->Implements<UChildInterface>())
				if (!Out.Contains(it))
					Out.Add(it);
		}
	}
	else {
		for (auto it : Root)
		{
				if (!Out.Contains(it))
					Out.Add(it);
		}
	}
	// Then call this loop --- Don't worry the Compiler should be able to optimize by merging with the other loops
	for (auto it : Root) // Use the array ( not containing them all)
	{
		auto AsInterface = Cast<IChildInterface>(it);
		if (AsInterface)
			AsInterface->GetAttachedActorsRecursively(Out);
	}
}

AActor * IChildInterface::AddChildActor(USceneComponent * Parent, TSubclassOf<class ASpaceActor> ClassToSpawn, const FTransform & InTransform, FName Socket)
{
	auto Actor = Cast<AActor>(this);
	if (!Actor)
		return nullptr;
	auto World = Actor->GetWorld();
	if(!World)
		return nullptr;
	// first prepare the parameters
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParam.Owner = Actor;
	SpawnParam.bAllowDuringConstructionScript = true; // maybe not necessary but better be safe than sorry
	auto NewActor = World->SpawnActor<ASpaceActor>(ClassToSpawn, InTransform,  SpawnParam);
	if (!NewActor)
		return nullptr;
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules::KeepRelativeTransform;
	AttachRules.bWeldSimulatedBodies = true;
	NewActor->AttachToComponent(Parent, AttachRules, Socket);

	NewActor->SetOwner(Actor);

	UpdateChildActors();

	return NewActor;
}

bool IChildInterface::GetAvaibleAttachPoints(TArray<FTransform>& Out)
{
	auto Actor = Cast<AActor>(this);
	if (!Actor)
		return false;
	Out.Empty();
	auto Array = Actor->GetComponentsByClass(UAttachComponent::StaticClass());
	for (auto it : Array)
	{
		auto Attach = Cast<UAttachComponent>(it);
		if(Attach)
			Out.Add(Attach->GetRelativeTransform());
	}
	return true;
}
