// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpaceActorRootComponent.generated.h"

/**
 * @brief The USpaceActorRootComponent class
 * This represents the base of a space actor and can be derived to Create whole components representing ships elements.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCENTAURI_API USpaceActorRootComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceActorRootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Will not be called
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
