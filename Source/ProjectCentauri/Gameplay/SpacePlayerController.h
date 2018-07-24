// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpacePlayerController.generated.h"

/**
 *	@brief ASpacePlayerController class
 *	Extend PlayerController by giving Selection capabilities
 */
UCLASS()
class PROJECTCENTAURI_API ASpacePlayerController : public APlayerController
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

	/**
	 *	@brief GetVisibleComponentUnderCursor function
	 *	Fast an easy way of finding components under the mouse
	 *	@return USceneComponent * : A component that's under the cursor, nullptr if you're pointing at the void
	 */
	UFUNCTION()
		USceneComponent * GetVisibleComponentUnderCursor();

	/**
	 *	@brief GetVisibleComponentUnderCursor_BP function
	 *	Fast an easy way of finding components under the mouse, for blueprints
	 *	@return USceneComponent * : A component that's under the cursor, nullptr if you're pointing at the void
	 *	@note : For Blueprints.
	 */
	UFUNCTION(BlueprintPure, Category = "Centauri", meta = (DisplayName = "Get Visible Component Under Cursor") )
		FORCEINLINE USceneComponent * GetVisibleComponentUnderCursor_BP() { return GetVisibleComponentUnderCursor(); }

	/**
	 *	@brief GetComponentByObjectUnderCursor function
	 *	Fast an easy way of finding components under the mouse
	 *	@return USceneComponent * : A component that's under the cursor, nullptr if you're pointing at the void
	 */
	UFUNCTION()
		USceneComponent * GetComponentByObjectUnderCursor();

	/**
	 *	@brief GetComponentByObjectUnderCursor_BP function
	 *	Fast an easy way of finding components under the mouse, for blueprints
	 *	@return USceneComponent * : A component that's under the cursor, nullptr if you're pointing at the void
	 *	@note : For Blueprints.
	 */
	UFUNCTION(BlueprintPure, Category = "Centauri", meta = (DisplayName = "Get Component by Object Under Cursor"))
		FORCEINLINE USceneComponent * GetComponentByObjectUnderCursor_BP() { return GetComponentByObjectUnderCursor(); }


	/**
	 *	@brief SelectComponent function
	 *	Select a cursor. is called by a binding (should be the left click)
	 */
	UFUNCTION()
		void SelectComponent();

	/**
	 *	@brief SelectComponent_BP function
	 *	@note : For Blueprints to implement further behaviour.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri", meta = (DisplayName = "Select Component"))
		void SelectComponent_BP(class USceneComponent * Selected);

	/**
	*	@brief MouseOverComponent function
	*	hover a component. is called in tick
	*/
	UFUNCTION()
		void MouseOverComponent();

	/**
	*	@brief SelectComponent_BP function
	*	@note : For Blueprints to implement further behaviour.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri", meta = (DisplayName = "Mouse Over Component"))
		void MouseOverComponent_BP( class USceneComponent * Hovered);

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

	UPROPERTY()
		class USceneComponent * SelectedComponent; // Selected component by the selection method

	UPROPERTY()
		class AActor * SelectedActor;// Selected Actor by the selection method

	UPROPERTY()
		class USceneComponent * HoveredComponent; // Selected component by the MouseOver method

	UPROPERTY()
		class AActor * HoveredActor;// Selected Actor by the MouseOver method



	
	
};
