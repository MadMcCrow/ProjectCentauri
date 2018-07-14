// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "SpaceObjectData.h"
#include "ShipData.generated.h"


/**
 *  Contains the data that makes a spaceship
 */
//use this for blueprint 
USTRUCT(BlueprintType)
struct FShipData : public  FSpaceObjectData
{
	//Always make USTRUCT variables into UPROPERTY()
	//    any non-UPROPERTY() struct vars are not replicated -- Could be usefull ??
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere)
		class UMaterialInterface* Skin;
	UPROPERTY(EditAnywhere)
		float Acceleration;


public:
	//Set
	FORCEINLINE void SetAcceleration(const float NewValue)			{Acceleration = NewValue;}
	FORCEINLINE void SetMesh(class UStaticMesh* NewMesh)   { Mesh = NewMesh; }
	FORCEINLINE void SetSkin(class UMaterialInterface* NewMaterial) { Skin = NewMaterial; }
	//Get
	FORCEINLINE class UStaticMesh* GetMesh() const			{ return Mesh;}
	FORCEINLINE class UMaterialInterface* GetSkin() const	{ return Skin;}
	FORCEINLINE float GetAcceleration() const 				{ return Acceleration; }
	//Check
	bool IsValid() const;

	//Constructor
	FShipData()
	{
		Mesh = nullptr;
		Skin = nullptr;
		Acceleration =	0;
		Mass = 0;
		Name = FName(TEXT("Default Ship"));
	}

	
	
	
};
