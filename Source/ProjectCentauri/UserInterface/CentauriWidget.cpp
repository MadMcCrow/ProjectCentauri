// Copyright 2018 Noe PERARD-GAYOT

#include "CentauriWidget.h"


UCentauriWidget::UCentauriWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BindDelegates();
}

void UCentauriWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	BindDelegates(); // Somehow works when set here efficient here
}

void UCentauriWidget::PostLoad()
{
	Super::PostLoad();
	BindDelegates();
}

void UCentauriWidget::BindDelegates()
{

}

void UCentauriWidget::SetActive(bool NewActive)
{
	bIsActive = NewActive;
	OnActive(bIsActive);
}

void UCentauriWidget::OnActive(bool IsActive)
{
	OnActive_BP(IsActive);
}



