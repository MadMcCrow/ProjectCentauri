// Copyright 2018 Noe PERARD-GAYOT

#pragma once
// minimum includes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShipData.h"
#include "TeamInterface.h"
#include "ShipPawn.generated.h"


UCLASS()
class PROJECTCENTAURI_API AShipPawn : public APawn, public ITeamInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AShipPawn();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Space ship | Class")
		FShipData ShipClassStruct;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Space ship | Class")
	class UShipComponent* ShipComponent;

	class UCameraComponent* CameraComponent;
	class USpringArmComponent* CameraBoom;
	class UShipMovementComponent* MovementComponent;
	float Acceleration = 100;
	float RealMass = 100;
	bool bCanMove = true;

public:	

	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns Shipsubobject **/
	FORCEINLINE class UShipComponent* GetShipComponent() const { return ShipComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }



private:
	void ApplyMovement();


	// Team Interface
private:
	FTeam SpaceShipTeam;
protected:
	FORCEINLINE virtual void SetTeam(const FTeam &NewTeam) override { SpaceShipTeam = NewTeam; }
	FORCEINLINE virtual FTeam & GetTeam()  override { return SpaceShipTeam; }

		
};
