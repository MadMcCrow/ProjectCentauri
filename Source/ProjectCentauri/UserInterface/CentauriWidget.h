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
	UFUNCTION(BlueprintPure, Category = "Centauri", meta = (DisplayName ="Get Controller"))
		FORCEINLINE  ACentauriController *  GetCentauriController_BP() {	return GetCentauriController();	}

};
