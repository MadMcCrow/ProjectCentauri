// Copyright 2018 Noe PERARD-GAYOT

#pragma once
// minimum includes
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Gameplay/TeamInterface.h"
#include "ChildInterface.h"
#include "ShipPawn.generated.h"

/**
*	This is the main part of a spaceship
*/
UCLASS()
class PROJECTCENTAURI_API AShipPawn : public APawn, public ITeamInterface, public IChildInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AShipPawn();

	// Do the spawn initialisation here
	virtual void OnConstruction(const FTransform & Transform) override;
	
	// Static names for axis bindings
	static const FName EngineThrustBinding;
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName FireRightBinding;

private:
	/**
	*	@brief ThrusterMeshComponent
	*	Static mesh representing the Thruster
	*/
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * PawnBaseMeshComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Space ship | Class")
	class UChildActorComponent* ShipComponent;

	class UCameraComponent* CameraComponent;
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UShipMovementComponent* MovementComponent;

	bool bCanMove = true;




public:	

	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns Shipsubobject **/
	FORCEINLINE class UActorComponent* GetShipComponent() const { return ShipComponent; }
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

	// Child Interface
public: 
	FORCEINLINE virtual void UpdateChildActors() override { ChildActorList.Reset(); GetAttachedActorsRecursively(ChildActorList, true); }
	FORCEINLINE virtual TArray<AActor *> GetAllAttachedActors() const override { return ChildActorList; };

private:
	/**
	*	This Array contains pointer to all the Actors we attached to the spaceship
	*/
	TArray<AActor*> ChildActorList;

protected:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get All Attached Actors" ))
	FORCEINLINE TArray<AActor*> GetAllAttachedActors_BP() const { return ChildActorList; }


#if 0
protected:
	UPROPERTY()
		TMap<AActor*, FVector> EnginesAttached;

#endif // 0
};
