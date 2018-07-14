// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "SpaceObjectData.h"
#include "TurretData.generated.h"


/**
 *  Contains the data that makes a spaceship
 */
//use this for blueprint 
USTRUCT(BlueprintType)
struct FTurretData : public  FSpaceObjectData
{
	//Always make USTRUCT variables into UPROPERTY()
	//    any non-UPROPERTY() struct vars are not replicated -- Could be usefull ??
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		class UStaticMesh* BaseMesh;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* SwivelMesh;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* GunMesh;
	UPROPERTY(EditAnywhere)
		float RotationSpeed;
	UPROPERTY(EditAnywhere)
		float Range;
	UPROPERTY(EditAnywhere)
		float FiringRate;
	UPROPERTY(EditAnywhere)
		int  ProjectileIndex;

public:
	//Set
	FORCEINLINE void SetBaseMesh(class UStaticMesh* NewMesh)	{ BaseMesh = NewMesh; }
	FORCEINLINE void SetSwivelMesh(class UStaticMesh* NewMesh)  { SwivelMesh = NewMesh; }
	FORCEINLINE void SetGunMesh(class UStaticMesh* NewMesh)		{ GunMesh = NewMesh; }
	FORCEINLINE void SetRotationSpeed( float NewRotSpeed)		{ RotationSpeed = NewRotSpeed; }
	FORCEINLINE void SetRange(float NewRange)					{ Range = NewRange; }
	FORCEINLINE void SetFiringRate(float NewFiringRate)			{ FiringRate = NewFiringRate; }

	//Get
	FORCEINLINE class UStaticMesh* GetBaseMesh() const		{ return BaseMesh; }
	FORCEINLINE class UStaticMesh* GetSwivelMesh() const	{ return SwivelMesh; }
	FORCEINLINE class UStaticMesh* GetGunMesh() const		{ return GunMesh; }
	FORCEINLINE float GetRotationSpeed() const				{ return RotationSpeed; }
	FORCEINLINE float GetRange() const						{ return Range; }
	FORCEINLINE float GetFiringRate() const					{ return FiringRate; }
	FORCEINLINE int   GetProjectileIndex() const			{ return ProjectileIndex; }
	//Check
	//Check
	virtual bool IsValid() const override;

	//Constructor
	FTurretData()
	{
		BaseMesh = nullptr;
		GunMesh = nullptr;
		SwivelMesh = nullptr;
		Name = FName(TEXT("Default Turret"));
	}

	
	
	
};
