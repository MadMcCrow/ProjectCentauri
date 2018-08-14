// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class PROJECTCENTAURI_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	/**
	*	@brief GetCentauriController Function
	*	@return ACentauriController : The centauri controller controlling this pawn. nullptr if it is not controlled by a Player or gamemode not set properly
	*/
	UFUNCTION()
	class ACentauriController * GetCentauriController();

	/**
	*	@brief GetCentauriController Function
	*	@return ACentauriController : The centauri controller controlling this pawn. nullptr if it is not controlled by a Player or gamemode not set properly
	*/
	UFUNCTION(BlueprintPure, Category = "Centauri", meta = (DisplayName = "Get Centauri Controller"))
		FORCEINLINE class ACentauriController * GetCentauriController_BP() {return GetCentauriController();	}

protected:

	// Camera Controller bindings
	static const FName RotateYawBinding;
	static const FName RotatePitchBinding;
	static const FName RotateRollBinding;
	static const FName ForwardBinding;
	static const FName RightBinding;
	static const FName DollyBinding;

private:

	/**
	*	@brief PlayerCamera property
	*	The main camera for the player. it should be auto possesed.
	*/
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* PlayerCamera;


	/**
	*	@brief PlayerCameraBoom property
	*	The virtual arm to distance the camera from the center. it should be auto possesed.
	*/
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* PlayerCameraBoom;


protected:

	/**
	 *	@brief BorderRotationSpeed Property
	 *	Scale the speed at wich the camera turns when at screen border
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Centauri|Camera", meta = (DisplayName = "Screen Border Rotation Speed"))
		float BorderRotationSpeed;

	/**
	*	@brief BorderSize Property
	*	Define the portion of the screen to use for rotating the view.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Centauri|Camera", meta = (DisplayName = "Screen Border size"))
		float BorderSize;

	/**
	*	@brief bShouldRotateOnBorder Property
	*	boolean flag to allow rotating the camera on borders
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Centauri|Camera", meta = (DisplayName = "Should Rotate camera on screen border ?"))
		bool bShouldRotateOnBorder;

private:

	/**
	 *	@brief RotateOnBorder Function
	 *	Rotate the camera when the mouse cursor approaches the border of the viewport.
	 *	@note : should be called on tick
	 */
	UFUNCTION()
		void RotateOnBorder(float DeltaTime);


public:
	/**
	 *	@brief SetLookAtObject Function
	 *	Set the camera pawn to be attached to a target
	 *	@param	AActor * Target : The Object you want to be attached to
	 *	@param	float Margin : An additional distance you want to set
	 */
	UFUNCTION()
	void SetLookAtObject(AActor * Target, const float Margin = 0.f);

	/**
	 *	@brief SetLookAtObject Function
	 *	Set the camera pawn to be attached to a target
	 *	@param	AActor * Target : The Object you want to be attached to
	 *	@param	float Margin : An additional distance you want to set
	 */
	UFUNCTION(BlueprintCallable, Category = "Centauri", meta = (DisplayName = "Set to Look At Object"))
		void SetLookAtObject_BP(AActor * Target, const float Margin = 0.f) { SetLookAtObject(Target, Margin); }
		 
	
	
};
