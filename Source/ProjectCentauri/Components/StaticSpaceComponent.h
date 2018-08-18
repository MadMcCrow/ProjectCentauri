// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "AttachInterface.h"
#include "StaticSpaceComponent.generated.h"

/**
 *	@class UStaticSpaceComponent
 *	Space-ship/Space-Station part that has no movable part
 */
UCLASS(ClassGroup = (SpaceActors), Blueprintable)
class PROJECTCENTAURI_API UStaticSpaceComponent : public UStaticMeshComponent, public IAttachInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaticSpaceComponent();

	virtual void PostInitProperties() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	/**
	*	@brief Sockets property
	*	Stores the information to the Sockets used in this component
	*	@see IAttachInterface
	*/
	UPROPERTY()
		TArray<FSpaceSocket> Sockets;


public:


	// IAttachInterface override
	UFUNCTION()
		virtual class UMeshComponent * GetMesh() const override { return (UMeshComponent*)this; }

protected:

	// IAttachInterface override
	UFUNCTION()
		virtual void SetSockets(class UMeshComponent * Setup) override;

public:

	// IAttachInterface override
	UFUNCTION()
		FORCEINLINE TArray<FSpaceSocket> GetSockets() const override { return Sockets; }


};
