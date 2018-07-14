// Copyright 2018 Noe PERARD-GAYOT

#include "ShipComponent.h"
#include "Engine/CollisionProfile.h"
#include "ShipDataTable.h"
#include "ShipData.h"
#include "ProjectCentauri.h"
#include "ThrusterTrailComponent.h"
#include "Engine/StaticMeshSocket.h"


// Constructor
UShipComponent::UShipComponent()
{
	// Prevent component from using CPU time
	bAutoActivate = false;
	PrimaryComponentTick.bCanEverTick = false;


	GetDataFromTable();
	Setup();
}

// Destructor
UShipComponent::~UShipComponent()
{
	//TODO: Find a way to determine if the trails were added at runtime.
	/*
	for (UThrusterTrailComponent* it : Trails)
	{
		it->DestroyComponent();
	}
	*/
}

/**
 * Post Spawn initialisation
 */
void UShipComponent::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * Construction method
 * @todo : maybe put it directly in constructor
 */
void UShipComponent::Setup()
{
	if(ShipData.IsValid())	{
		SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
		SetStaticMesh(ShipData.GetMesh());
		SetupSocketList(); // this is essential
		SetRealMass(ShipData.GetMass());
		Name = ShipData.GetName();
		//const TCHAR* NameAsChar = *(Name.ToString());
		//Rename(NameAsChar);

		TArray<UStaticMeshSocket*> Thrusters = GetSocketsByTag(TEXT("Thruster"));
		for (UStaticMeshSocket* it : Thrusters)
		{
			Trails.Add(AddParticleTrail(it));
		}
	}
}

/**
 * Function that spawn a List of ship and get the correct data from it
 * @todo : maybe try to make this static and template for all DataTable
 */
void UShipComponent::GetDataFromTable()
{
	UShipDataTable* SampleList = NewObject<UShipDataTable>();
	ShipData = SampleList->GetRowByIndex(ShipDataIndex);

	if(ShipData.IsValid())
		UE_LOG(LogTemp, Display, TEXT("Spaceship Data Retrieved"));
	// get rid of the reference so it gets GC
	SampleList = nullptr;
}

/**
 * Simple getter for the struct that rule them all
 *
 * @todo : make in inline
 */
FShipData UShipComponent::GetShipData()
{
	return  ShipData;
}

/**
* Simple setter for the struct that rule them all
* @todo : make in inline
*/
void  UShipComponent::SetShipData(FShipData Data) {
	ShipData = Data;
}

/**
 * Function that adds particule trail (for constructor only)
 * @return UThrusterTrailComponent* : pointer to the newly created Trail effect component
 * @todo : maybe merge with runtime function and add a way to determine if run from constructor or not
 */
UThrusterTrailComponent* UShipComponent::AddParticleTrail(UStaticMeshSocket * AttachSocket)
{
	static int num = 0;
	FString NewTrailName("EngineTrail");
	NewTrailName += FString::FromInt(num);
	UThrusterTrailComponent* NewTrail = CreateDefaultSubobject<UThrusterTrailComponent>(FName(*NewTrailName));
	if (!NewTrail)
	{
		return nullptr;
	}
	NewTrail->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachSocket->SocketName);
	num++;
	return NewTrail;
}

/**
* Function that adds particule trail (during runtime)
* @return UThrusterTrailComponent* : pointer to the newly created Trail effect component
* @todo :this seems to produce crashes. Shall be investigated.
*/
UThrusterTrailComponent* UShipComponent::AddParticleTrailRuntime(UStaticMeshSocket * AttachSocket)
{
	static int num = 0;
	FString NewTrailName("EngineTrail");
	NewTrailName += FString::FromInt(num);
	UThrusterTrailComponent* NewTrail = NewObject<UThrusterTrailComponent>();
	if (!NewTrail)
	{
		return nullptr;
	}
	// This should do to create the trail so it exist in he editor
	NewTrail->RegisterComponent();
	NewTrail->Rename(*NewTrailName);
	NewTrail->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocket->SocketName);
	num++;
	return NewTrail;
}
