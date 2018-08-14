// Copyright 2018 Noe PERARD-GAYOT

#include "CentauriButton.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Styling/SlateWidgetStyleAsset.h"





UCentauriButton::UCentauriButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BindDelegates();
}

void UCentauriButton::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	//@TODO: Check this frequently as it is subject to change


	if (!LabelWidget)
	{
		Super::PostLoad();
		UE_LOG(LogSlate, Error, TEXT("Label Widget not set."));
		return;
	}
	LabelWidget->SetText(Label);

	if (!ButtonStyle) // This make no sens to do anything if nothing is set properly
	{
		Super::PostLoad();
		UE_LOG(LogSlate, Error, TEXT("Button Style not set."));
		return;
	}
	if (!ButtonWidget)
	{
		Super::PostLoad();
		UE_LOG(LogSlate, Error, TEXT("Button Widget not set."));
		return;
	}
	ButtonWidget->Style_DEPRECATED = ButtonStyle; // Maybe this won't work in future UE4 version

	const FButtonStyle* StylePtr = ButtonStyle->GetStyle<FButtonStyle>();
	if (StylePtr != nullptr)
	{
		ButtonWidget->WidgetStyle = *StylePtr;
	}
}


void UCentauriButton::BindDelegates()
{
	if (ButtonWidget)
	{
		ButtonWidget->OnClicked.Clear();
		ButtonWidget->OnClicked.AddDynamic(this, &UCentauriButton::OnClicked);
	}
}

void UCentauriButton::OnClicked()
{
	OnClickedDelegate.Broadcast();
}
