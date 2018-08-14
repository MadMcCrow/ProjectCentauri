// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Gameplay/CentauriController.h"
#include "CentauriWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCENTAURI_API UCentauriWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UCentauriWidget(const FObjectInitializer& ObjectInitializer);

	/**	Allows for setting Applying Variables set in Blueprint	*/
	virtual void OnWidgetRebuilt() override;


protected:

	/**	This is just a wrapper for a struct allowing to set the styles separately in a different Asset ( for reusability)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
	class USlateWidgetStyleAsset* DefaultWidgetStyle;
	This Cannot be used with UUserWidget. We'll have to Hardcode the conversion from this to the appearance
	*/

	virtual void PostLoad() override;


	/**
	 *	@brief BindDelegates function
	 *	This function is meant to do all the bindings ( OnClicked(), etc... ) in C++
	 *	@note : it is not necessary to call it. just define it in child Classes
	 */
	UFUNCTION()
		virtual void BindDelegates();

	/**
	*	@brief GetCentauriController function
	*	@return The Centauri Controller who controls it
	*/
	UFUNCTION()
		FORCEINLINE  ACentauriController *  GetCentauriController() { return Cast<ACentauriController>(GetOwningPlayer());}

	/**
	*	@brief GetCentauriController_BP function
	*	@return The Centauri Controller who controls it
	*/
	UFUNCTION(BlueprintPure, Category = "Centauri|UI", meta = (DisplayName ="Get Controller"))
		FORCEINLINE  ACentauriController *  GetCentauriController_BP() {	return GetCentauriController();	}

private:

	/**
	*	@brief bIsActive property
	*	Boolean Flag to do something if this should not be active
	*/
	UPROPERTY()
	bool bIsActive;

public:

	/**
	*	@brief SetActive function
	*	Setter for the Active Flag.
	*/
	UFUNCTION()
		void SetActive(bool NewActive);

	/**
	*	@brief SetActive_BP function
	*	Setter for the Active Flag.
	*	@note For BP only
	*/
	UFUNCTION(BlueprintCallable, Category = "Centauri|UI", meta = (DisplayName = "Set Active"))
		void SetActive_BP( const bool NewActive) { SetActive(NewActive); }

protected:

	/**
	*	@brief SetActive_BP function
	*	Function to implement behaviour of Active state
	*	@param isActive : Just pass the bIsActive value.
	*/
	UFUNCTION()
		virtual void OnActive(const bool IsActive);

	/**
	*	@brief SetActive_BP function
	*	Function to implement behaviour of Active state
	*	@param isActive : Just pass the bIsActive value.
	*	@note Implemented in BP, Not in C++
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Centauri|UI", meta = (DisplayName = "On Active Event"))
		void OnActive_BP(const bool IsActive);

};
