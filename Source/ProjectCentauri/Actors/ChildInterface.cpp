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

AActor * IChildInterface::AddChildActor(UAttachComponent * Parent, TSubclassOf<class ASpaceActor> ClassToSpawn, const FTransform & InTransform, FName Socket)
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


bool IChildInterface::GetAvaibleAttachPoints(TArray<class UAttachComponent *> &Out) 
{
	auto Actor = Cast<AActor>(this);
	if (!Actor)
		return false;
	Out.Reset();
	auto Array = Actor->GetComponentsByClass(UAttachComponent::StaticClass());
	for (auto it : Array)
	{
		auto Attach = Cast<UAttachComponent>(it);
		if (Attach)
		{
			if(Attach->GetIsAvailable())
				Out.Add(Attach);
		}

	}
	return (Out.Num()>0);
}

bool IChildInterface::GetAvaibleAttachPointsTransforms(TArray<FTransform>& Out)
{
	TArray<class UAttachComponent *> components;
	bool success = GetAvaibleAttachPoints(components);
	Out.Reset();
	for (auto it : components)
	{
		if (it)
			Out.Add(it->GetWorldTransform());
	}
	return success;
}


bool IChildInterface::AddAttachSpaceActor(AActor * & Out, TSubclassOf<ASpaceActor> ClassToSpawn, UAttachComponent  * Target)
{
	// Check if we're an actor.
	auto Actor = Cast<AActor>(this);
	if (!Actor)
		return false;


	// Find the Attach point
	UAttachComponent * validtarget = nullptr;
	if (Target)
	{
		validtarget = Target;
	}
	else {
		TArray<UAttachComponent * > AvailableTargets;
		if(GetAvaibleAttachPoints(AvailableTargets))
			validtarget = AvailableTargets[0];
	}
	if (!validtarget)
		return false;

	// spawn the actor
	Out = AddChildActor(validtarget, ClassToSpawn, validtarget->GetComponentToWorld());
	if (!Out)
		return false;
	return true;
}
