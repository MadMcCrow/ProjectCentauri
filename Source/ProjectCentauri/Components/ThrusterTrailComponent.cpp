// Copyright 2018 Noe PERARD-GAYOT

#include "ThrusterTrailComponent.h"
#include "ConstructorHelpers.h"

UThrusterTrailComponent::UThrusterTrailComponent()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystem_BP(TEXT("ParticleSystem'/Game/Effects/Particules/ThusterTrail.ThusterTrail'"));
	if (ParticleSystem_BP.Succeeded())
		SetTemplate(ParticleSystem_BP.Object);
	else
#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Warning, TEXT("Could not initialize particule system"));
#endif
}

