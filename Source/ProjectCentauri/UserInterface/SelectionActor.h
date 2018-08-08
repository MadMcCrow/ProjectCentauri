// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Widget3DActor.h"
#include "SelectionActor.generated.h"

UCLASS()
class PROJECTCENTAURI_API ASelectionActor : public AWidget3DActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelectionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	*	@brief SetActive function
	*	get the boolean flag as a const return
	*	@return bool : true if selection, false if just hover
	*	@see bIsSelection
	*/
	UFUNCTION()
		FORCEINLINE bool GetIsSelection() const { return bIsSelection;}


	/**
	*	@brief SetActive_BP function
	*	get the boolean flag as a const return
	*	@return bool : true if selection, false if just hover
	*	@see bIsSelection
	*	@note for Blueprint Debugging
	*/
	UFUNCTION(BlueprintPure, Category ="SelectionActor", meta = (DisplayName = "Is Active ?"))
		FORCEINLINE bool GetIsSelection_BP() const { return bIsSelection; }

	/**
	*	@brief SetActive function
	*	Set The Selection Actor it's active State
	*	@param bool Active : true to active false to disable.
	*	@see bIsActive
	*/
	UFUNCTION()
		void SetActive(bool Active);
	/**
	*	@brief SetActive function
	*	Set The Selection Actor it's active State
	*	@param bool Active : true to active false to disable.
	*	@note : For Blueprints to implement further behaviour.
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "SelectionActor", meta = (DisplayName = "Active Effect"))
		void SetActive_BP(bool Active);

private:
	/**
	 *	@brief bIsSelection property
	 *	boolean flag for Activity
	 *	Active mean the Selection Actor is currently showing a selection
	 */
	UPROPERTY()
		bool bIsSelection;

	
	
};
