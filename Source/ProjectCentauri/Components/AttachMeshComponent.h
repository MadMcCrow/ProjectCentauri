// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/AttachComponent.h"
#include "AttachMeshComponent.generated.h"

/**
 *  @brief UAttachMeshComponent class
 *	This Class just adds a static mesh to see the connector.
 */
UCLASS(Blueprintable, ClassGroup = (Centauri), meta = (BlueprintSpawnableComponent))
class PROJECTCENTAURI_API UAttachMeshComponent : public UAttachComponent
{
	GENERATED_BODY()

public:
	/**
	 *	@brief UAttachMeshComponent function
	 *	Default Constructor, calls parent and construct the static Mesh Component
	 */
	UAttachMeshComponent();

private:

	/**
	*	@brief ThrusterMeshComponent
	*	Static mesh representing the Connector. is only cosmetic
	*/
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent * ConnectorMeshComponent;

	
	
	
};
