// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PowerInterface.generated.h"



/**
*	@brief FPowerData Structure
*	Holds the information about the power consumption
*/
USTRUCT(BlueprintType)
struct FPowerData
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float IdlePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float LoadPower;

protected:

	UPROPERTY()
		bool bIsUsed;

public:
	// Constructor
	FPowerData(float Idle = 0.f, float Load = 0.f, bool Used = false)
	{
		IdlePower	= Idle;
		LoadPower	= Load;
		bIsUsed		= Used;
	}

	inline void Use(bool Used) { bIsUsed = Used; }
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPowerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTCENTAURI_API IPowerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/**
	 *	@brief ConsumeEnergy function
	 *	Function consume energy for the part
	 */
	UFUNCTION()
		virtual void ConsumeEnergy();
	
	/**
	*	@brief ConsumeEnergy function
	*	Function consume energy for the part
	*/
	UFUNCTION()
		virtual class AActor* GetPowerSource() = 0;

	
};
