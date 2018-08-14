// Copyright 2018 Noe PERARD-GAYOT

#pragma once
#include "CoreMinimal.h"
#include "TeamInterface.generated.h"



/**
 * This Enum could be extended to handle more different clans
 */
UENUM(BlueprintType)
enum class ETeamEnum : uint8
{
	TE_Neutral	UMETA(DisplayName = "Neutral"),
	TE_Player	UMETA(DisplayName = "Player"),
	TE_Enemy	UMETA(DisplayName = "Enemy")
};

USTRUCT(BlueprintType)
struct FTeam
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		ETeamEnum Team;

	UPROPERTY(EditAnyWhere)
		FColor TeamColor;

public:
	virtual bool operator==(const FTeam& other) const {	return Team == other.Team;}
	virtual bool operator!=(const FTeam& other) const { return Team != other.Team;}

};

// This class does not need to be modified.
//UINTERFACE(MinimalAPI)
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class UTeamInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface allow the owning object to rally a team and be handled as a possible target for the weapons.
 */
class PROJECTCENTAURI_API ITeamInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

		UFUNCTION()
		virtual FTeam& GetTeam() = 0;

		UFUNCTION(BlueprintCallable, Category = "Team", meta = (DisplayName = "Get Team"))
		virtual  FTeam GetTeam_BP();

		UFUNCTION()
		virtual void  SetTeam(const FTeam& NewTeam) = 0;

		UFUNCTION(BlueprintCallable, Category = "Team", meta = (DisplayName = "Set Team"))
		virtual	void  SetTeam_BP(const FTeam& NewTeam);


protected:


};
