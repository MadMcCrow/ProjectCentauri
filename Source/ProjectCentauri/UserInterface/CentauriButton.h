// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/CentauriWidget.h"
#include "Components/Button.h"
#include "CentauriButton.generated.h"

/**
* @class UCentauriButton
* A button with an automatically added text Label
*/
UCLASS()
class PROJECTCENTAURI_API UCentauriButton : public UCentauriWidget
{
	GENERATED_BODY()

public:
	
	UCentauriButton(const FObjectInitializer& ObjectInitializer);

	/**	Allows for setting Applying Variables set in Blueprint	*/
	virtual void OnWidgetRebuilt() override;

protected:
	/** The text of the Text box child, will eventually */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text")
		FText Label;

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock * LabelWidget;

	UPROPERTY(meta = (BindWidget))
		class UButton * ButtonWidget;

	/**	This is just a wrapper for a struct allowing to set the styles separately in a different Asset ( for reusability) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Style")
		class USlateWidgetStyleAsset* ButtonStyle;

	UFUNCTION(BlueprintCallable, Category = "Button|Event")
		virtual void OnClicked();

	virtual void BindDelegates() override;


public:
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnButtonClickedEvent	OnClickedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnButtonPressedEvent	OnPressedDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnButtonReleasedEvent	OnReleaseDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnButtonHoverEvent		OnHoverDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Button|Event")
		FOnButtonHoverEvent		OnUnhoverDelegate;
	
	
};
