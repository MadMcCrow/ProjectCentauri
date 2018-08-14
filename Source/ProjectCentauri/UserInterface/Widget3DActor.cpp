// Copyright 2018 Noe PERARD-GAYOT

#include "Widget3DActor.h"
#include "Components/WidgetComponent.h"
#include "UserInterface/CentauriWidget.h"

// Sets default values
AWidget3DActor::AWidget3DActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	if (!Widget)
		return;
	RootComponent = Widget;
	if (WidgetClass)
		Widget->SetWidgetClass(WidgetClass.Get());
	Widget->RequestRedraw();
	Widget->bVisibleInReflectionCaptures = false;
	Widget->bRenderInMainPass = false;
	Widget->bRenderInMono = false;
	Widget->bOnlyOwnerSee = true;
	Widget->bReceivesDecals = false;
}

UCentauriWidget * AWidget3DActor::GetWidget() const
{
	if (Widget)
		return Cast<UCentauriWidget>(Widget->GetUserWidgetObject());
	return nullptr;
}
