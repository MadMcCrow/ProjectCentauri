// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CentauriController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCENTAURI_API ACentauriController : public APlayerController
{
	GENERATED_BODY()
public:
	ACentauriController();
protected:

	UPROPERTY()
		class USceneComponent * SelectedComponent; // Selected component by the selection method

	UPROPERTY()
		class AActor * SelectedActor;// Selected Actor by the selection method

	UPROPERTY()
		class USceneComponent * HoveredComponent; // Selected component by the MouseOver method

	UPROPERTY()
		class AActor * HoveredActor;// Selected Actor by the MouseOver method

public:

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
	UFUNCTION(BlueprintPure, Category = "Centauri", meta = (DisplayName = "Get Visible Component Under Cursor"))
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
		void MouseOverComponent_BP(class USceneComponent * Hovered);

};
