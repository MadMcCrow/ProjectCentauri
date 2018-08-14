// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Widget3DActor.generated.h"

UCLASS()
class PROJECTCENTAURI_API AWidget3DActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWidget3DActor();

	/**
	*	@brief WidgetClass property
	*	The widget Displaying component
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Centauri|UI")
		TSubclassOf<class UCentauriWidget> WidgetClass;


	/**
	*	@brief Widget property
	*	The widget Displaying component
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Centauri|UI")
		class UWidgetComponent * Widget;


	/**
	*	@brief GetWidget_BP function
	*	Get the Underlying Widget
	*	@return the underlying Centauri Widget, nullptr if there's none
	*/
	UFUNCTION()
		class UCentauriWidget * GetWidget() const;

	/**
	*	@brief GetWidget_BP function
	*	Get the Underlying Widget
	*	@return the underlying Centauri Widget, nullptr if there's none
	*	@note : For BP only
	*/
	UFUNCTION(BlueprintPure, Category = "Centauri|UI", meta = (DisplayName = "Get Widget"))
		class UCentauriWidget * GetWidget_BP() const { return GetWidget(); }

	
};
