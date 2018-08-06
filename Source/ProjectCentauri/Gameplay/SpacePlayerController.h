// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "CentauriController.h"
#include "SpacePlayerController.generated.h"

/**
*	@brief EControllerStateEnum Enum
*	Describe the different states the player controller can be
*/
UENUM(Blueprintable)
enum class EControllerStateEnum : uint8
{
	CSE_Build	 	UMETA(DisplayName = "Building"),
	CSE_Pilot	 	UMETA(DisplayName = "Flying"),
	CSE_Aim			UMETA(DisplayName = "Aiming")
};

/**
 *	@brief ASpacePlayerController class
 *	Extend PlayerController by giving Selection capabilities
 */
UCLASS()
class PROJECTCENTAURI_API ASpacePlayerController : public ACentauriController
{
	GENERATED_BODY()
public:
	ASpacePlayerController();

	// Controller Bindings
	static const FName RotateYawBinding;
	static const FName RotatePitchBinding;
	static const FName RotateRollBinding;

	/**
	*	@brief SelectionModeBinding Property
	*	The name of the binding for togglingSelectionMode
	*/
	static const FName SelectionToggleBinding;

	/**
	*	@brief SelectionModeBinding Property
	*	The name of the binding for togglingSelectionMode
	*/
	static const FName SelectionClickBinding;

	/**
	*	@brief SelectionModeBinding function
	*	Prepare the bindings
	*/
	virtual void InitializeBindings();

	/**
	*	@brief SetupInputComponent function override
	*	Enable the bindings
	*	@see APlayerController
	*/
	virtual void SetupInputComponent() override;

	/**
	*	@brief Tick function override
	*	Called every image
	*	@see AActor
	*/
	virtual void Tick(float DeltaTime) override;


public:
	/**
	*	@brief SelectionActorClass property
	*	class defining An actor allowing to show what's selected
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Selection")
		TSubclassOf<class ASelectionActor> SelectionActorClass;

protected:
	/**
	*	@brief SelectionActor property
	*	An actor allowing to show what's selected
	*/
	UPROPERTY()
		class ASelectionActor * SelectionActor;

	/**
	*	@brief SelectionActor property
	*	An actor allowing to show what's hovered
	*/
	UPROPERTY()
		class ASelectionActor * HoverActor;


	/**
	*	@brief SpawnSelectionActor Function
	*	@param SpawnTransform : the world transform to spawn it.
	*	@retrun a pointer to the created Actor or nullptr if it failed
	*	@note Does not assign anything you'll have to store the returned pointer.
	*/
	UFUNCTION()
		class ASelectionActor *  SpawnSelectionActor(const FTransform SpawnTransform);



public:
	/**
	*	@brief HoverOnMode function
	*	Allow for handling Hovering depending on Mode
	*	@param bool Mode : the mode to use
	*	@note : you should feed it the current mode
	*/
	UFUNCTION()
		void HoverOnMode(EControllerStateEnum Mode);



public:

	/**
	*	@brief SetSelectionMode function
	*	Allow for Changing mode of cursor
	*	@param bool IsSelectionMode : true to enable selection. false to disable.
	*/
	UFUNCTION()
		void SetSelectionMode(bool IsSelectionMode);

	/**
	 *	@brief SetSelectionMode_BP function
	 *	Allow for Changing mode of cursor
	 *	@param bool IsSelectionMode : true to enable selection. false to disable.
	 *	@note : For Blueprints to implement further behaviour.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri", meta = (DisplayName = "Selection Enabled"))
		void SetSelectionMode_BP(bool IsSelectionMode);


	/**
	 *	@brief ToggleSelectionMode function
	 *	Allow for Changing mode of cursor
	 */
	UFUNCTION()
		void ToggleSelectionMode();

	/**
	 *	@brief ToggleSelectionMode_BP function
	 *	Allow for Changing mode of cursor
	 *	@param bool IsSelectionMode : true to enable selection. false to disable.
	 *	@note : For Blueprints to implement further behaviour.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri", meta = (DisplayName = "Toggle selection"))
		void ToggleSelectionMode_BP();

	/**
	 *	@brief GetSelectedComponent function
	 *	Safe way to access SelectedComponent
	 *	@return USceneComponent * : The component selected or NULL if nothing is selected
	 */
	UFUNCTION()
		FORCEINLINE class USceneComponent * GetSelectedComponent() const { return SelectedComponent; }


