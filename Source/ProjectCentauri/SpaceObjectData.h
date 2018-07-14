// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpaceObjectData.generated.h"


/**
 *  Contains the data that makes a spaceship
 */
//use this for blueprint 
USTRUCT(BlueprintType)
struct FSpaceObjectData : public  FTableRowBase
{
	//Always make USTRUCT variables into UPROPERTY()
	//    any non-UPROPERTY() struct vars are not replicated -- Could be usefull ??
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		uint16 Index;
	UPROPERTY(EditAnywhere)
		FName Name;
	UPROPERTY(EditAnywhere)
		float Mass;

public:
	//Set
	FORCEINLINE void SetMass(const float NewValue)					{ Mass = NewValue; }
	FORCEINLINE void SetName(const FName NewName)					{ Name = NewName; }
	//Get
	FORCEINLINE float GetMass()	const						{ return Mass; }
	FORCEINLINE FName GetName()	const 						{ return Name; }

	//Check
	virtual bool IsValid() const;

	//Constructor
	FSpaceObjectData()
	{
		Mass = 0;
		Name = FName(TEXT("Default"));
	}

	
	
	
};
