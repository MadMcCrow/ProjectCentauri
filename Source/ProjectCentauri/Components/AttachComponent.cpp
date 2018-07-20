// Copyright 2018 Noe PERARD-GAYOT

#include "AttachComponent.h"
#if WITH_EDITOR
#include "Components/ArrowComponent.h"
#endif // WITH_EDITOR



UAttachComponent::UAttachComponent() : Super()
{
	Owner = GetOwner();
#if WITH_EDITOR
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->ArrowColor = FColor::Yellow;
	Arrow->EditorScale = 1;
	Arrow->SetupAttachment(this);
#endif // WITH_EDITOR
}