	/**
	 *	@brief GetSelectedComponent function
	 *	Safe way to access SelectedComponent
	 *	@return USceneComponent * : The component selected or NULL if nothing is selected
	 *	@note : For Blueprints.
	 */
	UFUNCTION(BlueprintPure, Category = "Centauri", meta = (DisplayName = "Get Selected Component"))
		FORCEINLINE class USceneComponent * GetSelectedComponent_BP() const { return GetSelectedComponent(); }

	/**
	*	@brief GetSelectedComponent function
	*	Safe way to access bSelectionEnabled
	*	@return bool : true if in selection mode, false otherwise
	*/
	UFUNCTION()
		FORCEINLINE bool IsSelectionMode() const { return bSelectionEnabled; }


	/**
	*	@brief GetSelectedComponent function
	*	Safe way to access bSelectionEnabled
	*	@return bool : true if in selection mode, false otherwise
	*	@note : For Blueprints.
	*/
	UFUNCTION(BlueprintPure, Category = "Centauri", meta = (DisplayName = "Selection Mode Enabled ?"))
		FORCEINLINE bool IsSelectionMode_BP() const { return IsSelectionMode(); }


protected:
	
	/**
	 *	@brief DisplaySelection function
	 *	Allow to show on UI the selection
	 */
	UFUNCTION()
		virtual void DisplaySelection();

	/**
	 *	@brief DisplaySelection_BP function
	 *	Allow to show on UI the selection
	 *	@note : Not implemented in C++
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri", meta = (DisplayName = "Display Selection Component"))
		void DisplaySelection_BP();

private:

	UPROPERTY()
		bool bSelectionEnabled;  // boolean flag, true if in selection mode


private:

	UPROPERTY()
		EControllerStateEnum SpaceState;

public:

	/**
	*	@brief ChooseMode function
	*	Allow switching modes between building, flying and fighting
	*/
	UFUNCTION()
		virtual void ChooseMode(const EControllerStateEnum NewMode);


	/**
	*	@brief DisplaySelection_BP function
	*	Allow switching modes between building, flying and fighting
	*	@note for blueprint only, calls the C++ method
	*/
	UFUNCTION(BlueprintCallable, Category = "Centauri|Mode", meta = (DisplayName = "ChooseMode"))
	void ChooseMode_BP(const EControllerStateEnum NewMode) { ChooseMode(NewMode); }

	/**
	 *	@brief GetMode function
	 *	@return SpaceState
	 */
	UFUNCTION()
	FORCEINLINE EControllerStateEnum GetMode() const { return SpaceState; }

	/**
	 *	@brief GetMode_BP function
	 *	@return SpaceState
 	 *	@note for blueprint only.
	 */
	UFUNCTION(BlueprintPure, Category = "Centauri|Mode", meta = (DisplayName = "Get Mode"))
	FORCEINLINE EControllerStateEnum GetMode_BP() const { return SpaceState; }

protected:

	/**
	*	@brief SetBuilding function
	*	Set in building Mode
	*/
	UFUNCTION()
		virtual void SetBuilding();

	/**
	*	@brief DisplaySelection_BP function
	*	Setup the building Mode
	*	@note : Not implemented in C++
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri|Mode", meta = (DisplayName = "Set in building Mode"))
		void SetBuilding_BP();

	/**
	*	@brief SetBuilding function
	*	Set in building Mode
	*/
	UFUNCTION()
		virtual void SetPilot();

	/**
	*	@brief DisplaySelection_BP function
	*	Setup the Flying Mode
	*	@note : Not implemented in C++
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri|Mode", meta = (DisplayName = "Set in flying Mode"))
		void SetPilot_BP();

	/**
	*	@brief SetBuilding function
	*	Set in Aiming Mode
	*/
	UFUNCTION()
		virtual void SetAim();

	/**
	*	@brief DisplaySelection_BP function
	*	Setup the Aiming Mode
	*	@note : Not implemented in C++
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri|Mode", meta = (DisplayName = "Set in aiming Mode"))
		void SetAim_BP();



	
	
};
