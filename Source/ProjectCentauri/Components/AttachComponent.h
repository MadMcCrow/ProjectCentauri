// Copyright 2018 Noe PERARD-GAYOT

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AttachComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCENTAURI_API UAttachComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttachComponent();


#if WITH_EDITOR
	class UArrowComponent * Arrow; /** This allows displaying an arrow in editor to clearly see the attach component*/
#endif // WITH_EDITOR

	/**	
	 *	@brief GetWorldTransform
	 *	Allows for getting the world location of the AttachComponent 
	 */
	FORCEINLINE FTransform GetWorldTransform(){
		FTransform worldtrans = GetRelativeTransform();
		worldtrans.AccumulateWithShortestRotation(Owner->GetTransform(), ScalarRegister(1.f));
		return worldtrans;
	}



private:
		class AActor* Owner;

};
